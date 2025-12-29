# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(FirstOpenCV)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(FirstCV first_opencv.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(FirstCV ${OpenCV_LIBS})