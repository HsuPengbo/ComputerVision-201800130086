cmake_minimum_required(VERSION 3.17)
project(CV_E5)

set(CMAKE_CXX_STANDARD 20)
set(OpenCV_DIR C:/OpenCV-MinGW-Build)
set(CMAKE_EXE_LINKER_FLAGS "-static")

find_package(OpenCV REQUIRED)
add_executable(CV_E5 main.cpp E5.h)

target_link_libraries(CV_E5 ${OpenCV_LIBS})