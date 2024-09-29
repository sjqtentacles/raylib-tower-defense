#include <stddef.h>       // Include for NULL
#include "raylib.h"
#include "map.h"          // For drawing the grid
#include "towers.h"       // Tower-related logic
#include "input.h"        // Input-related logic
#include "hud.h"          // HUD drawing functions
#include "tower_panel.h"  // Tower panel functions
#include "tower_config.h" // Tower configurations
#include "tower_logic.h"  // Tower placement logic

#define INITIAL_GOLD 10000
#define INITIAL_SANITY 500

// Player resources
int playerGold = INITIAL_GOLD;
int playerSanity = INITIAL_SANITY;

Tower availableTowers[5]; // Array to store configured towers
int towerCount = 0;       // Number of configured towers

int main(void) {
    const int gridWidth = 20;
    const int gridHeight = 15;
    const int cellSize = 40;
    const int windowWidth = gridWidth * cellSize;
    const int windowHeight = gridHeight * cellSize + 100;  // Add space for HUD

    InitWindow(windowWidth, windowHeight, "Tower Defense with Modular HUD");
    SetTargetFPS(60);

    // Initialize towers
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
                Vector2 gridPos = GetMouseGridPosition(cellSize);
                PlaceTower(currentTowerIndex, gridPos, &playerGold, &playerSanity);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Draw2DGrid(gridWidth, gridHeight, cellSize);
        DrawTowers(cellSize, NULL);  // Simplified: You can modify to pass selectedTower if needed

        // Draw HUD (left for stats, right for towers)
        DrawHUD(windowWidth, windowHeight, playerGold, playerSanity);
        DrawTowerPanel(windowWidth, windowHeight, playerGold, playerSanity);

        EndDrawing();
    }

    CloseWindow();
}
