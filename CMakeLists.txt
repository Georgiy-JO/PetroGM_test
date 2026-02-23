cmake_minimum_required(VERSION 3.10)
project(2DSceneRenderer_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(
    -Wall 
    -Wextra 
    # -Werror     # libbtmap codebase has issues in lines 33 (memset) and 185 (anonymous structure)
    -Wpedantic
    -g 
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
    COMMENT "Copy example/files to the active directory"
)

find_program(CLANG_FORMAT_EXE
    NAMES clang-format clang-format-20 clang-format-14 clang-format-13
    DOC "Path to clang-format executable"
)

if(CLANG_FORMAT_EXE)
    set(CLANG_FILE 
        "${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
        )
    file(GLOB_RECURSE CHECKABLE_FILES
        LIST_DIRECTORIES false
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    )
    list(FILTER CHECKABLE_FILES EXCLUDE REGEX "src[\\/]+third_party")
    
    add_custom_target(style_check
        COMMAND ${CLANG_FORMAT_EXE}
            --style=file:${CLANG_FILE}
            -n
            ${CHECKABLE_FILES}
        COMMENT "Checking files' style according to Google style set in .clang-format file..."
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )
    add_custom_target(style_make
        COMMAND ${CLANG_FORMAT_EXE}
            --style=file:${CLANG_FILE}
            -i
            ${CHECKABLE_FILES}
        COMMENT "Fixing files' style according to Google style set in .clang-format file..."
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )
else()        
    message(WARNING "clang-format not found! Code style targets unavailable.")
endif()
