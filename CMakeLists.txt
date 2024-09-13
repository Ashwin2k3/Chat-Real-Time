cmake_minimum_required(VERSION 3.10)
project(ChatServer)

set(CMAKE_CXX_STANDARD 17)

# Specify the path to the Boost library
find_package(Boost REQUIRED COMPONENTS system)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include ${Boost_INCLUDE_DIR})

# Add executable target
add_executable(ChatServer src/main.cpp src/chat_server.cpp)

# Link libraries
target_link_libraries(ChatServer ${Boost_LIBRARIES} pthread)

