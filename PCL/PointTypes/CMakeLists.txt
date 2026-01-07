# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(PointType)   # PCD Poind Cloud Data file with .pcd

# Find the OpenCV Package
find_package(PCL 1.11 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# Add the executable target
add_executable(PointType point_types.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(PointType ${PCL_LIBRARIES})