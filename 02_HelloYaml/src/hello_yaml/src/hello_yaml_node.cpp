#include<rclcpp/rclcpp.hpp>
#include<std_msgs/msg/float32.hpp>

using namespace std::chrono_literals;

class HelloYamlNode : public rclcpp::Node
{
public:
    HelloYamlNode() : Node("hello_yaml_node")
    {
        //参数声明
        this->declare_parameter<double>("x", 0.0);
        this->declare_parameter<double>("y", 0.0);
        this->declare_parameter<double>("z", 0.0);

        
        this->get_parameter("x", x_);
        this->get_parameter("y", y_);
        this->get_parameter("z", z_);
        
        RCLCPP_INFO(
          this->get_logger(),
          "x=%f, y=%f, z=%f",
          x_, y_, z_);
          
          //创建发布者
          pub_x_ = this->create_publisher<std_msgs::msg::Float32>("x", 10);
          pub_y_ = this->create_publisher<std_msgs::msg::Float32>("y", 10);
          pub_z_ = this->create_publisher<std_msgs::msg::Float32>("z", 10);

          //创建定时器
          timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1000), std::bind(&HelloYamlNode::publish_message, this));

        }
        
        
private:
    void publish_message(){
      std_msgs::msg::Float32 msg_x;
      std_msgs::msg::Float32 msg_y;
      std_msgs::msg::Float32 msg_z;

      msg_x.data = static_cast<float>(x_);
      msg_y.data = static_cast<float>(y_);
      msg_z.data = static_cast<float>(z_);

      pub_x_->publish(msg_x);
      pub_y_->publish(msg_y);
      pub_z_->publish(msg_z);

      RCLCPP_INFO(
          this->get_logger(),
          "发布 x: %f, y: %f, z: %f",
          msg_x.data, 
          msg_y.data, 
          msg_z.data);
    }

    double x_;
    double y_;
    double z_;

    rclcpp::TimerBase::SharedPtr timer_;

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pub_x_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pub_y_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pub_z_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<HelloYamlNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
