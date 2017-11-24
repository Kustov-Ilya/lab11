cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/Kustov-Ilya/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "affff3092b27bdc5cbb96fca80c37c2673475886"
)

project(demo)

hunter_add_package(print)
find_package(print)

find_package( Boost REQUIRED COMPONENTS program_options)
include_directories( ${Boost_INCLUDE_DIRS} )



add_executable(demo ${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp)
target_link_libraries(demo print)
target_link_libraries( demo ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_REGEX_LIBRARY} )


install(TARGETS demo RUNTIME DESTINATION bin)
