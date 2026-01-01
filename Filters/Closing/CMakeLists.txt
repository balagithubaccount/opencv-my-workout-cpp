# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Closing)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(Closing closing.cpp)
# add_executable(Closing closing_test.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(Closing ${OpenCV_LIBS})