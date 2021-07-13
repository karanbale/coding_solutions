cmake_minimum_required(VERSION 3.14)

set(component_name "MaxHeap")

set(srcs
    358_rearrangeStringKDistanceApart.c
    767_rearrangeStringMaxHeap.c
    857_minCostToHireKWorkers.c
)

target_include_directories(${LIBRARY_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:/include>
    PRIVATE
        ${PROJECT_SOURCE_DIR}/C/include/MaxHeap/
        ${PROJECT_SOURCE_DIR}/C/src/common_utils/
)

add_lib_sources(${component_name} "${srcs}")
