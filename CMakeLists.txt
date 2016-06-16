cmake_minimum_required(VERSION 3.4)
project(Hospital1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES
    src/diseases.c
    src/diseases.h
    src/hospital.c
    src/hospital.h
    src/parse.c
    src/parse.h
    src/structure.c
    src/structure.h
    src/test.c src/test.h)

add_executable(Hospital1 ${SOURCE_FILES})