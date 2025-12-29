# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MedianBlur)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(MedianBlur median_blur.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(MedianBlur ${OpenCV_LIBS})