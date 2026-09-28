file(GLOB as_sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_library(angelscript STATIC
        ${as_sources}
        add_on/scriptstdstring/scriptstdstring.cpp
        add_on/scriptstdstring/scriptstdstring_utils.cpp
        add_on/scriptarray/scriptarray.cpp
        add_on/scripthelper/scripthelper.cpp
)

target_include_directories(angelscript PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/add_on
)
target_compile_definitions(angelscript PUBLIC AS_MAX_PORTABILITY)