cmake_minimum_required(VERSION 3.26)
project(WS4 C)

set(CMAKE_C_STANDARD 11)

add_executable(
        6_20
        6_20/6_20.c
        6_20/LapsToMiles.c
        6_20/LapsToMiles.h

)

add_executable(
        6_30
        6_30/6_30.c
        6_30/MaxNumber.c
        6_30/MaxNumber.h
        6_30/MinNumber.c
        6_30/MinNumber.h
)
