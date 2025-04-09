cmake_minimum_required(VERSION 3.15)
project(game_of_life)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
    src/Field.cpp
    src/Game_Of_Life.cpp
    src/main.cpp
)

include_directories(
    include
)
set(Boost_DIR "D:/Kirill.documents/c++/boost_1_82_0/stage/lib/cmake/Boost-1.82.0")

find_package(Boost REQUIRED program_options)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(GameOfLife ${SOURCE_FILES})
    target_link_libraries(GameOfLife ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Boost.Program_options not found")
endif()