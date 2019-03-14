#include <sstream>
#include "stdlib.h"
#include "stdio.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"


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

int main(int argc, char **argv) {
    int i;

    ros::init(argc, argv, "TestW");

    ros::NodeHandle n;

    ros::Publisher TestW = n.advertise<std_msgs::UInt8MultiArray>("serialW", 1000);

    ros::Rate loop_rate(10);

    int count = 0;

    while (ros::ok()) {
        std_msgs::UInt8MultiArray val;
        if (count % 10 == 0)
        {
            std_msgs::UInt8MultiArray val;
            val.data.push_back(0x01);
            TestW.publish(val);
            PrintROSUint8MultiArray(val, 1);
        }
        ros::spinOnce();
        loop_rate.sleep();
        ++count;
    }
    return 0;
}

