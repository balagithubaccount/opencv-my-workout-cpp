# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(ShapeDet)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(ShapeDet shape_detect.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(ShapeDet ${OpenCV_LIBS})