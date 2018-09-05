################################################################
#                          Created by:                         #
#                         James Miller                         #
################################################################

cmake_minimum_required(VERSION 3.1)

# Include Extra CMake capabilities
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

# Assignment Name
set(CGRA_PROJECT "a2-loader" CACHE STRING "CGRA Project Name")

# Project
project("CGRA_PROJECT_${CGRA_PROJECT}" CXX C)

include(CGRACompiler)
include(CGRAFunctions)

#Package Finding
FIND_PACKAGE(PkgConfig REQUIRED)


# Enable IDE Project Folders
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Force Output Directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Vendored libraries
add_subdirectory(vendor/glew)
include_directories("${PROJECT_SOURCE_DIR}/vendor/glfw/include")
include_directories("${PROJECT_SOURCE_DIR}")
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/imgui)

# Find OpenGL
find_package(OpenGL REQUIRED)

#NFD
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include/")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/nfd/")
ADD_LIBRARY(nfd_lib STATIC IMPORTED)
SET_PROPERTY(TARGET nfd_lib PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/nfd/libnfd.a")


#GTK3
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
message(status "GTK3_INCLUDE_DIRS = ${GTK3_INCLUDE_DIRS}")
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})
message(status "GTK3_LIBRARY_DIRS = ${GTK3_LIBRARY_DIRS}")
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})
message(status "GTK3_CFLAGS_OTHER = ${GTK3_CFLAGS_OTHER}")


# Add subdirectories
add_subdirectory(src) # Primary Source Files
add_subdirectory(res) # Resources; for example shaders
set_property(TARGET ${CGRA_PROJECT} PROPERTY FOLDER "CGRA")
