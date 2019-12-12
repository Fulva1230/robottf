//
// Created by fulva on 11/25/19.
//

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#define T1 3
#define T2 7
#define T3 10

int main(int argc, char **argv) {
    ros::init(argc, argv, "robot_tf_publisher");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/order", 20);

    ros::Rate rate{20};
    ros::Time begin{ros::Time::now()};
    ros::Duration cTime;
    while ((cTime = (ros::Time::now() - begin)) < ros::Duration{10, 0}) {
        geometry_msgs::Twist twist{};
        double cSec = cTime.toSec();
        if (cSec < T1) {
            twist.linear.x = 0 * (cSec - 3) / (0 - 3) + 300 * (cSec - 0) / (3 - 0);
            twist.linear.y = 300 * (cSec - 0) / 3;
            twist.angular.z = 0.1 * (cSec - 0) / 3;
        } else if (cSec < T2) {
            twist.linear.x = 300;
            twist.linear.y = 300;
            twist.angular.z = 0.1;
        } else {
            twist.linear.x = 300 * (cSec - 10) / (7 - 10);
            twist.linear.y = 300 * (cSec - 10) / (7 - 10);
            twist.angular.z = 0.1 * (cSec - 10) / (7 - 10);
        }
        pub.publish(twist);
        rate.sleep();
    }
    geometry_msgs::Twist twist;
    twist.linear.x = 0;
    twist.linear.y = 0;
    twist.angular.z = 0;
    pub.publish(twist);
}