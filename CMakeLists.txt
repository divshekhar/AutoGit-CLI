cmake_minimum_required (VERSION 3.8)

project ("AutoGit-CLI" VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set Pybind11 python version
set(PYBIND11_PYTHON_VERSION 3.9.5 CACHE STRING "")

# Set runtime output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Executable name
set(EXECUTABLE_NAME "autogit")

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/extern/CLI11/CMakeLists.txt")
message(
    FATAL_ERROR
      "The submodules were not downloaded! AUTOGIT_SUBMODULE was turned off or failed. Please update submodules and try again."
  )
endif()


# **************** PROJECT INCLUSION **************** #

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    "${SOURCE_DIR}/*.cpp"
    "${INCLUDE_DIR}/*.hpp"
)

# ************** SUBDIRECTORY INCLUSION ************** #

find_package(Python COMPONENTS Interpreter Development)
add_subdirectory("extern/pybind11")

add_subdirectory("extern/CLI11")
add_subdirectory("extern/fmt")
set_target_properties(fmt PROPERTIES FOLDER extern)

# ************ EXTERNAL LIBRARY INCLUSION ************ #

add_library(rang INTERFACE)
target_include_directories(rang SYSTEM INTERFACE "${CMAKE_SOURCE_DIR}/extern/rang/include")

add_library(curlpp INTERFACE)
target_include_directories(curlpp SYSTEM INTERFACE "${CMAKE_SOURCE_DIR}/extern/curlpp/include")


# **************** EXECUTABLE SETUP ****************** #

add_executable(${EXECUTABLE_NAME} ${SOURCES})

# ************** SET BINARY FILENAMES **************** #

set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${EXECUTABLE_NAME}-debug)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME_RELWITHDEBUGINFO ${EXECUTABLE_NAME}-relwithdebuginfo)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${EXECUTABLE_NAME}-release)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME_MINSIZEREL ${EXECUTABLE_NAME}-minsizerel)

# **************** EXECUTABLE SETUP ****************** #

target_link_libraries(${EXECUTABLE_NAME} PRIVATE CLI11::CLI11)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE rang)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE fmt)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE curlpp)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE pybind11::embed pybind11::module pybind11::pybind11)
