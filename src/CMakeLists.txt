cmake_minimum_required(VERSION 3.21)

project(scene_painter
  VERSION 1.0.0
  LANGUAGES CXX
  DESCRIPTION "Creates BMP pictures from scene files."
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(
    -Wall 
    -Wextra 
    -Wpedantic 
    -Werror 
    -g 
    -D_POSIX_C_SOURCE=201706L)
endif()

set(INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/scene
  ${CMAKE_CURRENT_SOURCE_DIR}/scene/core
  ${CMAKE_CURRENT_SOURCE_DIR}/scene/objects/include
  ${CMAKE_CURRENT_SOURCE_DIR}/parser
)


set(SCENE_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/scene/core/vec2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/scene/objects/src_files/hline.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/scene/objects/src_files/vline.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/scene/objects/src_files/rect.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/scene/objects/src_files/point.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/scene/objects/src_files/object.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/scene/objects/src_files/circle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/scene/scene.cpp
)

set(PARSER_SOURCES

)

set(MAIN_SOURCE
    ${SCENE_SOURCES}
    ${PARSER_SOURCES}
)


add_library(scene_painter
    ${MAIN_SOURCE}
)

target_include_directories(scene_painter PUBLIC
    ${INCLUDE_DIRS}
)




