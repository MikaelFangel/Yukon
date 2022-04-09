cmake_minimum_required(VERSION 3.21)
project(Yukon C)

set(CMAKE_C_STANDARD 23)

set(Sources main.c linkedlist.c view.c deck.c)
set(Headers deck.h view.h linkedlist.h)
add_executable(Yukon ${Sources} ${Headers})

set(Test_Sources test/main_test.c linkedlist.c view.c deck.c)
set(Test_Headers )
add_executable(YukonTest ${Test_Sources} ${Headers} ${Test_Headers})
