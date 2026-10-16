cmake_minimum_required(VERSION 3.16)

project(LightweightVdiClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMake_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(LightweightVdiClient
	src/main.cpp
	src/MainWindow.cpp
	src/VdiSession.cpp
	src/ConfigLoader.cpp
	src/ProcessSpawner.cpp
	include/MainWindow.h
	include/VdiSession.h
	include/ConfigLoader.h
)
target_include_directories(LightweightVdiClient
	PRIVATE
		$(CMAKE_CURRENT_SOURCE_DIR)/include
)
target_link_libraries(LightweightVdiClient
	PRIVATE
		Qt6::Core
		Qt6::Widgets
)
