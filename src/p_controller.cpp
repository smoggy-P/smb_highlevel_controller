#include"p_controller.h"

void p_controller::calculate(const double& kp){
    double err = 0.0;
    err = min_element(this->input.ranges.begin(), this->input.ranges.end()) - ((this->input.ranges.begin()) + (this->input.ranges.end() - this->input.ranges.begin())/2);;
    ROS_INFO("ERROR: [%f]", err);
    this->output.angular.z = kp * err;
}
void p_controller::callback(const sensor_msgs::LaserScan::ConstPtr& msg){
    this->input = *msg;
}