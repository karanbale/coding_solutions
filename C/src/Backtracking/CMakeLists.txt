cmake_minimum_required(VERSION 3.14)

set(component_name "Backtracking")

set(srcs
    31_nextPermutation.c
    46_permutations.c
    47_permutations2.c
    78_subsets.c
)

target_include_directories(${LIBRARY_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:/include>
    PRIVATE
        ${PROJECT_SOURCE_DIR}/C/include/Backtracking/
        ${PROJECT_SOURCE_DIR}/C/src/common_utils/
)

add_lib_sources(${component_name} "${srcs}")
