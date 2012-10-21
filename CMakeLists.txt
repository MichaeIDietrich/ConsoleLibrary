cmake_minimum_required(VERSION 2.7)

project(ConsoleLibrary)

set(SOURCE
  main.cpp
  ConsoleLibrary/LinuxConsole.cpp
)

add_executable(ConsoleLibrary ${SOURCE})

target_link_libraries(ConsoleLibrary "ncurses")