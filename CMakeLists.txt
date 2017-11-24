cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/Kustov-Ilya/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "affff3092b27bdc5cbb96fca80c37c2673475886"
)

project(demo)

project(demo)

hunter_add_package(print)
find_package(print)

hunter_add_package(Boost COMPONENTS system filesystem program_options)
find_package(Boost CONFIG REQUIRED system filesystem program_options)

add_executable(demo ${CMAKE_CURRENT_SOURCE_DIR}/sources/demo.cpp)
target_link_libraries(demo print Boost::system  Boost::filesystem  Boost::program_options)

install(TARGETS demo RUNTIME DESTINATION bin)
