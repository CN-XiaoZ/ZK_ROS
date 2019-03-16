#include <sstream>
#include "stdlib.h"
#include "stdio.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/Float64MultiArray.h"
double Angle[3];
int stopKey;
void PrintROSUint8MultiArray(std_msgs::UInt8MultiArray Data, int RorW) {
    char tmp[2000];
    memset(tmp, 0, sizeof tmp);
    if (RorW == 0) {
        strcat(tmp, "Read:");
    } else strcat(tmp, "Write:");
    for (int i = 0; i < Data.data.size(); ++i) {
        char myhex[10];
        sprintf(myhex, " 0x%02x", Data.data[i]);
        strcat(tmp, myhex);
    }
    ROS_INFO("%s", tmp);
}
int speed[5];
double theta = 60.0/1690;
void getFromFile(){
    FILE *fp = fopen("/home/zyc/catkin_ws/1.txt","r");
 //   if(!fp) printf("ERROR OPEN FILE");
    fscanf(fp,"%d %d %d %d",&speed[0],&speed[1],&speed[2],&speed[3]);
    fclose(fp);
}
const double eps = 0.5;
int sgn(double x){
    if(fabs(x)<eps)return  0;
    if(x<0) return -1;
    else return  1;
}
const double init_angle = 116.762695;
void AngleSetCallBack(const std_msgs::Float64MultiArray::ConstPtr &Data)
{
    Angle[0]=Data->data[0]-init_angle;
    Angle[1]=Data->data[1]-init_angle;
    Angle[2]=Data->data[2]-init_angle;
    //modify speed
    //printf("%lf %lf %lf\n",Data->data[0],Data->data[1],Data->data[2]);
}
/*
 2 3

 0 1
 */
void modifySpeed(){
    ROS_INFO("%lf",Angle[2]);
    int delta = 10;
    if(sgn(Angle[2])==1){//向右偏转
        speed[3] += delta;
        speed[1] += delta;
    }
    if(sgn(Angle[2])==-1){
        speed[0] += delta;
        speed[2] += delta;
    }

    if(speed[0]>2000||speed[1]>2000||speed[2]>2000||speed[3]>2000){
        speed[1] = speed[3] = 1500;
        speed[0] = speed[2] = speed[1]*(1-theta);
        //speed[0]/=2,speed[1]/=2,speed[2]/=2,speed[3]/=2;
    }
    ROS_INFO("RF=%d LF=%d RD=%d LD=%d",speed[0],speed[1],speed[2],speed[3]);
}
//lets go straight
/*
void goStraight(){
    ROS_INFO("%lf",Angle[2]);
    if(sgn(Angle[2])==1){//向右偏转
        speed[3] += 1;
        speed[1] += 1;
    }
    if(sgn(Angle[2])==-1){
        speed[0] += 1;
        speed[2] += 1;
    }
    if(speed[0]>2000||speed[1]>2000||speed[2]>2000||speed[3]>2000){
        speed[0]/=2,speed[1]/=2,speed[2]/=2,speed[3]/=2;
    }
    ROS_INFO("RF=%d LF=%d RD=%d LD=%d",speed[0],speed[1],speed[2],speed[3]);
}
 */
void stopSignal(){
    char startKey[100];
    char endKey[100];
    FILE *fp = fopen("/home/zyc/catkin_ws/st.txt","r");
    fscanf(fp,"%s",startKey);
    fclose(fp);

    FILE *fp1 = fopen("/home/zyc/catkin_ws/ed.txt","r");
    fscanf(fp1,"%s",endKey);
    fclose(fp1);
    if(strcmp(startKey,endKey)==0){
        speed[0]=speed[1]=speed[2]=speed[3]=0;
    }
}

int main(int argc, char **argv) {
    int i;
    ros::init(argc, argv, "TestW");
    ros::NodeHandle n;
    ros::Publisher TestW = n.advertise<std_msgs::UInt8MultiArray>("serialW", 1000);
    ros::Subscriber AngleListener = n.subscribe("angle", 1000, AngleSetCallBack);
    ros::Rate loop_rate(10);
    int count = 0;
    speed[1] = speed[3] = 1500;
    speed[0] = speed[2] = speed[1]*(1-theta);
    while (ros::ok()){
        std_msgs::UInt8MultiArray val;
        if (count % 5 == 0)
        {
            for(int i=0;i<10;++i) modifySpeed();
            val.data.push_back(0x04);
            for(int j=0;j<4;++j){
                val.data.push_back(speed[j]>0?1:0);
                speed[j]=abs(speed[j]);
                val.data.push_back((speed[j]&0xFF00)>>8);
                val.data.push_back((speed[j]&0xFF));
            }
            TestW.publish(val);
            std_msgs::UInt8MultiArray val2;
            val2.data.push_back(0x01);
            TestW.publish(val2);
        }
        ros::spinOnce();
        loop_rate.sleep();
        ++count;
        stopSignal();
    }
    return 0;
}

