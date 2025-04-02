cmake_minimum_required(VERSION 3.8)
project(nameof VERSION 0.1.3)

add_library(nameof INTERFACE)
set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)
target_include_directories(
	nameof INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_library(nameof::nameof ALIAS nameof)
