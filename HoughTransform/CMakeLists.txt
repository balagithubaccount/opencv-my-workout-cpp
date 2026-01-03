# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(HoughLine)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(HoughLine hough_line_transform.cpp)
# add_executable(HoughLine hough_line_transform.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(HoughLine ${OpenCV_LIBS})