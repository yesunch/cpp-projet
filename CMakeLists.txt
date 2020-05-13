cmake_minimum_required(VERSION 3.10)
project(bestioles)

set(CMAKE_CXX_STANDARD 14)

add_executable(bestioles main.cpp Aquarium.cpp Aquarium.h Milieu.cpp Milieu.h Bestiole.cpp Bestiole.h Espece.cpp Espece.h)

target_link_libraries(bestioles sfml-system sfml-window sfml-graphics)
