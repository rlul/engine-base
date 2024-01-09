cmake_minimum_required(VERSION 3.10)

project(glad)

add_library(glad STATIC include/glad/glad.h src/glad.c)

if (NOT MSVC)
	set_property(TARGET glad PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

target_include_directories(glad PUBLIC include/)
