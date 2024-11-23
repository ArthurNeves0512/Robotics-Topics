#include "chrono"                  //this is used for time,
#include "functional"              //irá servir para a funcao bind
#include "rclcpp/rclcpp.hpp"       //biblioteca do ros
#include "std_msgs/msg/string.hpp" //menssagem que iremos enviar do tipo string
#include <memory> //para usar o SharedPtr e deixar o ros cuidar do gerenciamento de memoria
class StringNode : public rclcpp::Node {
  // Herda da classe abstrata Node e entao precisamos implementar o construtor
public:
  StringNode() : Node("publisher_node_string"), count_(0) {
    // o publisher que criamos irá escrever nesse topico e pode deixar até
    // 10msgs na fila
    publisher = this->create_publisher<std_msgs::msg::String>(
        "topicoQueEnviaString", 10);
    // de 2 em 2 segundos, ele chama essa funcao de enviar a menssagem
    timer = this->create_wall_timer(std::chrono::milliseconds(2000),
                                    std::bind(&StringNode::sendMessage, this));
  };

private:
  unsigned long count_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
  rclcpp::TimerBase::SharedPtr timer;
  void sendMessage() {
    auto message = std_msgs::msg::String();
    message.data =
        "I already Send this message " + std::to_string(count_) + " times";

    // irá printar isso no terminal quando a gente rodar o ros2 run
    // <nomeDoPacote> <nomeDoExecutavel de saída que está no CmakeLists.txt>
    RCLCPP_INFO(this->get_logger(), "Publishing in logge %s the value %ld",
                message.data.c_str(), count_);
    publisher->publish(message);
  }
};
int main(int argc, char *argv[]) {
  // inicia o ros
  rclcpp::init(argc, argv);
  // fala pro ros rodar esse nosso nó
  rclcpp::spin(std::make_shared<StringNode>());
  // se der crtl C no terminal, parar a execução.
  rclcpp::shutdown();
  return 0;
}
