# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(WritePCD)   # PCD Poind Cloud Data file with .pcd

# Find the OpenCV Package
find_package(PCL 1.11 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# Add the executable target
# add_executable(WritePCD write_pcd_file.cpp)
add_executable(WritePCD cloud_size.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(WritePCD ${PCL_LIBRARIES})