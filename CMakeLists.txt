cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

###
# Setup project Raytracing
###

project(TNCG15)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER CMake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

add_library(project_warnings INTERFACE)
if (WIN32)
  target_compile_options(project_warnings INTERFACE "/W4")
else ()
  target_compile_options(project_warnings INTERFACE "-Wall")
endif ()

###
# Raytracing Library
###

set(HEADER_FILES
  include/Ray.h
  include/ColorRGB.h
)

set(SOURCE_FILES
  src/Ray.cpp
  src/ColorRGB.cpp
)

add_library(Raytracing
  ${SOURCE_FILES}
  ${HEADER_FILES}
)

source_group("Header Files" FILES ${HEADER_FILES})
target_include_directories(Raytracing PRIVATE "include")

###
# Application
###
add_executable(Application
  src/main.cpp
)

target_include_directories(Application PRIVATE "include")

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Application)
endif()


if (EXISTS "${PROJECT_SOURCE_DIR}/solution")
  add_executable(solution
    solution/main.cpp
    solution/Ray.cpp
  )
  target_include_directories(solution PRIVATE "include" "solution")
endif ()
