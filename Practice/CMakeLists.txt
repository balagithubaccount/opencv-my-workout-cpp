# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Practice)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(Practice practice.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(Practice ${OpenCV_LIBS})