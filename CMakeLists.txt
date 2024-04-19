cmake_minimum_required(VERSION 3.10)
project(base_cpp)

include_directories(
  "${CMAKE_SOURCE_DIR}/external/sdl2/include/SDL2"
  "${CMAKE_SOURCE_DIR}/external/sdl2_ttf/include/SDL2"
)

add_executable(a.out src/entry.cpp)

target_link_libraries(a.out 
  "${CMAKE_SOURCE_DIR}/external/sdl2/lib/libSDL2.a"
  "${CMAKE_SOURCE_DIR}/external/sdl2_ttf/lib/libSDL2_ttf.a"
  )
