# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(PointCloudDistance)

# Find OpenCV Package
find_package(PCL 1.11 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# Add the executable target
add_executable(PointCloudDistance find_point_cloud_point_distance.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(PointCloudDistance ${PCL_LIBRARIES})