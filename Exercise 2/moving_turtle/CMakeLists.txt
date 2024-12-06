cmake_minimum_required(VERSION 3.8)
project(moving_turtle)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
# Corrigido para usar `size` sem os parênteses


find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(noQueEnviaString src/example.cpp)
ament_target_dependencies(noQueEnviaString rclcpp std_msgs)

add_executable(noQueEnviaMovimento src/moving_turtle.cpp)
ament_target_dependencies(noQueEnviaMovimento rclcpp std_msgs geometry_msgs)


install(TARGETS
  noQueEnviaString
  noQueEnviaMovimento
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
