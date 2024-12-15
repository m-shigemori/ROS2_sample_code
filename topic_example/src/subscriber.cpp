#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

class SubscriberNode : public rclcpp::Node
{
public:
  SubscriberNode() : Node("subscriber_node")
  {
    subscription_ = this->create_subscription<std_msgs::msg::Int32>("counter_topic", 10, [this](std_msgs::msg::Int32::SharedPtr msg)
                                                                    { this->topic_callback(msg); });
  }

private:
  void topic_callback(const std_msgs::msg::Int32::SharedPtr msg) const
  {
    RCLCPP_INFO(this->get_logger(), "Received: '%d'", msg->data);
  }

  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SubscriberNode>());
  rclcpp::shutdown();
  return 0;
}
