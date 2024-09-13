cmake_minimum_required(VERSION 3.10)
project(ChatServer)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system)

include_directories(${Boost_INCLUDE_DIR})

add_executable(ChatServer src/main.cpp src/chat_server.cpp)

target_link_libraries(ChatServer ${Boost_LIBRARIES} pthread)

