#include <sstream>
#include "stdlib.h"
#include "stdio.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/Int16MultiArray.h"
#include "std_msgs/Float64MultiArray.h"
using namespace std;
//常量
const double theta = 60.0 / 1690;
const double PI = acos(-1.0);
const double eps = 2;

//变量
double Angle[3]; // 角度读取值
int speed[5];
bool rotateSignal = false;
int PreSpeed = 0;
int TargetAngle = 0;
int delta = 5;
double initAngle = 116.78597;//车子出发时候的角度
double setAngle;

//函数
void PrintROSUint8MultiArray(std_msgs::UInt8MultiArray Data, int RorW)//打印函数
{
    char tmp[2000];
    memset(tmp, 0, sizeof tmp);
    if (RorW == 0)
    {
        strcat(tmp, "Read:");
    }
    else
        strcat(tmp, "Write:");
    for (int i = 0; i < Data.data.size(); ++i)
    {
        char myhex[10];
        sprintf(myhex, " 0x%02x", Data.data[i]);
        strcat(tmp, myhex);
    }
    ROS_INFO("%s", tmp);
}

//void getFromFile()
//{
//    FILE *fp = fopen("/home/zyc/catkin_ws/1.txt", "r");
//    //   if(!fp) printf("ERROR OPEN FILE");
//    fscanf(fp, "%d %d %d %d", &speed[0], &speed[1], &speed[2], &speed[3]);
//    fclose(fp);
//}
void setRotateAngle(double);
int sgn(double x)
{
    if (fabs(x) < eps)
        return 0;
    if (x < 0)
        return -1;
    else
        return 1;
}
double getRightAngle(double myangle){//0-360
    if(myangle<0) myangle += 360;
    return myangle;
}
void AngleSetCallBack(const std_msgs::Float64MultiArray::ConstPtr &Data)
{
    Angle[0] = Data->data[0];
    Angle[1] = Data->data[1];
    Angle[2] = getRightAngle(Data->data[2]);
}
/*
 2 3
 0 1
 */
//void modifySpeed()
//{
//    ROS_INFO("%lf", Angle[2]);
//    int delta = 10;
//    if (sgn(Angle[2]) == 1)
//    { //向右偏转
//        speed[3] += delta;
//        speed[1] += delta;
//    }
//    if (sgn(Angle[2]) == -1)
//    {
//        speed[0] += delta;
//        speed[2] += delta;
//    }
//
//    if (speed[0] > 2000 || speed[1] > 2000 || speed[2] > 2000 || speed[3] > 2000)
//    {
//        speed[1] = speed[3] = 1500;
//        speed[0] = speed[2] = speed[1] * (1 - theta);
//        //speed[0]/=2,speed[1]/=2,speed[2]/=2,speed[3]/=2;
//    }
//    ROS_INFO("RF=%d LF=%d RD=%d LD=%d", speed[0], speed[1], speed[2], speed[3]);
//}
//lets go straight
/*
void goStraight(){
    ROS_INFO("%lf",Angle[2]);
    for(int i=0;i<30;++i){
        if(sgn(Angle[2])==1){//向右偏转
            speed[3] += 1;
            speed[1] += 1;
        }
        if(sgn(Angle[2])==-1){
            speed[0] += 1;
            speed[2] += 1;
        }
    }
    //ROS_INFO("RF=%d LF=%d RD=%d LD=%d",speed[0],speed[1],speed[2],speed[3]);
}
*/
//TODO
/* 正
    ^
   1 0
   3 2
 */
void rotate(){
    double diff = setAngle - Angle[2];
    diff = fabs(diff);
    diff = min(diff,360-diff);
    printf("setAngle = %lf Angle[2]=%lf diff=%lf\n",setAngle,Angle[2],diff);
    if(sgn(diff)==0){
        speed[0] = speed[1] = speed[2] = speed[3] = 000;
        setAngle = Angle[2];
        rotateSignal = false;
        return;
    }
 //   if(setAngle-Angle[2]>0||setAngle-Angle[2]<-180){//需要顺时针旋转 当前的角度没有到达设定的位置
        // + -
        //+ -
        //speed[1] = speed[3] = 1000;
        //speed[0] = speed[2] = -1000;
   // }
   // else{//需要逆时针旋转
        //- +
        //- +
            speed[1] = speed[3] = -1000;
            speed[0] = speed[2] = 1000;
    //}
}
void goStraight(){
    speed[0] = speed[1] = speed[2] = speed[3] = 2000;
}
void goRight(){
    //+ -
    //- +
    speed[1] = speed[2] = 2000;
    speed[0] = speed[3] = -2000;
}
void goLeft(){
    //- +
    //+ -
    speed[1] = speed[2] = -2000;
    speed[0] = speed[3] = 2000;
}
void goBack(){
    speed[0] = speed[1] = speed[2] = speed[3] = -2000;
}
void Run(int angle, int Speed) //设定的加减角度 设定速度
{
    ROS_INFO("ANGLE: %d, SPEED:%d",angle,Speed);
    if (angle == 0) //继续直线行走
    {
        if (Speed == 0)
        {
            speed[0] = speed[1] = speed[2] = speed[3] = 0;
        }
        if (Speed == PreSpeed) //如果和之前速度一样 就按角度更改
        {
            if (Angle[2] < TargetAngle)
            {
                speed[0] += delta;
                speed[2] += delta;
                speed[1] -= delta;
                speed[3] -= delta;
            }
            else
            {
                speed[0] -= delta;
                speed[2] -= delta;
                speed[1] += delta;
                speed[3] += delta;
            }
        }
        else //如果不一样 设定到角度即可
        {
            PreSpeed = Speed; //更新之前速度
            speed[1] = speed[3] = Speed;
            speed[0] = speed[2] = Speed * (1 - theta);
        }
    }
    else // 停下转向
    {
        TargetAngle = angle;
        if (abs(TargetAngle - Angle[2]) < 1)
        {
            Run(0,0);
        }
        else
        {
            speed[1] = speed[3] = Speed;
            speed[0] = speed[2] = -(Speed * (1- theta));
        }
    }
    ROS_INFO("RF=%d LF=%d RD=%d LD=%d",speed[0],speed[1],speed[2],speed[3]);
}
short Argc_Angle,Argc_Speed=0;
void ControllerSetCallBack(const std_msgs::Int16MultiArray::ConstPtr &Data)
{
    Argc_Angle=Data->data[0];
    Argc_Speed=Data->data[1];
}
double getRad(double degree){
    return degree*PI/180.0;
}
void setRotateAngle(double relativeAngle){//相对当前位置旋转一定的角度
    setAngle = relativeAngle + Angle[2];
    if(setAngle<0) setAngle += 360;
    if(setAngle>360) setAngle -= 360;
    rotateSignal = true;
}
int main(int argc, char **argv)
{
    int i;
    ros::init(argc, argv, "TestW");
    ros::NodeHandle n;

    ros::Publisher TestW = n.advertise<std_msgs::UInt8MultiArray>("serialW", 1000);

    ros::Subscriber AngleListener = n.subscribe("angle", 1000, AngleSetCallBack);
    ros::Subscriber ControllerListener = n.subscribe("controller", 1000, ControllerSetCallBack);

    ros::Rate loop_rate(50);
    int count = 0;
    speed[1] = speed[3] = 2000;
    speed[0] = speed[2] = 2000;
    while (ros::ok())
    {
        std_msgs::UInt8MultiArray val;
        if(count==100){//假设在这个时候我们想要他转90度 走了两格
            setRotateAngle(90);
        }
        /*
        else if(count==350){
            setRotateAngle(90-8);
        }
        else if(count==517){
            setRotateAngle(90-8);
        }
        else if(count==734){
            setRotateAngle(90-8);
        }
         */
        //else if(count>1000){
          //  speed[0] = speed[1] = speed[2] = speed[3] = 0;
        //}
     /*
        else if(count==800){
            setRotateAngle(90-8);
        }
        else if(count==1344){
            setRotateAngle(90-8);
        }
        else if(count==1888){
            setRotateAngle(90-8);
        }
        */
       if (count)
        {
            if(rotateSignal){//旋转符号标志
                rotate();
            }
            val.data.push_back(0x04);
            for (int j = 0; j < 4; ++j)
            {
                val.data.push_back(speed[j] > 0 ? 1 : 0);
                speed[j] = abs(speed[j]);
                val.data.push_back((speed[j] & 0xFF00) >> 8);
                val.data.push_back((speed[j] & 0xFF));
            }
            TestW.publish(val);

            std_msgs::UInt8MultiArray val2;
            val2.data.push_back(0x01);
            TestW.publish(val2);
        }
        ros::spinOnce();
        loop_rate.sleep();
        //if(speed[0]==speed[1]&&speed[1]==speed[2]&&speed[2]==speed[3]&&speed[3]==2000)
            ++count;
    }
    return 0;
}