cmake_minimum_required(VERSION 3.11)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Search for system Raylib
find_path(RAYLIB_INCLUDE_DIR raylib.h)
find_library(RAYLIB_LIBRARY raylib)

if(RAYLIB_INCLUDE_DIR AND RAYLIB_LIBRARY)
    include_directories(${RAYLIB_INCLUDE_DIR})
    set(RAYLIB_LIBRARIES ${RAYLIB_LIBRARY})
else()
    include_directories(external/Raylib/include)
    link_directories(external/Raylib/lib)
    set(RAYLIB_LIBRARIES raylib)
endif()

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(SnakeGame ${SOURCES})

target_link_libraries(SnakeGame ${RAYLIB_LIBRARIES})

if(APPLE)
    target_link_libraries(SnakeGame "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif(LINUX)
    target_link_libraries(SnakeGame m pthread dl rt)
endif()

set_target_properties(SnakeGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
