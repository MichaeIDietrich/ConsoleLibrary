cmake_minimum_required(VERSION 2.7)

project(SpaceInvaders)

set(SOURCE
  main.cpp
  Bullet.cpp
  CollisionDetectorController.cpp
  GameField.cpp
  GameFieldController.cpp
  GameFigure.cpp
  GameFigureController.cpp
  GameMatrix.cpp
  Invader.cpp
  InvaderController.cpp
  Player.cpp
  PlayerController.cpp
  Shield.cpp
  SpaceInvaders.cpp
  Vector2D.cpp
  SpaceInvaders.cpp
  ../ConsoleLibrary/Menu.cpp
  ../ConsoleLibrary/LinuxConsole.cpp
)

set(HEADERS
  main.h
  Bullet.h
  CollisionDetectorController.h
  GameField.h
  GameFieldController.h
  GameFigure.h
  GameFigureController.h
  GameMatrix.h
  Invader.h
  InvaderController.h
  Player.h
  PlayerController.h
  Shield.h
  Vector2D.h
  ../ConsoleLibrary/Menu.h
  ../ConsoleLibrary/Console.h
  ../ConsoleLibrary/LinuxConsole.h
)

add_executable(SpaceInvaders ${SOURCE} ${HEADERS})

target_link_libraries(SpaceInvaders "ncurses")