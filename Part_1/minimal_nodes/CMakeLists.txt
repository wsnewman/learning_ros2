cmake_minimum_required(VERSION 3.5)
project(minimal_nodes)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies; get these from the manifest package.xml automatically, instead of repeating them
# use these dependencies for compiling and linking
# if the package has an /include folder, these headers are installed and exported
# automatically generates msg or srv interfaces, if msg or srv directories exist
# installs libraries and executables in default locations
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

# setup targets
ament_auto_add_executable(ros2_sleepy_minimal_publisher_v1 src/ros2_sleepy_minimal_publisher_v1.cpp)
ament_auto_add_executable(ros2_sleepy_minimal_publisher_v2 src/ros2_sleepy_minimal_publisher_v2.cpp)
ament_auto_add_executable(ros2_sleepy_minimal_publisher_v3 src/ros2_sleepy_minimal_publisher_v3.cpp)
ament_auto_add_executable(ros2_minimal_subscriber_v1 src/ros2_minimal_subscriber_v1.cpp)
ament_auto_add_executable(ros2_minimal_subscriber_v2 src/ros2_minimal_subscriber_v2.cpp)
#ament_auto_add_library(foo_lib src/lib.cpp)

#the following seems to not be necessary with ament_auto
#install(TARGETS
#  wsn_ros2_sleepy_minimal_publisher_v1
#  wsn_ros2_sleepy_minimal_publisher_v2
#  wsn_ros2_sleepy_minimal_publisher_v3
#  DESTINATION lib/${PROJECT_NAME}
#)
#one of the following lines DOES seem to be necessary--not documented
#ament_package() #seems still need this, even with ament_auto
ament_auto_package() #this also seems to work

