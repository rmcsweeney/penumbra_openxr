cmake_minimum_required (VERSION 3.25)
project (HPL)

set(HPL_VERSION_MAJOR 1)
set(HPL_VERSION_MINOR 0)


file(GLOB_RECURSE all_sources CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.c
)
list(FILTER all_sources EXCLUDE REGEX "/(win32\\.cpp|VideoStreamTheora\\.cpp)$")
list(FILTER all_sources EXCLUDE REGEX "/sources/vr/VRBackend(OpenVR|OpenXR)\\.cpp$")

file(GLOB_RECURSE all_headers CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

add_library(HPL STATIC ${all_sources} ${all_headers})

#temp include to fix GLee issue of glx.h including new versions, this uses GLee 5.4
target_compile_definitions(HPL PUBLIC GL_GLEXT_LEGACY GLX_GLXEXT_LEGACY)

target_include_directories(HPL PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/include
)
target_link_libraries(HPL PUBLIC OALWrapper)

if (VR_BACKEND STREQUAL "OPENVR")
    target_sources(HPL PRIVATE sources/vr/VRBackendOpenVR.cpp)
    target_include_directories(HPL PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/openvr-1.0.2/headers)
    target_compile_definitions(HPL PUBLIC HPL_VR_OPENVR=1)
endif ()

# TODO: here be 32 bit prebuilts
add_library(Newton STATIC IMPORTED)
set_target_properties(Newton PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/lib/linux/libNewton.a)

add_library(angelscript STATIC IMPORTED)
set_target_properties(angelscript PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/lib/linux/libangelscript.a)

