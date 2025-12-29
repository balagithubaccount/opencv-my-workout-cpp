# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(AllFilters)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(AllFilters all_filters.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(AllFilters ${OpenCV_LIBS})