//
// Created by fulva on 10/18/19.
//

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

#define HEIGHT 0.2
#define OFFSET_Y 0.28

int main(int argc, char **argv) {
    ros::init(argc, argv, "robot_tf_firstlink");
    ros::NodeHandle n;

    ros::Rate r(1);

    tf::TransformBroadcaster broadcaster;

    while (n.ok()) {
        broadcaster.sendTransform(
                tf::StampedTransform(
                        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0, OFFSET_Y, HEIGHT)),
                        ros::Time::now(), "base_link", "camera_depth_frame"));
        r.sleep();
    }
}

