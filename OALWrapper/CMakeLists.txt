cmake_minimum_required (VERSION 3.25)
project (OALWrapper)

set(OALWrapper_VERSION_MAJOR 1)
set(OALWrapper_VERSION_MINOR 0)


file(GLOB_RECURSE all_sources CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp
)

add_library(OALWrapper STATIC ${all_sources})

target_include_directories(OALWrapper PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_SOURCE_DIR}/dependencies/include
)