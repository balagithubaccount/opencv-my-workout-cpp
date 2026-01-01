# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MorphOperation)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(MorphOperation morph_operation.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(MorphOperation ${OpenCV_LIBS})