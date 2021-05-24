#include <ros/ros.h>
#include "sensor_msgs/LaserScan.h"
#include <algorithm>
#include"geometry_msgs/Twist.h"

#pragma once

class p_controller{
public:
    sensor_msgs::LaserScan input;
    geometry_msgs::Twist output;
    void calculate(const double &kp);
    void callback(const sensor_msgs::LaserScan::ConstPtr &msg);
};

