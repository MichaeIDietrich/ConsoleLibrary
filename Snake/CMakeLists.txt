cmake_minimum_required(VERSION 2.7)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

project(Snake)

set(SOURCE
  main.cpp
  Snake.cpp
  ../ConsoleLibrary/Menu.cpp
  ../ConsoleLibrary/LinuxConsole.cpp
)

set(HEADERS
  Snake.h
  ../ConsoleLibrary/Menu.h
  ../ConsoleLibrary/Console.h
)

add_executable(Snake ${SOURCE} ${HEADERS})

target_link_libraries(Snake "ncurses")