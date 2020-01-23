#include "rclcpp/rclcpp.hpp"
#include <std_msgs/msg/float64.hpp>
 
void cbTopic1(const std_msgs::msg::Float64::SharedPtr msg)
{
  printf("received value is: %f\n", msg->data);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("minimal_subscriber");

  //auto sub = node->create_subscription<std_msgs::msg::Float64>("topic1", cbTopic1, rmw_qos_profile_default);
  auto sub = node->create_subscription<std_msgs::msg::Float64>("topic1",10, cbTopic1);

  rclcpp::spin(node);

  return 0;
}