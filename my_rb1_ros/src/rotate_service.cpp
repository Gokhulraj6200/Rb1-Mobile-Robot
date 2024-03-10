#include "geometry_msgs/Twist.h"
#include "my_rb1_ros/Rotate.h"
#include "ros/init.h"
#include "ros/ros.h"
#include <cmath>
#include <nav_msgs/Odometry.h>

ros::Publisher vel_pub;
double current_angular_z = 0.0;

void odomCallback(const nav_msgs::Odometry::ConstPtr &msg) {
  double s = msg->pose.pose.orientation.w;
  double x = msg->pose.pose.orientation.x;
  double y = msg->pose.pose.orientation.y;
  double z = msg->pose.pose.orientation.z;

  // Calculate yaw angle from the quaternion
  current_angular_z = atan2(2.0 * (y * x + s * z), s * s + x * x - y * y - z * z);
}

bool rotateCallback(my_rb1_ros::Rotate::Request &req,
                    my_rb1_ros::Rotate::Response &res) {

  ROS_INFO("Service /rotate_robot has been called.");
  float required = req.degrees * (M_PI / 180);

  float actual = current_angular_z;

  float val = required + current_angular_z;

  if (val > M_PI) {
    val = val - (2 * M_PI);
  }

  geometry_msgs::Twist vel;

  ros::Rate loop_rate(2);

  while (ros::ok()) {


    if (fabs(val - current_angular_z) < 0.01) {
      vel.angular.z = 0;
      vel_pub.publish(vel);
      ros::spinOnce();
      loop_rate.sleep();

      break;
    }
    
    
    vel.angular.z = -0.5 * (val - current_angular_z);

    vel_pub.publish(vel);
    ros::spinOnce();
    loop_rate.sleep();
  }

  ROS_INFO(
      "Service execution completed. Current Degree: %f, Initial Degree: %f",
      current_angular_z * (180 / M_PI), actual * (180 / M_PI));
  res.result = "Rotation completed";
  return true;
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "rotate_server_node");
  ros::NodeHandle nh;

  vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ros::ServiceServer my_service =
      nh.advertiseService("/rotate_robot", rotateCallback);

  ROS_INFO("Service /rotate_robot is now Ready!");

  ros::Subscriber sub = nh.subscribe("/odom", 1, odomCallback);

  ros::spin();

  return 0;
}