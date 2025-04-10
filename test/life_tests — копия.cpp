#define CATCH_CONFIG_MAIN
#include "../include/catch_amalgamated.hpp"
#include "../include/Game_Of_Life.h"
#include "../include/Variable.h"

using namespace Variable;

// Helper function to create a Field with specific initial state
Field createField(int height, int width, const std::vector<std::pair<int, int>>& liveCells) {
    Field field(height, width);
    field.field.resize(height);  // Устанавливаем правильный размер вектора

    for (int i = 0; i < height; ++i) {
        field.field[i].resize(width, INT_DEATH_CELL); // Инициализируем каждую строку
    }
    for (const auto& cell : liveCells) {
        field.field[cell.first][cell.second] = INT_LIVE_CELL; // Set живые клетки
    }
    return field;
}


TEST_CASE("NextGeneration applies rules correctly", "[NextGeneration]") {
    Game_Of_Life game; // Create a Game_Of_Life object

    SECTION("Live cell with fewer than 2 live neighbors dies") {
        // Arrange
        Field field = createField(3, 3, { {1, 1} }); // Single live cell

        // Act
        game.NextGeneration(field); // Apply one generation

        // Assert
        REQUIRE(field.field[1][1] == INT_DEATH_CELL); // Cell at (1,1) should die
    }

    SECTION("Live cell with 2 live neighbors survives") {
        // Arrange
        Field field = createField(3, 3, { {0, 0}, {0, 1}, {1, 0} }); // Live cell at (1,1) with 2 neighbors

        // Act
        game.NextGeneration(field); // Apply one generation

        // Assert
        REQUIRE(field.field[1][1] == INT_LIVE_CELL); // Cell at (1,1) should survive
    }

    SECTION("Live cell with 3 live neighbors survives") {
        // Arrange
        Field field = createField(3, 3, { {0, 0}, {0, 1}, {1, 0}, {1, 1} }); // Live cell at (1,1) with 3 neighbors

        // Act
        game.NextGeneration(field); // Apply one generation

        // Assert
        REQUIRE(field.field[1][1] == INT_LIVE_CELL); // Cell at (1,1) should survive
    }

    SECTION("Live cell with more than 3 live neighbors dies") {
        // Arrange
        Field field = createField(3, 3, {
            {0, 0}, {0, 1}, {0, 2},
            {1, 0}, {1, 1} // Live cell at 1,1 with 4 neighbors
            });

        // Act
        game.NextGeneration(field); // Apply one generation

        // Assert
        REQUIRE(field.field[1][1] == INT_DEATH_CELL); // Cell at (1,1) should die
    }

    SECTION("Dead cell with exactly 3 live neighbors becomes alive") {
        // Arrange
        Field field = createField(3, 3, { {0, 0}, {0, 1}, {1, 0} }); // Dead cell at (1,1) with 3 neighbors

        // Act
        game.NextGeneration(field); // Apply one generation

        // Assert
        REQUIRE(field.field[1][1] == INT_LIVE_CELL); // Cell at (1,1) should become alive
    }

    SECTION("Equality flag set when board doesn't change - BLOCK") {
        // Arrange
        Field field = createField(3, 3, { {0, 0}, {0, 1}, {1, 0}, {1, 1} }); // Block configuration
        game.FlagEquality = false; // Setting to false to ensure it will be set to true in function

        // Act
        game.NextGeneration(field); // Apply one generation

        // Assert
        REQUIRE(game.FlagEquality == TRUE_FLAGE_QUALITY); // Should be equal after one generation
    }

    SECTION("Equality flag set when board changes - BLINKER") {
        // Arrange
        Field field = createField(3, 3, { {1, 0}, {1, 1}, {1, 2} }); // Blinker configuration
        game.FlagEquality = true; // Setting to true to ensure it will be set to false in function

        // Act
        game.NextGeneration(field); // Apply one generation

        // Assert
        REQUIRE(game.FlagEquality == false); // Should be changed after one generation
    }
}