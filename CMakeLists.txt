cmake_minimum_required(VERSION 3.19)
project(Car)

set(CMAKE_CXX_STANDARD 14)

add_executable(Car main.cpp Car.cpp Car.h CarDataBase.cpp CarDataBase.h CarNode.cpp CarNode.h Application.cpp Application.h SortingLinkedList.cpp SortingLinkedList.h)