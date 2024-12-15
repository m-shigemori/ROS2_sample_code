#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

class PublisherNode : public rclcpp::Node
{
public:
  PublisherNode() : Node("publisher_node"), count(0)
  {
    publisher = this->create_publisher<std_msgs::msg::Int32>("counter_topic", 10);
    timer = this->create_wall_timer(std::chrono::seconds(1), std::bind(&PublisherNode::publish_message, this));
  }

private:
  void publish_message()
  {
    auto message = std_msgs::msg::Int32();
    message.data = count;
    RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.data);
    publisher->publish(message);
    count++;
  }

  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher;
  rclcpp::TimerBase::SharedPtr timer;
  int count;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PublisherNode>());
  rclcpp::shutdown();
  return 0;
}
