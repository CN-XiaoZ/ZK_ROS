#include <sstream>
#include "stdlib.h"
#include "stdio.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/Float64MultiArray.h"

double Angle[3];



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
//test ....
int speed[5];
void getFromFile(){
    FILE *fp = fopen("/home/zyc/catkin_ws/1.txt","r");
    //if(fp){
      //  ROS_INFO("??");
    //}
    //else ROS_INFO("....");
   fscanf(fp,"%d %d %d %d",&speed[0],&speed[1],&speed[2],&speed[3]);

    fclose(fp);
}

void AngleSetCallBack(const std_msgs::Float64MultiArray::ConstPtr &Data)
{
    Angle[0]=Data->data[0];
    Angle[1]=Data->data[1];
    Angle[2]=Data->data[2];
    printf("%lf %lf %lf",Data->data[0],Data->data[1],Data->data[2]);
}

int main(int argc, char **argv) {
    int i;

    ros::init(argc, argv, "TestW");

    ros::NodeHandle n;

    ros::Publisher TestW = n.advertise<std_msgs::UInt8MultiArray>("serialW", 1000);
    ros::Subscriber AngleListener = n.subscribe("angle", 1000, AngleSetCallBack);

    ros::Rate loop_rate(10);

    int count = 0;

    while (ros::ok()) {
        std_msgs::UInt8MultiArray val;
        if (count % 5 == 0)
        {
            std_msgs::UInt8MultiArray val;
            getFromFile();
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
    }
    return 0;
}

