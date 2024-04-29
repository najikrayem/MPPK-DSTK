cmake_minimum_required(VERSION 3.22.1)

# Set the project name
project(MPPK_DSTK LANGUAGES C ASM)

# GDB TODO
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_USE_RELATIVE_PATHS ON)

# set verbose makefile
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

# Define the option to strip the binary
option(STRIP_BINARY "Strip the binary" ON)
# Strip the binary if the option is ON and the build type is NOT Debug
if(STRIP_BINARY AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
else()
    message(STATUS "Stripping the binary is disabled because the build type is Debug")
endif()


add_subdirectory(lib)
add_subdirectory(src)
