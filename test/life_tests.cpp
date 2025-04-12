#define BOOST_TEST_MODULE GameOfLifeTests
#include <boost/test/included/unit_test.hpp>
#include "../include/Game_Of_Life.h"
#include "../include/Variable.h"
#include "../include/Field.h"

using namespace Variable;


Field createEmptyField(int height, int width) {
    Field field;
    field.InitializeField(); // Random initialization
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            field.setCell(i, j, INT_DEATH_CELL); // Make all the cells dead
        }
    }
    return field;
}

Field createField(int height, int width, const vector<pair<int, int>>& liveCells) {
    Field field = createEmptyField(height, width); // Create an empty field

    // Set initial live cells
    for (const auto& cell : liveCells) {
        field.setCell(cell.first, cell.second, INT_LIVE_CELL);
    }
    return field;
}

BOOST_AUTO_TEST_CASE(test_NextGeneration_applies_rules_correctly) {
    Game_Of_Life game; // Create a Game_Of_Life object

    // Live cell with fewer than 2 live neighbors dies
    {
        // Arrange
        Field field = createField(HEIGHT, WIDTH, { {1, 1} }); // Single live cell

        // Act
        game.NextGeneration(field); // Apply one generation

        // Assert
        BOOST_CHECK(field.getCell(1, 1) == INT_DEATH_CELL); // Cell at (1,1) should die, using the getter
    }


    // Live cell with 2 live neighbors survives
    {
        // Arrange
        Field field = createField(HEIGHT, WIDTH, { {0, 0}, {0, 1}, {1, 0} });

        // Act
        game.NextGeneration(field);

        // Assert
        BOOST_CHECK(field.getCell(1, 1) == INT_LIVE_CELL); // using the getter
    }

    // Live cell with 3 live neighbors survives
    {
        // Arrange
        Field field = createField(HEIGHT, WIDTH, { {0, 0}, {0, 1}, {1, 0}, {1, 1} });
        // Act
        game.NextGeneration(field);
        // Assert
        BOOST_CHECK(field.getCell(1, 1) == INT_LIVE_CELL); // using the getter
    }

    // Live cell with more than 3 live neighbors dies
    {
        // Arrange
        Field field = createField(HEIGHT, WIDTH, {
            {0, 0}, {0, 1}, {0, 2},
            {1, 0}, {1, 1}
            });
        // Act
        game.NextGeneration(field);
        // Assert
        BOOST_CHECK(field.getCell(1, 1) == INT_DEATH_CELL); // using the getter
    }

    // Dead cell with exactly 3 live neighbors becomes alive
    {
        // Arrange
        Field field = createField(HEIGHT, WIDTH, { {0, 0}, {0, 1}, {1, 0} });
        // Act
        game.NextGeneration(field);
        // Assert
        BOOST_CHECK(field.getCell(1, 1) == INT_LIVE_CELL); // using the getter
    }

    // Equality flag set when board doesn't change - BLOCK
    {
        // Arrange
        Field field = createField(HEIGHT, WIDTH, { {0, 0}, {0, 1}, {1, 0}, {1, 1} });
        game.FlagEquality = false;
        // Act
        game.NextGeneration(field);
        // Assert
        BOOST_CHECK(game.FlagEquality == TRUE_FLAGE_QUALITY);
    }

    // Equality flag set when board changes - BLINKER
    {
        // Arrange
        Field field = createField(HEIGHT, WIDTH, { {1, 0}, {1, 1}, {1, 2} });
        game.FlagEquality = true;
        // Act
        game.NextGeneration(field);
        // Assert
        BOOST_CHECK(game.FlagEquality == false);
    }
}