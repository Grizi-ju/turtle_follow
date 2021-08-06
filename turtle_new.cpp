#include <ros/ros.h>
#include <turtlesim/Spawn.h>
 
int main(int argc, char** argv)
{
    int i;
    if (argc < 2)
    {
        ROS_ERROR("Turtle's name can't be empty");
        return -1;
    }
    ros::init(argc, argv, "turtle_new");
    ros::NodeHandle node;
    ros::service::waitForService("spawn");
    ros::ServiceClient add_turtle_client = node.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn srv_msg;
    for (i = 1; i < argc; ++i)
    {
        srv_msg.request.x = i;
        srv_msg.request.y = i;
        srv_msg.request.theta = 0;
        srv_msg.request.name = *(argv + i);
        add_turtle_client.call(srv_msg);
    }
    return 0;
}


