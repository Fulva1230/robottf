//
// Created by fulva on 10/18/19.
//

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

class TfPubFromOdom {
public:
    TfPubFromOdom(tf::TransformBroadcaster &broadcaster) : broadcaster(broadcaster) {

    }

    void operator()(const nav_msgs::OdometryConstPtr &odomMsg) {
        tf::Quaternion oriantation{
                odomMsg->pose.pose.orientation.x,
                odomMsg->pose.pose.orientation.y,
                odomMsg->pose.pose.orientation.z,
                odomMsg->pose.pose.orientation.w
        };
        tf::Vector3 odomPose{
                odomMsg->pose.pose.position.x,
                odomMsg->pose.pose.position.y,
                odomMsg->pose.pose.position.z
        };
        tf::StampedTransform stampedTransform{
                tf::Transform{
                        oriantation,
                        odomPose
                },
                odomMsg->header.stamp,
                odomMsg->header.frame_id,
                odomMsg->child_frame_id
        };
        broadcaster.sendTransform(stampedTransform);
    }

private:
    tf::TransformBroadcaster &broadcaster;
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "robot_tf_publisher");
    ros::NodeHandle nodeHandle;

    tf::TransformBroadcaster broadcaster;
    TfPubFromOdom tfPubFromOdom{broadcaster};
    ros::Subscriber odomSub = nodeHandle.subscribe<nav_msgs::Odometry>("odom", 10, tfPubFromOdom);
    ros::spin();

}

