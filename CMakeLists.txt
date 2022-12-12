cmake_minimum_required(VERSION 3.24)
project(Socket_Programming)

set(CMAKE_CXX_STANDARD 14)

add_executable(Socket_Programming
        .idea/.gitignore
        .idea/modules.xml
        .idea/Socket-Programming.iml
        .idea/workspace.xml
        main.c socket_client.c socket_server.c)
