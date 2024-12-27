cmake_minimum_required(VERSION 3.27)
project(oop_project_cpp)

set(CMAKE_C_STANDARD 23)

# Include the command that downloads libraries
include(FetchContent)

# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    # setup the declare
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

# add raylib support
set(LIB1 raylib)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
    message(STATUS "Getting ${LIB1} from Github")
    include_dependency(${LIB1} https://github.com/raysan5/raylib.git 5.0)
else()
    message(STATUS "Using local ${LIB1}")
endif()

add_executable(oop_project_cpp main.cpp
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
        game.cpp)

# set the include directory
target_include_directories(oop_project_cpp PRIVATE ${raylib_INCLUDE_DIRS})

# link all libraries to the project
target_link_libraries(oop_project_cpp PRIVATE ${LIB1})
