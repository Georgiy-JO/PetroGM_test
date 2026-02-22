cmake_minimum_required(VERSION 3.10)
project(2DSceneRenderer_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(
    # -Wall 
    # -Wextra 
    # -Wpedantic 
    # -Werror 
    # -g 
    -D_POSIX_C_SOURCE=201706L)
endif()

add_subdirectory(src/third_party/libbitmap)

add_subdirectory(src)

add_executable(example example/main.cpp)

target_link_libraries(example PRIVATE scene_renderer_lib)

add_custom_command(
    TARGET example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/example/files
            $<TARGET_FILE_DIR:example>/files
    COMMENT "Копирование example/files в директорию сборки"
)