//
// Created by zyc on 19-3-16.
//

#include <sstream>
#include "stdlib.h"
#include "stdio.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/Int16MultiArray.h"
#include "std_msgs/Float64MultiArray.h"
int main(int argc, char **argv)
{
    int i;
    ros::init(argc, argv, "Order");
    ros::NodeHandle n;
    ros::Publisher ControllerTalker = n.advertise<std_msgs::Int16MultiArray>("controller", 1000);

    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        short Angle,Speed;
        std_msgs::Int16MultiArray val;
        scanf("%hd %hd",&Angle,&Speed);
        val.data.push_back(Angle);
        val.data.push_back(Speed);
        ControllerTalker.publish(val);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}