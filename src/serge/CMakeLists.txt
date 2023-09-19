cmake_minimum_required(VERSION 3.0)
project(Network)

add_executable(network client2)

#add_executable(network server.cpp)

#target_link_libraries(serge boost_system pthread)

target_link_libraries(network boost_system pthread)