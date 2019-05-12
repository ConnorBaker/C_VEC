cmake_minimum_required(VERSION 3.14)
project(c_vec_lib)

set(CMAKE_C_STANDARD 11)

add_library(c_vec_lib vec_int.c vec_int.h vec_definitions.h vec_prototypes.h
        vec_nomenclature.h)