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

if (CECE_RENDER_ENABLE)
    set(RENDER_SOURCES $<TARGET_OBJECTS:render>)
endif ()

# Create library
add_library(${PROJECT_NAME} SHARED
    $<TARGET_OBJECTS:core>
    $<TARGET_OBJECTS:config>
    $<TARGET_OBJECTS:loader>
    $<TARGET_OBJECTS:init>
    $<TARGET_OBJECTS:module>
    $<TARGET_OBJECTS:object>
    $<TARGET_OBJECTS:program>
    $<TARGET_OBJECTS:plugin>
    $<TARGET_OBJECTS:simulator>
    ${RENDER_SOURCES}
)

# ######################################################################### #

# OSX framework
set_target_properties(${PROJECT_NAME} PROPERTIES
    FRAMEWORK On
)

# Generate export header (MSVC)
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
    EXPORT_FILE_NAME "export.hpp"
)

# ######################################################################### #

set(Boost_USE_STATIC_LIBS Off)
find_package(Boost REQUIRED filesystem system)

# Include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC ${Boost_INCLUDE_DIRS}
)
# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES}
)

# Include OpenGL if rendering is enabled
if (CECE_RENDER_ENABLE)
    # OpenGL library is required
    find_package(OpenGL REQUIRED)

    # Include OpenGL path
    target_include_directories(${PROJECT_NAME}
        PUBLIC ${OPENGL_INCLUDE_DIR}
    )
    target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
    )
endif ()

if (CECE_PHYSICS_BUILTIN)
    target_link_libraries(${PROJECT_NAME} Box2D)
endif ()

if (MINGW)
    target_link_libraries(${PROJECT_NAME} Ws2_32)
elseif (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} dl)
endif ()

# ######################################################################### #
