
#include"p_controller.h"


int main(int argc, char** argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle nodeHandle("~");

  std::string topic;
  int queue_size;
  double p;
  p_controller controller;

  if(!nodeHandle.getParam("topic", topic)){
    ROS_ERROR("COULD NOT FIND TOPIC PARAMETER!");
  }
  if(!nodeHandle.getParam("queue_size", queue_size)){
    ROS_ERROR("COULD NOT FIND QUEUE_SIZE PARAMETER!");
  }
  if(!nodeHandle.getParam("Kp", p)){
    ROS_ERROR("COULD NOT FIND Kp PARAMETER!");
  }
  if(!nodeHandle.getParam("speed", controller.output.linear.x)){
    ROS_ERROR("COULD NOT FIND speed PARAMETER!");
  }


  ros::Subscriber my_sub = nodeHandle.subscribe("/"+topic, queue_size, &p_controller::callback, &controller);
  ros::Publisher my_pub = nodeHandle.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  ros::Rate delay(5);

  while(nodeHandle.ok()){
    ros::spinOnce();
    controller.calculate(p);
    if(!nodeHandle.getParam("speed", controller.output.linear.x)){
      ROS_ERROR("COULD NOT FIND speed PARAMETER!");
    }
    my_pub.publish(controller.output);
    delay.sleep();
  }

  ros::spin();
  return 0;
}