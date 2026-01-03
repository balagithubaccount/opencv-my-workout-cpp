# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Scale)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(Scale scaling.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(Scale ${OpenCV_LIBS})