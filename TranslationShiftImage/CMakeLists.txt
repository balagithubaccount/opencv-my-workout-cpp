# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Translation)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(Translation translation_x_y.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(Translation ${OpenCV_LIBS})