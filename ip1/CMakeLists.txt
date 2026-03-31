cmake_minimum_required(VERSION 3.20)

project(card)
add_executable(card card.cpp)
set_target_properties(card PROPERTIES
    SUFFIX ".out"
)
