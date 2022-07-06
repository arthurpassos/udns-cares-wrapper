cmake_minimum_required(VERSION 3.22)
project(udns_wrapper)

set(CMAKE_CXX_STANDARD 23)

add_executable(udns_wrapper main.cpp UDNSPTRResolver.cpp UDNSPTRResolver.h CARESPTRResolver.cpp CARESPTRResolver.h)

add_subdirectory(contrib)

target_link_libraries(udns_wrapper ch_contrib::udns c-ares)