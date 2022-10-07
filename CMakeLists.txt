# -------------------------------
# Setup CMake minimum version
# -------------------------------
cmake_minimum_required(VERSION 3.16)

# -------------------------------
# Rex Version
# -------------------------------
SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 1)
SET(VERSION_PATCH 0)

# -------------------------------
# Configurations
# -------------------------------
SET(CONFIGURATION_DEBUG Debug)
SET(CONFIGURATION_RELWITHDEBINFO RelWithDebInfo)
SET(CONFIGURATION_MINSIZEREL Release)
SET(CONFIGURATION_RELEASE Release)

# -------------------------------
# Setup the "Rex Standard Library" solution
# -------------------------------
project(rex-standard-library VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}"
				  LANGUAGES C;CXX)

if ("${REX_STL_DIR}" STREQUAL "")
	SET(REX_STL_DIR "${CMAKE_SOURCE_DIR}/source/")
endif()

message(STATUS "#--------------------- Starting project generation ---------------------")
message("CMake Version: \t\t${CMAKE_VERSION}")
message("Architecture: \t\t${CMAKE_GENERATOR_PLATFORM}")
message("Generating project: \t${PROJECT_NAME} v${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# -------------------------------
# CMake dependencies
# -------------------------------
include(cmake\\utilities.cmake)
include(cmake\\directories.cmake)

# --------------------------
# Setup global properties
# --------------------------
# Enable folder structure in the IDE
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

SET(WINDOWS Windows)
SET(LINUX Linux)
SET(MACOS MacOS)

SET(BUILD_TARGETS ${WINDOWS} ${LINUX} ${MACOS})

SET(REX_BUILD_TARGET ${WINDOWS} CACHE STRING "Setup solution for the specific build target")
SET_PROPERTY(CACHE REX_BUILD_TARGET PROPERTY STRINGS ${BUILD_TARGETS})

if(REX_BUILD_TARGET STREQUAL ${WINDOWS})
add_compile_definitions("REX_PLATFORM_WINDOWS")
endif()

SET(X64 x64)
SET(X86 x86)
SET(PLATFORMS ${X64} ${X86})

SET(REX_PLATFORM ${X64} CACHE STRING "Setup solution for the specific platform")
SET_PROPERTY(CACHE REX_PLATFORM PROPERTY STRINGS ${PLATFORMS})

if(REX_PLATFORM STREQUAL ${X64})
add_compile_definitions("REX_PLATFORM_X64")
elseif(REX_PLATFORM STREQUAL ${X86})
add_compile_definitions("REX_PLATFORM_X86")
endif()

# Remove the always defined _WINDOWS flag
# CPP
if (MSVC)
	string (REPLACE "/D_WINDOWS" "" CMAKE_CUSTOM_CPP_FLAGS ${CMAKE_CXX_FLAGS})
	string (REPLACE "/DWIN32" "" CMAKE_CUSTOM_CPP_FLAGS ${CMAKE_CUSTOM_CPP_FLAGS}) 
	SET(CMAKE_CXX_FLAGS "${CMAKE_CUSTOM_CPP_FLAGS}" CACHE STRING "" FORCE)
	# C
	string (REPLACE "/D_WINDOWS" "" CMAKE_CUSTOM_C_FLAGS ${CMAKE_C_FLAGS})
	string (REPLACE "/DWIN32" "" CMAKE_CUSTOM_C_FLAGS ${CMAKE_CUSTOM_C_FLAGS}) 
	SET(CMAKE_C_FLAGS "${CMAKE_CUSTOM_C_FLAGS}" CACHE STRING "" FORCE)
endif()

# Debug postfix
SET (CMAKE_DEBUG_POSTFIX _d)

# --------------------------------
# Setup compiler features
# --------------------------------
SET (CMAKE_CXX_STANDARD 20)
SET (CMAKE_CXX_STANDARD_REQUIRED ON)
SET (CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "Output directory: \t\t${OUTPUT_BINDIR}")

# --------------------------------
# Add subdirectories
# --------------------------------
add_subdirectory(${SRC_DIR})

message(STATUS "#---------------------- Ending project generation ----------------------")	