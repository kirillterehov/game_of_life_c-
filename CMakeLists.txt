cmake_minimum_required(VERSION 3.15)
project(game_of_life)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
    src/Field.cpp
    src/Game_Of_Life.cpp
)

include_directories(
    include
    test  # Include the 'test' directory for Catch2 header
)

# Create a STATIC library for GameOfLife
add_library(GameOfLife_lib STATIC ${SOURCE_FILES})

# Link Boost to GameOfLife library
set(Boost_DIR BOOST_CMAKE_PATH)
find_package(Boost REQUIRED program_options)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(GameOfLife_lib Boost::program_options)
else()
    message(FATAL_ERROR "Boost.Program_options not found")
endif()

# Define test executable
add_executable(life_tests test/life_tests.cpp)

# Link test executable with GameOfLife library
target_link_libraries(life_tests GameOfLife_lib)

# Link with Boost (if found)
if(Boost_FOUND)
    target_link_libraries(life_tests Boost::program_options)
endif()

# Remove target_compile_definitions for CATCH_CONFIG_MAIN
# target_compile_definitions(life_tests PRIVATE CATCH_CONFIG_MAIN)  # NO LONGER NEEDED

# Add test execution using add_test
enable_testing()
add_test(NAME LifeTests COMMAND life_tests)

# Add executable (main)
add_executable(GameOfLife src/main.cpp) # only main.cpp here
target_link_libraries(GameOfLife GameOfLife_lib Boost::program_options) # Link GameOfLife to GameOfLife_lib and Boost