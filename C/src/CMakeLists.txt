# Add library target
add_library(${LIBRARY_NAME})

add_subdirectory(Backtracking)
add_subdirectory(DFS)

get_property(lib_srcs GLOBAL PROPERTY OPTANE_LIB_SRC)
target_sources(${LIBRARY_NAME}
    PRIVATE
        "${lib_srcs}"
)

find_program(CLANG_TIDY_PATH "clang-tidy")
if (CLANG_TIDY_PATH)
    set_target_properties(${LIBRARY_NAME} PROPERTIES C_CLANG_TIDY
            "clang-tidy;-checks=bugprone-*,clang-analyzer-*,concurrency-*,
            misc-*,cert-*,performance-*,readability-*,portability-*;-warnings-as-errors=*"
            )
endif ()

include(${PROJECT_SOURCE_DIR}/cmake/macros.cmake)
