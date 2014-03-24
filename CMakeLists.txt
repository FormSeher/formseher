cmake_minimum_required(VERSION 2.8)
project(formseher)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(BINARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# include(ExternalProject)
# ExternalProject_Add(
# 	gtest_EXTERNAL_PROJECT
# 	PREFIX vendor/gtest
# 	URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
# 	INSTALL_COMMAND ""
# 	LOG_UPDATE 0
# 	LOG_TEST 0
# 	LOG_INSTALL 0
# )

add_subdirectory( ./vendor/lsd )

find_package( OpenCV REQUIRED )

set(
	SOURCES
	src/main.cpp
)

include_directories(./include)
include_directories(./vendor/lsd/include)
link_directories(${LIBRARY_OUTPUT_PATH})

add_executable(formseher ${SOURCES})
add_dependencies(formseher lsd)
target_link_libraries(formseher lsd gtest pthread ${OpenCV_LIBS})
