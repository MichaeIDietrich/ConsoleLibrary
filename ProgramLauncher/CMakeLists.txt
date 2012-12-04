cmake_minimum_required(VERSION 2.7)

project(Launcher)

set(SOURCE
  main.cpp
  ../ConsoleLibrary/Menu.cpp
  ../ConsoleLibrary/LinuxConsole.cpp
)

set(HEADERS
  ../ConsoleLibrary/Menu.h
  ../ConsoleLibrary/Console.h
  ../ConsoleLibrary/LinuxConsole.h
)

add_executable(Launcher ${SOURCE} ${HEADERS})

target_link_libraries(Launcher "ncurses")