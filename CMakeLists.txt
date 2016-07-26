# ######################################################################### #
# Georgiev Lab (c) 2015-2016                                                #
# ######################################################################### #
# Department of Cybernetics                                                 #
# Faculty of Applied Sciences                                               #
# University of West Bohemia in Pilsen                                      #
# ######################################################################### #
#                                                                           #
# This file is part of CeCe.                                                #
#                                                                           #
# CeCe is free software: you can redistribute it and/or modify              #
# it under the terms of the GNU General Public License as published by      #
# the Free Software Foundation, either version 3 of the License, or         #
# (at your option) any later version.                                       #
#                                                                           #
# CeCe is distributed in the hope that it will be useful,                   #
# but WITHOUT ANY WARRANTY; without even the implied warranty of            #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             #
# GNU General Public License for more details.                              #
#                                                                           #
# You should have received a copy of the GNU General Public License         #
# along with CeCe.  If not, see <http://www.gnu.org/licenses/>.             #
#                                                                           #
# ######################################################################### #

cmake_minimum_required(VERSION 3.2)

# ######################################################################### #

# Add path to additional modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/")

# ######################################################################### #

project(CeCe
    VERSION 0.6.0
    LANGUAGES CXX
)

# C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_POSITION_INDEPENDENT_CODE On)

# ######################################################################### #

# Options
option(CECE_RENDER_ENABLE           "Enable simulation rendering (vizualization support)" On)
option(CECE_RENDER_CHECK_ERRORS     "Enable renderer errors checking." Off)
option(CECE_PHYSICS_BUILTIN         "Enable builtin physics engine (Box2D)" On)
option(CECE_PHYSICS_BUILTIN_DEBUG   "Enable or disable physics engine debugging" Off)
option(CECE_THREAD_SAFE             "Enable thread support" Off)
option(CECE_TESTS_BUILD             "Build simulator part tests (requires GTest)" Off)
option(CECE_PERFORMANCE_MEASUREMENT "Enable or disable time measurement" Off)
set(CECE_REAL_TYPE "double" CACHE STRING "Type used for real values")
set_property(CACHE CECE_REAL_TYPE PROPERTY STRINGS "float" "double" "long double")

# Must be defined
if (NOT CECE_REAL_TYPE)
    message(FATAL_ERROR "Missing 'CECE_REAL_TYPE' option")
endif ()

if (APPLE)
    set(MACOSX_VERSION_MIN "10.9" CACHE STRING "Minimum version of MacOS X to support")
endif ()

# ######################################################################### #

# Enable time measurement
if (CECE_PERFORMANCE_MEASUREMENT)
    message(STATUS "Time measurement enabled")
    add_definitions(-DENABLE_MEASUREMENT=1)
endif ()

# Build unit tests
if (CECE_TESTS_BUILD)
    message(STATUS "Build unit tests")
    enable_testing()
    include(GTest)
endif ()

if (CECE_PHYSICS_BUILTIN)
    set(BOX2D_BUILD_EXAMPLES Off CACHE BOOL "" FORCE)
    set(BOX2D_BUILD_SHARED Off CACHE BOOL "" FORCE)
    set(BOX2D_BUILD_STATIC On CACHE BOOL "" FORCE)
    set(BOX2D_INSTALL Off CACHE BOOL "" FORCE)
    set(BOX2D_INSTALL_DOC Off CACHE BOOL "" FORCE)
    add_subdirectory(Box2D/Box2D)
endif ()

# ######################################################################### #

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# ######################################################################### #

# CeCe library
add_subdirectory(cece)

# ######################################################################### #
