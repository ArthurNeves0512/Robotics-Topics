#include "chrono"
#include "functional"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int8.h"
#include <chrono>
#include <cstdio>
#include <geometry_msgs/msg/detail/twist__struct.hpp>
#include <memory>
#include <ratio>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>

class MovingTurle : public rclcpp::Node {

public:
  MovingTurle() : Node("moving_node_turtle") {
    squareMovimentPublisher = this->create_publisher<geometry_msgs::msg::Twist>(
        "turtlesim1/turtle1/cmd_vel", 10);
    circleMovimentPublisher = this->create_publisher<geometry_msgs::msg::Twist>(
        "turtlesim2/turtle1/cmd_vel", 2);
    timer1 =
        this->create_wall_timer(std::chrono::milliseconds(2000),
                                std::bind(&MovingTurle::movingInSquare, this));
    timer2 =
        this->create_wall_timer(std::chrono::milliseconds(200),
                                std::bind(&MovingTurle::movingInCircle, this));
  };

private:
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr
      squareMovimentPublisher;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr
      circleMovimentPublisher;
  rclcpp::TimerBase::SharedPtr timer1;
  rclcpp::TimerBase::SharedPtr timer2;

  void movingInCircle() {
    geometry_msgs::msg::Twist msg;
    msg.linear.x = 1;
    msg.linear.y = 1;
    msg.angular.z = 1;
    circleMovimentPublisher->publish(msg);
    rclcpp::sleep_for(std::chrono::seconds(2));
  }

  void movingInSquare() {
    geometry_msgs::msg::Twist msg;
    RCLCPP_INFO(this->get_logger(), "Andei para cima");
    msg.linear.set__x(0);
    msg.linear.set__y(1);

    squareMovimentPublisher->publish(msg);
    rclcpp::sleep_for(std::chrono::seconds(2));

    msg.linear.set__x(1);
    msg.linear.set__y(0);

    RCLCPP_INFO(this->get_logger(), "Andei para direita");
    squareMovimentPublisher->publish(msg);

    rclcpp::sleep_for(std::chrono::seconds(2));
    msg.linear.set__x(0);
    msg.linear.set__y(-1);

    RCLCPP_INFO(this->get_logger(), "Andei para baixo");
    squareMovimentPublisher->publish(msg);

    rclcpp::sleep_for(std::chrono::seconds(2));
    msg.linear.set__x(-1);
    msg.linear.set__y(0);

    RCLCPP_INFO(this->get_logger(), "Andei para esquerda");
    squareMovimentPublisher->publish(msg);

    rclcpp::sleep_for(std::chrono::seconds(2));
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MovingTurle>());
  rclcpp::shutdown();
  return 0;
}
