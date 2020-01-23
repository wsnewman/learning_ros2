//wsn 1/17/2020: ros2 version of minimal publisher
//  this is not the preferred style, but is closest to ROS1
//  see wsn_ros2_sleepy_minimal_publisher2.cpp for more modern version

//#include <chrono>  //these two #includes are a new requirement; boilerplate
//#include <memory>

//#include "rclcpp/rclcpp.hpp" //replaces #include <ros/ros.h>
#include <rclcpp/rclcpp.hpp> //replaces #include <ros/ros.h>
#include <std_msgs/msg/float64.hpp> //replaces #include <std_msgs/Float64.h>; note need addl /msg/ drill-down

//#include "std_msgs/msg/float64.hpp" //replaces #include <std_msgs/Float64.h>; note need addl /msg/ drill-down
                                   // and " " instead of < >...will search per compiler directives
                                   // on my installation, found here: /opt/ros/eloquent/include/std_msgs/msg/*.hpp
                                   //note: *.hpp vs *.h is arbitrary; hpp implies C++ header, but not enforced
                                   //note: no longer Float64, but lower-case float64




//int main(int argc, char * argv[])...this still works, but is old style
int main(int argc, char **argv) {
    rclcpp::init(argc, argv); //ros::init(argc, argv, "minimal_publisher2"); //ros2: do not name node here; can have more than 1 node
    rclcpp::Node node("minimal_publisher"); //ros::NodeHandle n;
    //better: use a shared pointer
    //auto node = rclcpp::Node::make_shared("minimal_publisher"); // pointer to a node is created here; has
     //methods formerly invoked via a separate nodeHandle
     //this is where we define the node's name
     //alt: std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("minimal_publisher");
     //Creating a node is done by calling the constructor of the rclcpp::Node class
    
    //try this: 
     //auto  my_publisher_object_ptr = node.create_publisher<std_msgs::msg::Float64>("topic1",1);
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr   my_publisher_object_ptr = node.create_publisher<std_msgs::msg::Float64>("topic1",1);

     //this does not work:  rclcpp::Publisher  my_publisher_object = node->advertise<std_msgs::Float64>("topic1", 1);
     //  auto chatter_pub = node->create_publisher<std_msgs::msg::String>("chatter",1000);
     //rclcpp::Rate loop_rate(10);

    //rclcpp::Publisher  my_publisher_object = node->advertise<std_msgs::Float64>("topic1", 1);
    //auto chatter_pub = node->create_publisher<std_msgs::msg::String>("chatter", custom_qos_profile);
    //ros::Publisher my_publisher_object = n.advertise<std_msgs::Float64>("topic1", 1);
    //"topic1" is the name of the topic to which we will publish
    // the "1" argument says to use a buffer size of 1; could make larger, if expect network backups
    
    std_msgs::msg::Float64 input_float;
    //std_msgs::Float64 input_float; //create a variable of type "Float64", 
    // as defined in: /opt/ros/indigo/share/std_msgs
    // any message published on a ROS topic must have a pre-defined format, 
    // so subscribers know how to interpret the serialized data transmission
   
    rclcpp::Rate naptime(1.0);
    
    //rclcpp::WallRate loop_rate(500ms);
   //ros::Rate naptime(1.0); //create a ros object from the ros “Rate” class; 
   //set the sleep timer for 1Hz repetition rate (arg is in units of Hz)

    input_float.data = 0.0;
    
    // do work here in infinite loop (desired for this example), but terminate if detect ROS has faulted
    //while (ros::ok()) 
    while (rclcpp::ok()) {
    
        // this loop has no sleep timer, and thus it will consume excessive CPU time
        // expect one core to be 100% dedicated (wastefully) to this small task
        input_float.data = input_float.data + 0.001; //increment by 0.001 each iteration
        my_publisher_object_ptr->publish(input_float);
        //my_publisher_object.publish(input_float); // publish the value--of type Float64-- 
        //to the topic "topic1"
	//the next line will cause the loop to sleep for the balance of the desired period 
        // to achieve the specified loop frequency 
        	naptime.sleep(); 
                
        //Spinning (i.e., letting the communications system process any pending incoming/outgoing messages) is different in that the call now takes the node as an argument:
        //    ros::spinOnce();
        //        rclcpp::spin_once();
        //        auto node_ptr = &node;
        //  rclcpp::spin_some(node_ptr); //needs a shared pointer to node
    

    }
    return 0;
}


