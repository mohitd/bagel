cmake_minimum_required(VERSION 3.14)
project(bagel
    VERSION 0.1.0
    DESCRIPTION "An everything bagel of C++"
    LANGUAGES CXX)

################
# CONFIG
################
string(TOUPPER ${PROJECT_NAME} UPPER_PROJECT_NAME)
set(namespace ${PROJECT_NAME})

message(CHECK_START "Checking ${UPPER_PROJECT_NAME}_SHARED_LIBS")
if(DEFINED ${UPPER_PROJECT_NAME}_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${UPPER_PROJECT_NAME}_SHARED_LIBS)
    message(CHECK_PASS "${${UPPER_PROJECT_NAME}_SHARED_LIBS}")
else()
    message(CHECK_FAIL "${BUILD_SHARED_LIBS}")
endif()

message(CHECK_START "Building shared libraries")
if(BUILD_SHARED_LIBS)
    message(CHECK_PASS "yes")
else()
    message(CHECK_FAIL "no")
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Setting build type: ${CMAKE_BUILD_TYPE}")

set(export_header_name "export.hpp")
set(export_file_name "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/${export_header_name}")

# Sets the library path to lib/ and the include path to include/
# in the install prefix
include(GNUInstallDirs)
set(cmake_config_dir ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
set(build_tests ${UPPER_PROJECT_NAME}_BUILD_TESTS)
set(build_examples ${UPPER_PROJECT_NAME}_BUILD_EXAMPLES)
set(build_docs ${UPPER_PROJECT_NAME}_BUILD_DOCS)

option(${build_tests} "Builds tests" OFF)
option(${build_examples} "Builds examples" OFF)
option(${build_docs} "Builds docs" OFF)

################
# BUILD
################
add_library(${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC ${UPPER_PROJECT_NAME}_STATIC_DEFINE)
endif()

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
    EXPORT_FILE_NAME ${export_file_name}
)

if(NOT DEFINED CMAKE_CXX_VISIBILITY_PRESET)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_VISIBILITY_PRESET hidden
    )
endif()
if(NOT DEFINED CMAKE_VISIBILITY_INLINES_HIDDEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VISIBILITY_INLINES_HIDDEN ON
    )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_sources(${PROJECT_NAME} PRIVATE
    src/chrono/timer.cpp)

################
# INSTALL
################

# Install the entire include directory
# Note: PUBLIC_HEADER is fine for smaller projects, but this project has a
# directory structure that we want to preserve.
# Installing the entire directory ensures that directory structure in the
# include directory at build time is preserved in the install path
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Targets"
)

install(EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    NAMESPACE ${namespace}::
    DESTINATION ${cmake_config_dir}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)
# create config file
configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${cmake_config_dir}
)
# install config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${cmake_config_dir}
)

message(CHECK_START "Building tests")
if(${build_tests})
    message(CHECK_PASS "yes")

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
else()
    message(CHECK_FAIL "no")
endif()

message(CHECK_START "Building examples")
if(${build_examples})
    message(CHECK_PASS "yes")

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
else()
    message(CHECK_FAIL "no")
endif()

message(CHECK_START "Building docs")
if(${build_docs})
    message(CHECK_PASS "yes")

    find_package(Doxygen REQUIRED)
    
    set(README_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Readme.md")
    set(DOXYGEN_PROJECT_NAME "${PROJECT_NAME}")
    set(DOXYGEN_PROJECT_BRIEF "${PROJECT_DESCRIPTION}")
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${README_PATH}")
    doxygen_add_docs(generate_docs include "${README_PATH}"
        COMMENT "Generating docs")
    add_dependencies(${PROJECT_NAME} generate_docs)
else()
    message(CHECK_FAIL "no")
endif()

# TODO: code coverage
