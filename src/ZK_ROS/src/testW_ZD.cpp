//
// Created by ZYC on 2019/4/15.
//

#include <sstream>
#include "stdlib.h"
#include "stdio.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt32MultiArray.h"
const int ServoNum = 3;
int main(int argc, char **argv)
{
    int i;
    ros::init(argc, argv, "TestW");
    ros::NodeHandle n;

    ros::Publisher TestW = n.advertise<std_msgs::UInt32MultiArray>("serialW_ZD", 1000);
    ros::Rate loop_rate(100);
    int data[30]={2048,2048,2048};
    while (ros::ok())
    {
        std_msgs::UInt32MultiArray val;

        for(i=0;i<ServoNum;i++) {
            val.data.push_back(data[i]);
        }
        TestW.publish(val);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}