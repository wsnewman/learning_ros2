//ros2_minimal_subscriber_v2.cpp, wsn

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include <std_msgs/msg/float64.hpp>
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
private:
  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
  void topic_callback(const std_msgs::msg::Float64::SharedPtr msg) const
  {
    RCLCPP_DEBUG(this->get_logger(),"debug message from topic_callback()");
    RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg->data);
    if (msg->data>0.010) {
      RCLCPP_WARN(this->get_logger(), "large-value warning: '%f'", msg->data);
    }
  }

public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<std_msgs::msg::Float64>(
      "topic1", 1, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
