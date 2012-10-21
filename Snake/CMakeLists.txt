cmake_minimum_required(VERSION 2.7)

project(Snake)

set(SOURCE
  main.cpp
  Snake.cpp
  ../ConsoleLibrary/LinuxConsole.cpp
)

set(HEADERS
  Snake.h
  ../ConsoleLibrary/LinuxConsole.h
)

add_executable(Snake ${SOURCE} ${HEADERS})

target_link_libraries(Snake "ncurses")