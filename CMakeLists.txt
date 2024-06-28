cmake_minimum_required(VERSION 3.23)
project(allocators)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
find_package(nlohmann_json 3.11.2 REQUIRED)
add_executable(allocators
        alloc_border
        alloc_buddies
        alloc_list
        alloc_new_delete
        logger
        memory.cpp
        memory.h
        typename_holder.h
        main.cpp)
target_link_libraries(allocators PRIVATE nlohmann_json::nlohmann_json)