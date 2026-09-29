file(GLOB newton_sources CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/physics/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/newton/*.cpp)
list(FILTER newton_sources EXCLUDE REGEX "physics/dgVehicleConstraint\\.cpp$")

add_library(newton STATIC
        ${newton_sources}
)

target_include_directories(newton PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/newton
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/core
        ${CMAKE_CURRENT_SOURCE_DIR}/physics
)
target_compile_options(newton PRIVATE -O2 -w)

find_package(Threads REQUIRED)
target_link_libraries(newton PUBLIC Threads::Threads)