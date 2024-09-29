#include "raylib.h"
#include "tower_config.h"

// Declare that availableTowers is defined elsewhere
extern Tower availableTowers[5];  // The array of available towers
extern int towerCount;            // Number of available towers

int towerPanelOffset = 0;         // Offset for scrolling
int towerButtonWidth = 80;
int towerButtonSpacing = 10;

// Helper function to determine if the tower can be placed
bool CanPlaceTower(int playerGold, int playerSanity, const Tower* tower) {
    return (playerGold >= tower->goldCost && playerSanity >= tower->specialCost);
}

// Helper function to draw a single tower button
void DrawTowerButton(const Rectangle buttonBounds, const Tower* tower, bool canPlace, bool isHovered) {
    Color buttonColor = canPlace ? GREEN : DARKGRAY;
    DrawRectangleRec(buttonBounds, buttonColor);

    // If hovered, add a highlight around the button
    if (isHovered) {
        DrawRectangleLinesEx(buttonBounds, 2, YELLOW);
    }

    // Draw the tower label in the center
    DrawText(TextFormat("Tower %d", tower - availableTowers + 1), buttonBounds.x + 10, buttonBounds.y + 30, 10, BLACK);
}

// Main function to draw the tower panel
void DrawTowerPanel(int windowWidth, int windowHeight, int playerGold, int playerSanity) {
    const int hudHeight = 100;
    const int rightPanelWidth = windowWidth - (windowWidth / 3); // 2/3 for tower panel

    // Define the scrollable area for tower buttons
    const int panelX = windowWidth / 3;
    const int panelY = windowHeight - hudHeight;

    DrawRectangle(panelX, panelY, rightPanelWidth, hudHeight, LIGHTGRAY);

    Vector2 mousePos = GetMousePosition();

    // Iterate over all available towers and draw the respective buttons
    for (int i = 0; i < towerCount; i++) {
        int buttonX = panelX + i * (towerButtonWidth + towerButtonSpacing) - towerPanelOffset;
        Rectangle buttonBounds = { buttonX, panelY + 20, towerButtonWidth, towerButtonWidth };

        bool canPlaceTower = CanPlaceTower(playerGold, playerSanity, &availableTowers[i]);
        bool isHovered = CheckCollisionPointRec(mousePos, buttonBounds);

        DrawTowerButton(buttonBounds, &availableTowers[i], canPlaceTower, isHovered);
    }
}
