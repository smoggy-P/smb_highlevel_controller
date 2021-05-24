#include <ros/ros.h>
#include "sensor_msgs/LaserScan.h"
#include <algorithm>
#include"geometry_msgs/Twist.h"

class p_controller{
public:
    sensor_msgs::LaserScan input;
    geometry_msgs::Twist output;
    void calculate(const double &kp);
    void callback(const sensor_msgs::LaserScan::ConstPtr &msg);
};

void p_controller::calculate(const double& kp){
    double err = 0.0;
    err = min_element(this->input.ranges.begin(), this->input.ranges.end()) - ((this->input.ranges.begin()) + (this->input.ranges.end() - this->input.ranges.begin())/2);;
    ROS_INFO("ERROR: [%f]", err);
    this->output.angular.z = kp * err;
}
void p_controller::callback(const sensor_msgs::LaserScan::ConstPtr& msg){
    this->input = *msg;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle nodeHandle("~");

  std::string topic;
  int queue_size;
  double p;
  p_controller controller;
  controller.output.linear.x=0.5;

  if(!nodeHandle.getParam("topic", topic)){
    ROS_ERROR("COULD NOT FIND TOPIC PARAMETER!");
  }
  if(!nodeHandle.getParam("queue_size", queue_size)){
    ROS_ERROR("COULD NOT FIND QUEUE_SIZE PARAMETER!");
  }
  if(!nodeHandle.getParam("Kp", p)){
    ROS_ERROR("COULD NOT FIND Kp PARAMETER!");
  }


  ros::Subscriber my_sub = nodeHandle.subscribe("/"+topic, queue_size, &p_controller::callback, &controller);
  ros::Publisher my_pub = nodeHandle.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  ros::Rate delay(5);

  while(nodeHandle.ok()){
    ros::spinOnce();
    controller.calculate(p);
    controller.output.linear.x=0.5;
    my_pub.publish(controller.output);
    delay.sleep();
  }

  ros::spin();
  return 0;
}