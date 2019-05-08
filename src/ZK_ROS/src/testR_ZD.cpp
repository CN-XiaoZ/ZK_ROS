//
// Created by ZYC on 2019/4/15.
//

#include <sstream>
#include "ros/ros.h"
#include "Timer.hpp"
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/Float64MultiArray.h"

uint8_t pointer = 0;   // 接收位置
uint8_t rx_buff[255]; // 指令接收暂存区
uint8_t LEN;           // 指令长度指示位
uint8_t count;         // 共用计数值
uint8_t sum;           // 校验和
uint32_t DataArray[60];
const int ServoNum = 3;
double Angle[3];
timer a;

void AnalysisData(uint8_t temp)
{
    if (pointer < 2)
    {
        rx_buff[pointer++] = temp;
        return;
    }
    if (pointer == 2)
    {
        if ((rx_buff[0] == 0x12) && (rx_buff[1] == 0x34))
        {
            rx_buff[pointer++] = temp;
            LEN                = temp;
        }
        else
        {
            rx_buff[0] = rx_buff[1];
            rx_buff[1] = temp;
        }
        return;
    }
    if (pointer > 2)
    {
        if (pointer < LEN)
        {
            rx_buff[pointer++] = temp;
            if (pointer == LEN)
            {
                if (rx_buff[LEN - 1] == 0x2F && rx_buff[LEN - 2] == 0x1F)
                {
                    for (count = 2; count < LEN - 3; count++) { sum = rx_buff[count] + sum; }
                    if (rx_buff[LEN - 3] == sum)
                    {
                        a.toc();
//                        for(int i=0;i<6;i++)
//                        {
//                            int data=(rx_buff[6+4*i]<<24)|(rx_buff[5+4*i]<<16)|(rx_buff[4+4*i]<<8)|rx_buff[3+4*i];
//                            printf("%7d ",data);
//                        }
//                        for(int i=0;i<9;i++)
//                        {
//                            short data=(rx_buff[27+2*i]<<8)|rx_buff[28+2*i];
//                            printf("%7d ",data);
//                        }
                        for(int i=0;i<LEN;i++)
                        {
                            printf("0x%X ",rx_buff[i]);
                        }
                        printf("\n");
                    }
                }
                sum     = 0;
                pointer = 0;
                memset(rx_buff, 0, 256 * sizeof(uint8_t));
            }
            else
            {
                return;
            }
        }
    }
}


void GetOrderCallBack(const std_msgs::UInt8MultiArray::ConstPtr &Data)
{
    for(int i=0;i<Data->data.size();i++)
    {
        AnalysisData(Data->data[i]);
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "TestR");
    ros::NodeHandle n;
    ros::Subscriber SerialOrder = n.subscribe("serialR_ZD", 1000, GetOrderCallBack);
    ros::Rate loop_rate(100);

    int count = 0;

    a.tic();
    while (ros::ok()) {
        std_msgs::Float64MultiArray val;
        ros::spinOnce();
        loop_rate.sleep();
        ++count;
    }
    return 0;
}
