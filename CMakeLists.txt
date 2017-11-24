cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/n0k8t/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "f411b045dd72a16eb4cd9ff10abe59a49526f490"
)

project(demo)

hunter_add_package(print)
hunter_add_package(Boost COMPONENTS program_options)
find_package(print)
find_package(Boost CONFIG REQUIRED program_options)

add_executable(demo ${CMAKE_CURRENT_SOURCE_DIR}/sources/demo.cpp)
target_link_libraries(demo print)

install(TARGETS demo RUNTIME DESTINATION bin)
