# Add library target
add_library(${LIBRARY_NAME})

add_subdirectory(Backtracking)
add_subdirectory(DFS)

get_property(lib_srcs GLOBAL PROPERTY OPTANE_LIB_SRC)
target_sources(${LIBRARY_NAME}
    PRIVATE
        "${lib_srcs}"
)

# target_include_directories(${LIBRARY_NAME}
#     PUBLIC
#         $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
#         $<INSTALL_INTERFACE:/include>
#     PRIVATE
#         ${CMAKE_CURRENT_SOURCE_DIR}/src/common_utils/
# )

include(${PROJECT_SOURCE_DIR}/cmake/macros.cmake)
