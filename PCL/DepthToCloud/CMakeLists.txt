# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(DepthToCloud)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)
find_package(PCL 1.11 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# Add the executable target
add_executable(DepthToCloud depth_to_cloud.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(DepthToCloud
    ${PCL_LIBRARIES}
    ${OpenCV_LIBS}
)










