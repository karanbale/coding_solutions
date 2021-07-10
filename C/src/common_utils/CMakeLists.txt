cmake_minimum_required(VERSION 3.14)

set(component_name "common_utils")

set(srcs
    common.c
    common.h
)

add_lib_sources(${component_name} "${srcs}")
