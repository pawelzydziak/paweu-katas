cmake_minimum_required(VERSION 3.0)
project(kata)

set(CMAKE_CXX_STANDARD 20)

add_executable(kata main.cpp
        lib/KataFramework.h
        Solutions/GeneratePassword/PasswordKata.h
        Solutions/Solutions.h)
