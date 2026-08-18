#include "rclcpp/rclcpp.hpp"
#include "interface_pkg/msg/robot_pose_msg.hpp"


class SubscriberNode : public rclcpp::Node{
private:
    rclcpp::Subscription<interface_pkg::msg::RobotPoseMsg>::SharedPtr subscription_;
    
    void message_callback(const interface_pkg::msg::RobotPoseMsg::SharedPtr msg){
        RCLCPP_INFO(this->get_logger(), 
        "订阅: x=%f, y=%f, z=%f, roll=%f, pitch=%f, yaw=%f",
         msg->x, msg->y, msg->z, msg->angles.data[0], msg->angles.data[1], msg->angles.data[2]);
    }
public:
    SubscriberNode() : Node("subscriber_node")
    {
        subscription_ = this->create_subscription<interface_pkg::msg::RobotPoseMsg>(
            "chatter",
            10,
            std::bind(
              &SubscriberNode::message_callback, 
              this,
              std::placeholders::_1)
        );
    }

};


int main(int argc,char* argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<SubscriberNode>());
    rclcpp::shutdown();
    return 0;
}