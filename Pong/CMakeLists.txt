cmake_minimum_required(VERSION 2.7)

project(Pong)

set(SOURCE
  main.cpp
  Ball.cpp
  ../ConsoleLibrary/LinuxConsole.cpp
)

set(HEADERS
  Ball.h
  ../ConsoleLibrary/Console.h
  ../ConsoleLibrary/LinuxConsole.h
)


add_executable(Pong ${SOURCE} ${HEADERS})

target_link_libraries(Pong "ncurses")