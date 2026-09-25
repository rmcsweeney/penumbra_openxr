cmake_minimum_required (VERSION 3.25)
project (HPL)

set(HPL_VERSION_MAJOR 1)
set(HPL_VERSION_MINOR 0)


file(GLOB_RECURSE all_sources CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.c
)
list(FILTER all_sources EXCLUDE REGEX "/(win32\\.cpp|VideoStreamTheora\\.cpp)$")

add_library(HPL STATIC ${all_sources})

target_include_directories(HPL PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/../OALWrapper/include
		${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/include
)
target_link_libraries(HPL PUBLIC OALWrapper)

# TODO: here be 32 bit prebuilts
add_library(Newton STATIC IMPORTED)
set_target_properties(Newton PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/lib/linux/libNewton.a)

add_library(angelscript STATIC IMPORTED)
set_target_properties(angelscript PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/lib/linux/libangelscript.a)

add_library(SDLmain STATIC IMPORTED)
set_target_properties(SDLmain PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/lib/linux/libSDLmain.a)

