#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"


uint8_t pointer = 0;   // 接收位置
uint8_t rx_buff[255]; // 指令接收暂存区
uint8_t LEN;           // 指令长度指示位
uint8_t count;         // 共用计数值
uint8_t sum;           // 校验和

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
                        if (rx_buff[3] == 0x01) //返回传感器数据
                        {
                            short Ax,Ay,Az;
                            short Dx,Dy,Dz;
                            Ax = ((short)rx_buff[4]<<8|rx_buff[5]);
                            Ay = ((short)rx_buff[6]<<8|rx_buff[7]);
                            Az = ((short)rx_buff[8]<<8|rx_buff[9]);

                            Dx = ((short)rx_buff[16]<<8|rx_buff[17]);
                            Dy = ((short)rx_buff[18]<<8|rx_buff[19]);
                            Dz = ((short)rx_buff[20]<<8|rx_buff[21]);

                            double Axf,Ayf,Azf;
                            double Dxf,Dyf,Dzf;

                            Axf = (Ax/32768.0)*16;
                            Ayf = (Ay/32768.0)*16;
                            Azf = (Az/32768.0)*16;

                            Dxf = (Dx/32768.0)*180;
                            Dyf = (Dy/32768.0)*180;
                            Dzf = (Dz/32768.0)*180;

                            ROS_INFO("Ax: %d Ay: %d Az:%d Dx: %d Dy: %d Dz: %d",Ax,Ay,Az,Dx,Dy,Dz);
                            ROS_INFO("Ax: %lf Ay: %lf Az:%lf Dx: %lf Dy: %lf Dz: %lf",Axf,Ayf,Azf,Dxf,Dyf,Dzf);
                        }
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
    ros::Subscriber SerialOrder = n.subscribe("serialR", 1000, GetOrderCallBack);

    ros::Rate loop_rate(50);

    int count = 0;

    while (ros::ok()) {

        ros::spinOnce();
        loop_rate.sleep();
        ++count;
    }
    return 0;
}
