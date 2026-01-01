# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Dilation)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(Dilation dilation.cpp)
# add_executable(Dilation dilation_test.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(Dilation ${OpenCV_LIBS})