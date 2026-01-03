# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Shearing)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(Shearing shearing.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(Shearing ${OpenCV_LIBS})