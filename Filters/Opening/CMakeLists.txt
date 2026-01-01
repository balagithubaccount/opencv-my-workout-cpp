# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Opening)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(Opening opening.cpp)
# add_executable(Opening opening_test.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(Opening ${OpenCV_LIBS})