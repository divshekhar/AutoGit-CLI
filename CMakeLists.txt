cmake_minimum_required (VERSION 3.8)

project ("AutoGit-CLI" VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_subdirectory("extern/CLI11")
add_subdirectory("extern/fmt")
set_target_properties(fmt PROPERTIES FOLDER extern)

# ************ EXTERNAL LIBRARY INCLUSION ************ #

add_library(rang INTERFACE)
target_include_directories(rang SYSTEM INTERFACE "${CMAKE_SOURCE_DIR}/extern/rang/include")


# **************** EXECUTABLE SETUP ****************** #

add_executable(${EXECUTABLE_NAME} ${SOURCES})

# ***************** LIBRARY LINKING ****************** #

target_link_libraries(${EXECUTABLE_NAME} PRIVATE CLI11::CLI11)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE rang)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE fmt)
