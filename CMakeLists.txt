cmake_minimum_required(VERSION 3.21)
project(Yukon C)

set(CMAKE_C_STANDARD 23)

set(Sources src/main.c src/linkedlist.c src/view.c src/deck.c)
set(Headers src/deck.h src/view.h src/linkedlist.h)
add_executable(Yukon ${Sources} ${Headers})

set(Test_Sources test/main_test.c src/linkedlist.c src/view.c src/deck.c)
set(Test_Headers )
add_executable(YukonTest ${Test_Sources} ${Headers} ${Test_Headers})
