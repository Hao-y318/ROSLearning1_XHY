#include "rclcpp/rclcpp.hpp"
#include "interface_pkg/msg/robot_pose_msg.hpp"


using namespace std::chrono_literals;


class PublisherNode : public rclcpp::Node{
  public:
  PublisherNode() : Node("publisher_node")
  {
    publisher_ = this->create_publisher<interface_pkg::msg::RobotPoseMsg>(
      "chatter", 10);
      
      timer_ = this->create_wall_timer(
        1s,
        std::bind(&PublisherNode::publishMessage, this));
      }
  private:
        rclcpp::Publisher<interface_pkg::msg::RobotPoseMsg>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        float x_=0.0;
        float y_=0.0;
        float z_=0.0;
    
        float roll_=0.0;
        float pitch_=0.0;
        float yaw_=0.0;
        void publishMessage(){
            auto message = interface_pkg::msg::RobotPoseMsg();
            message.x =x_;
            message.y =y_;
            message.z =z_;
            
            message.angles.data.resize(3);

            message.angles.data[0]=roll_;
            message.angles.data[1]=pitch_;
            message.angles.data[2]=yaw_;
      
            publisher_->publish(message);
      
            RCLCPP_INFO(this->get_logger(), 
            "x: %f, y: %f, z: %f,roll: %f, pitch: %f, yaw: %f", 
            message.x,message.y,message.z,
            message.angles.data[0],message.angles.data[1],message.angles.data[2]
          );
      
            x_ +=0.1;
            y_ +=0.1;
            z_ +=0.1;
      
            roll_ +=0.1;
            pitch_+= 0.1;
            yaw_ +=0.1;
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