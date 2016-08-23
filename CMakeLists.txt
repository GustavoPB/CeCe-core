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

cmake_minimum_required(VERSION 3.1)

# ######################################################################### #

project(cece
    VERSION 0.6.0
    LANGUAGES CXX
)

# ######################################################################### #

# Options
option(CECE_RENDER                  "Enable simulation rendering (vizualization support)" On)
option(CECE_RENDER_CHECK_ERRORS     "Enable renderer errors checking." Off)
option(CECE_THREAD_SAFE             "Enable thread support" Off)
option(CECE_TESTS_BUILD             "Build simulator part tests (requires GTest)" Off)
option(CECE_TIME_MEASUREMENT        "Enable or disable time measurement" Off)
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

# Build unit tests
if (CECE_TESTS_BUILD)
    enable_testing()

    # Init google test submodule
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/googletest/CMakeLists.txt")
        find_package(Git REQUIRED)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive googletest
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif ()

    message(STATUS "Build unit tests")
    set(BUILD_GMOCK Off CACHE BOOL "" FORCE)
    set(BUILD_GTEST On CACHE BOOL "" FORCE)
    set(gtest_force_shared_crt On CACHE BOOL "" FORCE)
    mark_as_advanced(BUILD_GMOCK BUILD_GTEST gtest_build_samples gtest_build_tests gtest_disable_pthreads gtest_force_shared_crt)
    add_subdirectory(googletest)
    target_include_directories(gtest INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/googletest/include)

    find_program(CCACHE_FOUND ccache)
    if (CCACHE_FOUND)
        set_property(DIRECTORY googletest PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(DIRECTORY googletest PROPERTY RULE_LAUNCH_LINK ccache)
    endif ()
endif ()

# Init google test submodule
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Box2D/Box2D/CMakeLists.txt")
    find_package(Git REQUIRED)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive Box2D
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif ()

# Add Box2D physics library
set(BOX2D_BUILD_EXAMPLES Off CACHE BOOL "" FORCE)
set(BOX2D_BUILD_SHARED Off CACHE BOOL "" FORCE)
set(BOX2D_BUILD_STATIC On CACHE BOOL "" FORCE)
set(BOX2D_INSTALL Off CACHE BOOL "" FORCE)
set(BOX2D_INSTALL_DOC Off CACHE BOOL "" FORCE)
mark_as_advanced(FORCE BOX2D_BUILD_EXAMPLES BOX2D_BUILD_SHARED BOX2D_BUILD_STATIC BOX2D_INSTALL BOX2D_INSTALL_DOC)

add_subdirectory(Box2D/Box2D)
# It will be linked in to the shared library
set_target_properties(Box2D PROPERTIES POSITION_INDEPENDENT_CODE On)
target_include_directories(Box2D INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Box2D/Box2D)

find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    set_property(DIRECTORY Box2D/Box2D PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(DIRECTORY Box2D/Box2D PROPERTY RULE_LAUNCH_LINK ccache)
endif ()

# ######################################################################### #

# CeCe library
add_subdirectory(cece)

# ######################################################################### #
