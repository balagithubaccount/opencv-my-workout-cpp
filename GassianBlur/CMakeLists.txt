# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(GaussianBlur)

# Find the OpenCV Package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(GaussianBlur gaussian_filter.cpp)
# add_executable(GaussianBlur gaussian_test.cpp)

# Link the executable with the OpenCV Libraries
target_link_libraries(GaussianBlur ${OpenCV_LIBS})