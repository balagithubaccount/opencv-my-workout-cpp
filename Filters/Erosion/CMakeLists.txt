# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Erosion)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(Erosion erosion.cpp)
# add_executable(Erosion erosion_test.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(Erosion ${OpenCV_LIBS})