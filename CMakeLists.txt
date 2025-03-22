cmake_minimum_required(VERSION 3.20)
project(lab_2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS "--coverage -O0 -g ${CMAKE_CXX_FLAGS}")

add_executable(lab_2 main.c teste.c console.c console.h srv.c lista.c oferta.c validator.c)

