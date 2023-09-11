cmake_minimum_required(VERSION 3.5)
project(gfx_test LANGUAGES C)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(GFX_TEST_SOURCES
    gfx_test.c
)

add_executable(gfx_test ${GFX_TEST_SOURCES})

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES) # fixes bug with trailing whitespace in some SDL2 versions
target_link_libraries(gfx_test ${SDL2_LIBRARIES})

# Deployment target
add_custom_target(deploy
    COMMENT "Copying gfx_test executable and resources for deployment..."
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:gfx_test>" "${CMAKE_BINARY_DIR}/gfx_test"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Add the deploy target as a dependency of the main target, so it will be built when running 'make'
#add_dependencies(gfx_test deploy)
