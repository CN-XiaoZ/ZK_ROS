#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/Float64MultiArray.h"

uint8_t pointer = 0;   // 接收位置
uint8_t rx_buff[255]; // 指令接收暂存区
uint8_t LEN;           // 指令长度指示位
uint8_t count;         // 共用计数值
uint8_t sum;           // 校验和

double Angle[3];

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
                            short Dx,Dy,Dz;
                            short GLx,GLy;

                            Dx = ((short)rx_buff[17]<<8|rx_buff[16]);
                            Dy = ((short)rx_buff[19]<<8|rx_buff[18]);
                            Dz = ((short)rx_buff[21]<<8|rx_buff[20]);
                            GLx = ((short)rx_buff[22]<<8|rx_buff[23]);
                            GLy = ((short)rx_buff[24]<<8|rx_buff[25]);
                            //printf("%hd\n",Dz);
                            //printf("%X %X %X\n",rx_buff[20],rx_buff[21],(short)rx_buff[20]<<8|rx_buff[21]);
                            Angle[0] = (Dx/32768.0)*180;
                            Angle[1] = (Dy/32768.0)*180;
                            Angle[2] = (Dz/32768.0)*180;


                            printf("%lf %lf %lf\n",Angle[0],Angle[1],Angle[2]);

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
    ros::Publisher AngleTalker = n.advertise<std_msgs::Float64MultiArray>("angle", 1000);
    ros::Rate loop_rate(50);

    int count = 0;

    while (ros::ok()) {
        std_msgs::Float64MultiArray val;
        val.data.push_back(Angle[0]);
        val.data.push_back(Angle[1]);
        val.data.push_back(Angle[2]);
        AngleTalker.publish(val);
        ros::spinOnce();
        loop_rate.sleep();
        ++count;
    }
    return 0;
}
