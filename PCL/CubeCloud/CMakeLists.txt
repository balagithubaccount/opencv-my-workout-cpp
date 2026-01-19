# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(CubeCloud)

# Find OpenCV Package
find_package(PCL 1.11 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# Add the executable target
# add_executable(CubeCloud generate_cube_cloud.cpp)
# add_executable(CubeCloud rgb_cube_pyramid.cpp)
# add_executable(CubeCloud rgb_cube_pyramid_ptr.cpp)  
add_executable(CubeCloud rgb_cube_pyramid_points.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(CubeCloud ${PCL_LIBRARIES})