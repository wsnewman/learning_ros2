//v3 of minimal publisher example, wsn
// based on https://github.com/ros2/examples/blob/master/rclcpp/minimal_publisher/member_function.cpp

//typical headers
#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
//will again use std_msgs Float64
#include "std_msgs/msg/float64.hpp"

using namespace std::chrono_literals; //just so I can say "ms"

/* This example creates a derived class based on the "Node" base class, and it will be
   used to publish incremented values once per second*/
class MinimalPublisher : public rclcpp::Node
{
private:
  //member variables:
  rclcpp::TimerBase::SharedPtr timer_;  //a pointer to a timer object
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_; // a pointer to a publisher object
  std_msgs::msg::Float64 float_msg_ = std_msgs::msg::Float64(); //a message object to hold a double-precision value

  //member methods:  
  void timer_callback() //this function is to be called whenever an associated timer goes off
  {
    float_msg_.data += 0.001; //increment the value
    publisher_->publish(float_msg_); //then publish it
  }

public:
  MinimalPublisher()  //constructor
 : Node("minimal_publisher")  //initializer list: creates a shared pointer to a Node object,
                              // as defined in base class "Node"
                              // and assigns the name "minimal_publisher" to this node via
                              // the Node constructor
  {
    //instantiate a publisher and put a pointer to it in publisher_
    // uses the base-class method create_publisher.
    publisher_ = this->create_publisher<std_msgs::msg::Float64>("topic1", 1);
    //create a timer object that will invoke timer_callback() every 1000ms
    timer_ = this->create_wall_timer(
      1000ms, std::bind(&MinimalPublisher::timer_callback, this));
    //initialize the output value; alternatively, could have been done with initializer in constructor
    float_msg_.data=0.0;
  }
};  //end of class definition for MinimalPublisher

//main function, which instantiates and runs a MinimalPublisher object
int main(int argc, char * argv[])  //generic
{
  rclcpp::init(argc, argv);   //generic: Initialize communications via the rmw implementation 
                              //and set up a global signal handler.

  //the following line instantiates a MinimalPublisher node and will continue "spinning" until
  //this process is shut down
  //"spin()" takes an argument of a shared pointer to a node
  //void rclcpp::spin(rclcpp::node_interfaces::NodeBaseInterface::SharedPtr node_ptr)	
  //Creates a default single-threaded executor and spins the specified node.
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown(); //clean up before halting
  return 0;
}
