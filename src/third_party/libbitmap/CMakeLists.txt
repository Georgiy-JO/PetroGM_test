cmake_minimum_required(VERSION 3.7)

project(libbitmap)
add_definitions(-DOWN_MAKE_UNIQUE)

include_directories(${libbitmap_SOURCE_DIR})

add_library(libbitmap libbitmap.cpp)
target_compile_features(libbitmap PRIVATE cxx_deleted_functions)

# add_executable(example example.cpp)
# target_link_libraries(example libbitmap)
# target_compile_features(example PRIVATE cxx_deleted_functions)
