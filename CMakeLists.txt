cmake_minimum_required (VERSION 2.6)
project (adaptive-thresholding)

set(CMAKE_CXX_FLAGS "-std=c++11 -O3")
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


add_executable(adaptive-thresholding src/main.cpp
                                     src/adaptive_thresholding.cpp
                                     src/mean_adaptive_thresholding.cpp)
target_link_libraries(adaptive-thresholding LINK_PUBLIC ${OpenCV_LIBS})