cmake_minimum_required(VERSION 3.5)
project(bounce LANGUAGES C)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SNAKE_SOURCES
    
    bounce.c
)

add_executable(bounce ${SNAKE_SOURCES})

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES) # fixes bug with trailing whitespace in some SDL2 versions
target_link_libraries(bounce ${SDL2_LIBRARIES})

# Deployment target
add_custom_target(deploy
    COMMENT "Copying bounce executable and resources for deployment..."
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:bounce>" "${CMAKE_BINARY_DIR}/bounce"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/gfx.h" "${CMAKE_BINARY_DIR}/gfx.h"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/globals.h" "${CMAKE_BINARY_DIR}/globals.h"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/io.h" "${CMAKE_BINARY_DIR}/io.h"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/snake2functions.h" "${CMAKE_BINARY_DIR}/snake2functions.h"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/types.h" "${CMAKE_BINARY_DIR}/types.h"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Add the deploy target as a dependency of the main target, so it will be built when running 'make'
#add_dependencies(bounce deploy)
