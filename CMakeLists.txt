cmake_minimum_required(VERSION 3.25)
project(PenumbraOpenXR C CXX)

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    MESSAGE(FATAL_ERROR "64 bit build required")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(VR_BACKEND "NONE" CACHE STRING "NONE, OPENVR, or OPENXR")
set_property(CACHE VR_BACKEND PROPERTY STRINGS NONE OPENVR OPENXR)
option(USE_CG "Use legacy Cg shaders" ON)
option(USE_SDL12 "Use SDL 1.2 API via sdl12-compat" ON)

add_subdirectory(OALWrapper)
add_subdirectory(HPL1Engine)
add_subdirectory(PenumbraOverture)

add_compile_options(-Wall -Wno-unused-parameter)