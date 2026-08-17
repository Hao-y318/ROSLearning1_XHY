#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
class PublisherNode : public rclcpp::Node{
  private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    void publishMessage(){
        auto message = std_msgs::msg::String();
        message.data = "鸣潮，启动！";
        publisher_->publish(message);
        RCLCPP_INFO(this->get_logger(), "发布: %s", message.data.c_str());
    }
public:
    PublisherNode() : Node("publisher_node")
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>(
            "chatter", 10);

        timer_ = this->create_wall_timer(
            1s,
            std::bind(&PublisherNode::publishMessage, this));
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(
        std::make_shared<PublisherNode>());
    rclcpp::shutdown();
    return 0;
}