#include <stddef.h>
#include "raylib.h"
#include "map.h"
#include "towers.h"
#include "input.h"
#include "hud.h"
#include "tower_panel.h"
#include "tower_config.h"
#include "tower_logic.h"

#define INITIAL_GOLD 10000
#define INITIAL_SANITY 500
#define MAX_LEVEL 3  // Example: 3 levels

// Player resources
int playerGold = INITIAL_GOLD;
int playerSanity = INITIAL_SANITY;
int currentLevel = 1;
bool gameOver = false;

Tower availableTowers[5];  // Array to store configured towers
int towerCount = 0;        // Number of configured towers

void AdvanceLevel() {
    if (currentLevel < MAX_LEVEL) {
        currentLevel++;
        playerGold = INITIAL_GOLD;
        playerSanity = INITIAL_SANITY;
    } else {
        gameOver = true;  // End game after the last level
    }
}

int main(void) {
    Path currentPath = GeneratePathForLevel(currentLevel);
    int windowWidth = currentPath.gridWidth * currentPath.cellSize;
    int windowHeight = currentPath.gridHeight * currentPath.cellSize + 100;  // Add space for HUD

    InitWindow(windowWidth, windowHeight, "Tower Defense with Multiple Levels");
    SetTargetFPS(60);

    InitializeTowers();
    ConfigureTowers(availableTowers, &towerCount);

    int currentTowerIndex = -1;  // No tower selected initially

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        // Handle tower selection and placement
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (mousePos.y > windowHeight - 100) {
                currentTowerIndex = (mousePos.x - (windowWidth / 3)) / (towerButtonWidth + towerButtonSpacing);
                if (currentTowerIndex >= towerCount) {
                    currentTowerIndex = -1;
                }
            } else if (currentTowerIndex != -1) {
                Vector2 gridPos = GetMouseGridPosition(currentPath.cellSize);
                PlaceTower(currentTowerIndex, gridPos, &playerGold, &playerSanity, currentPath);
            }
        }

        // Advance to the next level when the player presses Enter
        if (IsKeyPressed(KEY_ENTER)) {
            FreePath(currentPath);
            AdvanceLevel();
            currentPath = GeneratePathForLevel(currentLevel);
            windowWidth = currentPath.gridWidth * currentPath.cellSize;
            windowHeight = currentPath.gridHeight * currentPath.cellSize + 100;
            SetWindowSize(windowWidth, windowHeight);  // Adjust window size for new level
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Draw2DGrid(currentPath.gridWidth, currentPath.gridHeight, currentPath.cellSize);
        DrawPathAndGoal(currentPath);
        DrawTowers(currentPath.cellSize, NULL);  // Simplified: You can modify to pass selectedTower if needed

        // Draw HUD (left for stats, right for towers)
        DrawHUD(windowWidth, windowHeight, playerGold, playerSanity);
        DrawTowerPanel(windowWidth, windowHeight, playerGold, playerSanity);

        EndDrawing();

        if (gameOver) {
            break;  // Exit the loop when the game is over
        }
    }

    FreePath(currentPath);
    CloseWindow();
}
