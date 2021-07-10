cmake_minimum_required(VERSION 3.14)

add_subdirectory(src)
# add_subdirectory(Basics)
# add_subdirectory(BinarySearch)
# add_subdirectory(BitwiseOperations)
# add_subdirectory(Design)
# add_subdirectory(DynamicProgramming)
# add_subdirectory(ImplementYourOwn)
# add_subdirectory(LeetCode)
# add_subdirectory(LinkedList)
# add_subdirectory(Macros)
# add_subdirectory(Mathematics)
# add_subdirectory(MaxHeap)
# add_subdirectory(Multithreaded)
# add_subdirectory(Stack)
# add_subdirectory(StringManipulation)
# add_subdirectory(TwoPointer)
# add_subdirectory(utils)

get_property(lib_srcs GLOBAL PROPERTY C_LIB_SRC)
target_sources(${LIBRARY_NAME}
    PRIVATE
        "${lib_srcs}"
)

# find_program(CLANG_TIDY_PATH "clang-tidy")
# if (CLANG_TIDY_PATH)
#     set_target_properties(${LIBRARY_NAME} PROPERTIES C_CLANG_TIDY
#             "clang-tidy;-checks=bugprone-*,clang-analyzer-*,concurrency-*,misc-*,cert-*,performance-*,readability-*,portability-*;-warnings-as-errors=*"
#             )
# endif ()

target_compile_options(${LIBRARY_NAME} PRIVATE -Wall -Wextra -pedantic)
target_compile_features(${LIBRARY_NAME} PUBLIC c_std_99)

include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
    set_target_properties(${LIBRARY_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
