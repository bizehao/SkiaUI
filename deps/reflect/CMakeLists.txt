cmake_minimum_required(VERSION 3.8)
project(reflect VERSION 0.1.3)

add_library(reflect INTERFACE)
set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)
target_include_directories(
	reflect INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_library(reflect::reflect ALIAS reflect)
