//
// Created by fulva on 10/18/19.
//

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

tf::Quaternion getQuaternion();

tf::Vector3 getPosition();

int main(int argc, char **argv) {
    ros::init(argc, argv, "robot_tf_publisher");
    ros::NodeHandle n;

    ros::Rate r(100);

    tf::TransformBroadcaster broadcaster;

    while (n.ok()) {
        broadcaster.sendTransform(
                tf::StampedTransform(
                        tf::Transform(getQuaternion(), getPosition()),
                        ros::Time::now(), "base_link", "odem"));
        r.sleep();
    }
}

tf::Vector3 getPosition() {

}

tf::Quaternion getQuaternion() {

}
