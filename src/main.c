// main.c
#include "raylib.h"
#include "map.h"
#include "towers.h"
#include "input.h"
#include "hud.h"
#include "tower_panel.h"
#include "tower_config.h"
#include "tower_logic.h"
#include "menu.h"
#include <stddef.h>
#include <stdbool.h>  // For bool type
#include <stdio.h>    // For printf (optional, for debugging)

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

Tower* selectedTower = NULL;  // Track the currently selected tower
GameState gameState = GAME_RUNNING;  // Track the current state (running, paused, exit)

Path currentPath;  // Store the current path

// Function to initialize a level (including path and resources)
void InitializeLevel() {
    // Generate path for the current level
    currentPath = GeneratePathForLevel(currentLevel);

    // Reset player resources
    playerGold = INITIAL_GOLD;
    playerSanity = INITIAL_SANITY;

    // Debug: Indicate that level is initialized
    printf("Initializing Level %d\n", currentLevel);
}

void AdvanceLevel() {
    if (currentLevel < MAX_LEVEL) {
        currentLevel++;

        // Free the previous path memory
        FreePath(currentPath);

        // Initialize the new level
        InitializeLevel();
    } else {
        gameOver = true;  // End game after the last level
    }
}

int main(void) {
    // Initialize towers
    InitializeTowers();
    ConfigureTowers(availableTowers, &towerCount);

    // Initialize the first level
    InitializeLevel();

    int windowWidth = currentPath.gridWidth * currentPath.cellSize;
    int windowHeight = currentPath.gridHeight * currentPath.cellSize + 100;  // Add space for HUD

    InitWindow(windowWidth, windowHeight, "Tower Defense with Multiple Levels");
    
    // Disable default ESC key behavior
    SetExitKey(0);
    
    SetTargetFPS(60);

    int currentTowerIndex = -1;  // No tower selected initially

    // Flag to prevent immediate processing of Enter key after resuming
    bool skipNextEnterPress = false;

    while (!WindowShouldClose()) {
        if (gameState == GAME_RUNNING) {

            Vector2 mousePos = GetMousePosition();
            Vector2 gridPos = GetMouseGridPosition(currentPath.cellSize);

            // Handle tower selection and placement
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

                if (mousePos.y > windowHeight - 100) {
                    // Select a tower from the UI panel
                    currentTowerIndex = (mousePos.x - (windowWidth / 3)) / (towerButtonWidth + towerButtonSpacing);
                    if (currentTowerIndex >= towerCount) {
                        currentTowerIndex = -1;
                    }
                } else if (currentTowerIndex != -1) {
                    // Place a tower and reset selection
                    PlaceTower(currentTowerIndex, gridPos, &playerGold, &playerSanity, currentPath);
                    selectedTower = NULL;  // Do not show the placed tower's stats immediately
                    currentTowerIndex = -1;  // Reset tower selection after placement
                } else {
                    // Check if a tower is clicked
                    Tower* clickedTower = GetTowerAtPosition(gridPos);
                    if (clickedTower == selectedTower) {
                        // If clicking the selected tower again, toggle stats off
                        selectedTower = NULL;
                    } else {
                        // Select the new tower
                        selectedTower = clickedTower;
                    }
                }
            }

            // Check for pause (ESC key)
            if (IsKeyPressed(KEY_ESCAPE)) {
                gameState = GAME_PAUSED;  // Switch to paused state
            }

            // Advance to the next level when the player presses Enter
            if (IsKeyPressed(KEY_ENTER)) {
                if (!skipNextEnterPress) {
                    AdvanceLevel();  // Move to the next level

                    if (!gameOver) {
                        // Adjust window size for new level
                        windowWidth = currentPath.gridWidth * currentPath.cellSize;
                        windowHeight = currentPath.gridHeight * currentPath.cellSize + 100;
                        SetWindowSize(windowWidth, windowHeight);
                    }
                }
                // Reset the skip flag after processing
                skipNextEnterPress = false;
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            Draw2DGrid(currentPath.gridWidth, currentPath.gridHeight, currentPath.cellSize);
            DrawPathAndGoal(currentPath);
            DrawTowers(currentPath.cellSize, selectedTower);  // Pass selectedTower to show its radius and stats

            // Draw HUD (left for stats, right for towers)
            DrawHUD(windowWidth, windowHeight, playerGold, playerSanity);
            DrawTowerPanel(windowWidth, windowHeight, playerGold, playerSanity);

            EndDrawing();

            if (gameOver) {
                break;  // Exit the loop when the game is over
            }
        } else if (gameState == GAME_PAUSED) {
            BeginDrawing();
            ClearBackground(BLACK);

            DrawPauseMenu(windowWidth, windowHeight);  // Draw the pause menu

            EndDrawing();

            // Handle input for pause menu
            GameState newState = HandlePauseMenuInput();

            if (newState == GAME_RUNNING) {
                gameState = GAME_RUNNING;  // Resume the game
                skipNextEnterPress = true;  // Set flag to skip Enter press in the next frame
            } else if (newState == GAME_EXIT) {
                gameState = GAME_EXIT;      // Exit the game
            }
            // If newState is still GAME_PAUSED, remain in pause state

            // Handle GAME_EXIT state
            if (gameState == GAME_EXIT) {
                break;  // Exit the loop to close the game
            }
        }
    }

    // Free the path memory before closing
    FreePath(currentPath);
    CloseWindow();

    return 0;
}
