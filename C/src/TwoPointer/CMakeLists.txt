cmake_minimum_required(VERSION 3.14)

set(component_name "TwoPointer")

set(srcs
    5_longestPalindromicSubString.c
    27_RemoveElement.c
    42_TrappingRainWaterTP.c
)

target_include_directories(${LIBRARY_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:/include>
    PRIVATE
        ${PROJECT_SOURCE_DIR}/C/include/TwoPointer/
        ${PROJECT_SOURCE_DIR}/C/src/common_utils/
)

add_lib_sources(${component_name} "${srcs}")
