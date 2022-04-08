cmake_minimum_required(VERSION 3.21)
project(Yukon C)

set(CMAKE_C_STANDARD 23)

set(Sources main.c)
set(Headers deck.h view.h linkedlist.h)
add_executable(Yukon ${Sources} ${Headers})