cmake_minimum_required(VERSION 3.22.1)
project(Socket_Programming)

set(CMAKE_CXX_STANDARD 14)

add_executable(Socket_Programming
        .idea/.gitignore
        .idea/modules.xml
        .idea/Socket-Programming.iml
        .idea/workspace.xml
        socket_client.c socket_server.c)
