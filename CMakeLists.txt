cmake_minimum_required(VERSION 3.27)
project(oop_tet)

set(CMAKE_C_STANDARD 23)

# Include the command that downloads libraries
include(FetchContent)

# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    # setup the declare
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG ${gitTag}
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

# add raylib support
set(LIB1 raylib)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
    message(STATUS "Getting ${LIB1} from Github")
    include_dependency(${LIB1} https://github.com/raysan5/raylib.git 5.0)
else ()
    message(STATUS "Using local ${LIB1}")
endif ()

# Add Google Test
include_dependency(googletest https://github.com/google/googletest.git release-1.12.1)

add_executable(oop_tet main.cpp
        grid.h
        grid.cpp
        block.h
        position.h
        position.cpp
        colors.h
        colors.cpp
        block.cpp
        blocks.cpp
        game.h
        game.cpp
        score.h
        score.cpp
        draw.h
        draw.cpp
        block_types.h
        blocks_factory.h
        blocks.h
        draw.cpp
)

# set the include directory
target_include_directories(oop_tet PRIVATE ${raylib_INCLUDE_DIRS})

# link all libraries to the project
target_link_libraries(oop_tet PRIVATE ${LIB1})

# Add the src directory to the include path for tests
include_directories(${CMAKE_SOURCE_DIR}/src)

# Add a test executable
add_executable(tests
        tests/test_block.cpp
        tests/test_grid.cpp
        tests/test_score.cpp
        ${CMAKE_SOURCE_DIR}/grid.cpp
        ${CMAKE_SOURCE_DIR}/block.cpp
        ${CMAKE_SOURCE_DIR}/position.cpp
        ${CMAKE_SOURCE_DIR}/score.cpp
        ${CMAKE_SOURCE_DIR}/colors.cpp
        ${CMAKE_SOURCE_DIR}/blocks.cpp)

target_link_libraries(tests PRIVATE gtest gtest_main ${LIB1})