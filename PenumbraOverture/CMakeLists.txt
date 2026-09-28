cmake_minimum_required (VERSION 3.25)
project(Overture)


file(GLOB all_sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(Overture ${all_sources})

set_target_properties(Overture PROPERTIES
    OUTPUT_NAME overture
    SUFFIX .bin)

target_link_libraries(Overture PRIVATE HPL OALWrapper Newton Cg CgGL ogg vorbis vorbisfile openal SDL SDL_ttf SDL_image)
