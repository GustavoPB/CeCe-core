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

set(CECE_ENABLE_RENDER ${CECE_RENDER_ENABLE})
set(CECE_ENABLE_BOX2D_PHYSICS ${CECE_PHYSICS_BUILTIN})
set(CECE_ENABLE_BOX2D_PHYSICS_DEBUG ${CECE_PHYSICS_BUILTIN_DEBUG})

# Create config file
configure_file(config.hpp.in config.hpp)

# ######################################################################### #

##
## Pretend directory to source files
##
function(dir_pretend OUT DIR)
    set(FILES "")

    foreach (F ${ARGN})
        list(APPEND FILES "${DIR}${F}")
    endforeach ()

    set(${OUT} ${FILES} PARENT_SCOPE)
endfunction ()

# ######################################################################### #

# Core files
add_subdirectory(core)
add_subdirectory(config)
add_subdirectory(loader)
add_subdirectory(init)
add_subdirectory(module)
add_subdirectory(object)
add_subdirectory(program)
add_subdirectory(plugin)

# Renderer files
if (CECE_RENDER_ENABLE)
    add_subdirectory(render)
endif ()

# Simulation files
add_subdirectory(simulator)

# ######################################################################### #

# Sources
set(SRCS
    ${SOURCES_CORE}
    ${SOURCES_CONFIG}
    ${SOURCES_LOADER}
    ${SOURCES_INIT}
    ${SOURCES_MODULE}
    ${SOURCES_OBJECT}
    ${SOURCES_PROGRAM}
    ${SOURCES_PLUGIN}
    ${SOURCES_SIMULATOR}
)

if (CECE_RENDER_ENABLE)
    set(SRCS ${SRCS} ${SOURCES_RENDER})
endif ()

# Create library
add_library(${PROJECT_NAME} SHARED ${SRCS})

# ######################################################################### #

# Properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    FRAMEWORK On
    CXX_STANDARD 11
    CXX_EXTENSIONS Off
    CXX_STANDARD_REQUIRED On
    WINDOWS_EXPORT_ALL_SYMBOLS On
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_BINARY_DIR}/..
)

# Generate export header (MSVC)
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
    EXPORT_FILE_NAME "export.hpp"
)

# ######################################################################### #

# Boost libraries
if (UNIX AND NOT APPLE)
    set(Boost_USE_STATIC_LIBS Off)
else ()
    set(Boost_USE_STATIC_LIBS On)
endif ()

find_package(Boost REQUIRED filesystem system)
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# Include OpenGL if rendering is enabled
if (CECE_RENDER_ENABLE)
    # OpenGL library is required
    find_package(OpenGL REQUIRED)
    target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
endif ()

if (CECE_PHYSICS_BUILTIN)
    target_link_libraries(${PROJECT_NAME} Physics)
endif ()

# Enable time measurement
if (CECE_PERFORMANCE_MEASUREMENT)
    target_compile_definitions(${PROJECT_NAME} -DCECE_ENABLE_MEASUREMENT)
endif ()

if (MINGW)
    target_link_libraries(${PROJECT_NAME} Ws2_32)
elseif (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} dl)
endif ()

# ######################################################################### #

if (CECE_TESTS_BUILD)
    add_executable(${PROJECT_NAME}_test
        ${SOURCES_CORE_TEST}
    )

    # Properties
    set_target_properties(${PROJECT_NAME}_test PROPERTIES
        CXX_STANDARD 11
        CXX_EXTENSIONS Off
        CXX_STANDARD_REQUIRED On
    )

    target_link_libraries(${PROJECT_NAME}_test
        ${PROJECT_NAME}
        gtest_main
    )

    add_test(${PROJECT_NAME} ${PROJECT_NAME}_test)
endif ()

# ######################################################################### #
