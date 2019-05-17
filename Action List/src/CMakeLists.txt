# 요구 CMake 최소 버전
CMAKE_MINIMUM_REQUIRED ( VERSION 2.8 )
 
# 프로젝트 이름 및 버전
SET ( PROJECT_VERSION_MAJOR 0 )
SET ( PROJECT_VERSION_MINOR 1 )
 
# 빌드 형상(Configuration) 및 주절주절 Makefile 생성 여부
SET ( CMAKE_BUILD_TYPE Release )
SET ( CMAKE_VERBOSE_MAKEFILE true ) 
SET ( CMAKE_CXX_FLAGS "-std=c++11 -w")

ADD_COMPILE_OPTIONS ( -Wall )
 
ADD_EXECUTABLE( main main.cpp )
