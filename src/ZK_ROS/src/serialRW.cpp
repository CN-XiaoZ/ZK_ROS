//
// Created by zyc on 19-3-12.
//

#include <sstream>
#include "ros/ros.h"
#include <serial/serial.h>
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"

serial::Serial ser;

const int R = 0;
const int W = 1;

void SendOrder_Single(uint8_t Data) {
    uint8_t Order[7];
    int sum;
    Order[0] = 0x12;
    Order[1] = 0x34;
    Order[2] = 0x07;
    Order[3] = Data;
    Order[4] = (uint8_t) ((0x07 + Data) & 0xFF);
    Order[5] = 0x1F;
    Order[6] = 0x2F;
    ser.write(Order, 7);
}
// 12 34 len order checksum 1F 2F
//12 34 len list checksum 1F 2F
// 12 34 12+6 00 12 12 01 12 12 01 13 13
void SendOrder_List(uint8_t *Data, uint8_t size) {
    uint8_t Order[255];
    int sum, i;
    uint8_t CheckSum;
    Order[0] = 0x12;
    Order[1] = 0x34;
    Order[2] = size + 6;
    sum = Order[2];
    memcpy(&Order[3], Data, size);
    for (i = 0; i < size; i++) {
        sum = sum + Data[i];
    }
    CheckSum = (uint8_t) (sum & 0xFF);
    Order[3 + size] = CheckSum;
    Order[4 + size] = 0x1F;
    Order[5 + size] = 0x2F;
    ser.write(Order, size + 6);
}

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

void SendOrderCallBack(const std_msgs::UInt8MultiArray::ConstPtr &Data) {
    uint8_t Order[255];
    int i;
    for (i = 0; i < Data->data.size(); i++) {
        Order[i] = Data->data[i];
    }
    PrintROSUint8MultiArray(*Data, W);
    if (Data->data.size() == 1) {
        SendOrder_Single(Data->data[0]);
    } else {
        SendOrder_List(Order, (uint8_t) (Data->data.size()));
    }

}

int main(int argc, char **argv) {
    ros::init(argc, argv, "serialRW");

    ros::NodeHandle n;

    ros::Publisher serial_R = n.advertise<std_msgs::UInt8MultiArray>("serialR", 1000);

    ros::Subscriber serial_W = n.subscribe("serialW", 1000, SendOrderCallBack);

    ros::Rate loop_rate(50);
    try {
        ser.setPort("/dev/ttyUSB0");
        ser.setBaudrate(115200);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
        ser.open();
    }
    catch (serial::IOException &e) {
        ROS_ERROR_STREAM("Unable to open port ");
        return -1;
    }
    if (ser.isOpen()) {
        ROS_INFO_STREAM("Serial Port initialized");
    } else {
        return -1;
    }
    int count = 0;

    while (ros::ok()) {
        if (ser.available()) {
            std::string result;//接收区
            char temp[255];//暂时转为char 再转Uint8
            std_msgs::UInt8MultiArray val;
            int i, sersize;
            sersize = ser.available();
            result = ser.read(sersize);
            result.copy(temp, sersize, 0);
            for (i = 0; i < sersize; i++)
                val.data.push_back(temp[i]);
            serial_R.publish(val);
            PrintROSUint8MultiArray(val, R);
        }
        ros::spinOnce();
        loop_rate.sleep();
        ++count;
    }
    return 0;
}
