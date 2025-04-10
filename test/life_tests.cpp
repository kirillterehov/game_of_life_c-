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
        Field field = createField(25, 80, { {1, 1} }); // Single live cell

        // Act
        game.NextGeneration(field); // Apply one generation

        // Assert
        REQUIRE(field.field[1][1] == INT_DEATH_CELL); // Cell at (1,1) should die
    }

    SECTION("Live cell with 2 live neighbors survives") {
        // Arrange
        Field field = createField(25, 80, { {0, 0}, {0, 1}, {1, 0} });

        // Act
        game.NextGeneration(field);

        // Assert
        REQUIRE(field.field[1][1] == INT_LIVE_CELL);
    }

    SECTION("Live cell with 3 live neighbors survives") {
        // Arrange
        Field field = createField(25, 80, { {0, 0}, {0, 1}, {1, 0}, {1, 1} });
        // Act
        game.NextGeneration(field);
        // Assert
        REQUIRE(field.field[1][1] == INT_LIVE_CELL);
    }

    SECTION("Live cell with more than 3 live neighbors dies") {
        // Arrange
        Field field = createField(25, 80, {
            {0, 0}, {0, 1}, {0, 2},
            {1, 0}, {1, 1}
            });
        // Act
        game.NextGeneration(field);
        // Assert
        REQUIRE(field.field[1][1] == INT_DEATH_CELL);
    }

    SECTION("Dead cell with exactly 3 live neighbors becomes alive") {
        // Arrange
        Field field = createField(25, 80, { {0, 0}, {0, 1}, {1, 0} });
        // Act
        game.NextGeneration(field);
        // Assert
        REQUIRE(field.field[1][1] == INT_LIVE_CELL);
    }

    SECTION("Equality flag set when board doesn't change - BLOCK") {
        // Arrange
        Field field = createField(25, 80, { {0, 0}, {0, 1}, {1, 0}, {1, 1} });
        game.FlagEquality = false;

        // Act
        game.NextGeneration(field);
        // Assert
        REQUIRE(game.FlagEquality == TRUE_FLAGE_QUALITY);
    }

    SECTION("Equality flag set when board changes - BLINKER") {
        // Arrange
        Field field = createField(25, 80, { {1, 0}, {1, 1}, {1, 2} });
        game.FlagEquality = true;

        // Act
        game.NextGeneration(field);
        // Assert
        REQUIRE(game.FlagEquality == false);
    }
}