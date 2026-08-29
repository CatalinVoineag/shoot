cmake_minimum_required(VERSION 3.23)

project(
  Shoot
  VERSION 1.0
  DESCRIPTION "Shoot"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor")

add_executable(Shoot
  main.cpp
  src/cpp/gameScene.cpp
  src/cpp/player.cpp
)

target_include_directories(Shoot PRIVATE src ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory("${VENDOR_DIR}/raylib")

target_link_libraries(Shoot
  raylib
)
