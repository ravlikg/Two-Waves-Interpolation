cmake_minimum_required(VERSION 4.1)
project(interpolation)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
)

FetchContent_MakeAvailable(SFML)

add_executable(interpolation
        source/main.cpp
)
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/wave.frag
        ${CMAKE_CURRENT_BINARY_DIR}/wave.frag
        COPYONLY
)


target_link_libraries(interpolation
        PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)
