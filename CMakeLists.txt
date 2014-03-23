cmake_minimum_required(VERSION 2.8)
project(formseher)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")

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

# include_directories( ./vendor/gtest/src/gtest_EXTERNAL_PROJECT/include )
# link_directories( ${PROJECT_SOURE_DIR}/vendor/gtest/src/gtest_EXTERNAL_PROJECT-build )

find_package( OpenCV REQUIRED )

set(
	SOURCES
	src/main.cpp
)

include_directories( ./include )


add_executable(formseher ${SOURCES})
target_link_libraries(formseher gtest pthread ${OpenCV_LIBS})
