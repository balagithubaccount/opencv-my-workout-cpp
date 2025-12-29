# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(BoxFilter)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(BoxFilter box_filter.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(BoxFilter ${OpenCV_LIBS})