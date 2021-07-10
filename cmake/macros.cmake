cmake_minimum_required(VERSION 3.14)

#
# Adds a unity library test
#
# test_name     Test name to be displayed
# test_src      Source file(s) of test
#
function(add_unity_lib_test test_name test_srcs)
    set(test_target "utest_${test_name}")
    set(ctest_name "Test_${test_name}")

    add_executable(${test_target})

    target_sources(${test_target}
        PRIVATE
        ${test_srcs}
        ${unity_SOURCE_DIR}/src/unity.c
    )

    target_include_directories(${test_target}
        PRIVATE
            ${unity_SOURCE_DIR}/src/.
    )

    target_compile_features(${test_target}
        PRIVATE
            c_std_99
    )

    target_compile_definitions(${test_target}
        PUBLIC
            UNITY_OUTPUT_FOR_ECLIPSE
    )

    add_test(NAME ${ctest_name} COMMAND ${test_target})
endfunction()

#
# Adds a unity test
#
# test_name     Name of test
# test_src      Source file(s) for test
# comp_list     List of component
# comp_hdr_list List of component header only
#
function(add_unity_test test_name test_src comp_list)
    set(test_target "utest_${test_name}")
    set(ctest_name "Test_${test_name}")

    add_executable(${test_target})

    target_sources(${test_target} PRIVATE
        ${test_src}
        ${unity_SOURCE_DIR}/src/unity.c
    )

    # Component list
    foreach(component IN ITEMS ${comp_list})
        string(TOUPPER ${component} COMPONENT)
        get_property(comp_srcs GLOBAL PROPERTY OPTANE_${COMPONENT}_SRC)

        target_sources(${test_target}
            PRIVATE
                ${comp_srcs}
        )

        target_include_directories(${test_target}
            PRIVATE
                ${PROJECT_SOURCE_DIR}/src/${component}
        )
    endforeach()

    target_include_directories(${test_target}
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}/tests/mocks
            ${unity_SOURCE_DIR}/src/.
    )

    target_compile_features(${test_target}
        PRIVATE
            c_std_99
    )

    target_compile_definitions(${test_target}
        PUBLIC
            UNITY_OUTPUT_FOR_ECLIPSE
    )

    target_link_libraries(${test_target}
        PRIVATE
        # ${LIBRARY_NAME}
            safestring_static
            mock
    )

    add_test(NAME ${ctest_name} COMMAND ${test_target})
endfunction()

#
# Adds library sources and creates global properties for unit testing
#
# component     Component name
# sources_list  List of source files
#
function(add_lib_sources component_name sources_list)
    string(TOUPPER "${component_name}" COMPONENT)

    # Define component src property if not defined
    set(COMPONENT_SRC_PROP OPTANE_${COMPONENT}_SRC)
    get_property(comp_src GLOBAL PROPERTY ${COMPONENT_SRC_PROP} DEFINED)
    if (NOT comp_src)
        define_property(GLOBAL PROPERTY ${COMPONENT_SRC_PROP}
            BRIEF_DOCS "List of component source files"
            FULL_DOCS "List of component source files to be compiled into library")
    endif()

    # Define component hdr property if not defined
    set(COMPONENT_HDR_PROP OPTANE_${COMPONENT}_HDR)
    get_property(comp_hdr GLOBAL PROPERTY ${COMPONENT_HDR_PROP} DEFINED)
    if (NOT comp_hdr)
        define_property(GLOBAL PROPERTY ${COMPONENT_HDR_PROP}
            BRIEF_DOCS "List of component header files"
            FULL_DOCS "List of component header files to be compiled into library")
    endif()

    # Define library property if not defined
    get_property(c_lib_src GLOBAL PROPERTY C_LIB_SRC DEFINED)
    if (NOT c_lib_src)
        define_property(GLOBAL PROPERTY C_LIB_SRC
            BRIEF_DOCS "List of source files"
            FULL_DOCS "List of source files to be compiled into library")
    endif()

    # Make source files into absolute paths
    set(SRCS)
    set(HDRS)
    foreach(f IN LISTS sources_list)
        if (NOT IS_ABSOLUTE "${f}")
            get_filename_component(f "${f}" ABSOLUTE)
        endif()

        # Split headers and source files
        STRING(REGEX MATCH ".+\.h$" match "${f}")
        if (match)
            list(APPEND HDRS "${f}")
        else()
            list(APPEND SRCS "${f}")
        endif()
    endforeach()

    set_property(GLOBAL APPEND PROPERTY C_LIB_SRC "${SRCS}" "${HDRS}")
    set_property(GLOBAL APPEND PROPERTY ${COMPONENT_SRC_PROP} "${SRCS}")
    set_property(GLOBAL APPEND PROPERTY ${COMPONENT_HDR_PROP} "${HDRS}")
endfunction()
