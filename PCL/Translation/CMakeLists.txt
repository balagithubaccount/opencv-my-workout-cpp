# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Translation)

# Find the OpenCV Package
find_package(PCL 1.11 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# Add the executable target
add_executable(Translation pcl_translation.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(Translation ${PCL_LIBRARIES})