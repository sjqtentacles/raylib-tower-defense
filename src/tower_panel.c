#include "raylib.h"
#include "tower_config.h"

extern Tower availableTowers[5];
extern int towerCount;

int towerPanelOffset = 0;
int towerButtonWidth = 80;
int towerButtonSpacing = 10;

bool CanPlaceTower(int playerGold, int playerSanity, const Tower* tower) {
    return (playerGold >= tower->goldCost && playerSanity >= tower->specialCost);
}

void DrawTowerButton(const Rectangle buttonBounds, const Tower* tower, bool canPlace, bool isHovered) {
    Color buttonColor = canPlace ? GREEN : DARKGRAY;
    DrawRectangleRec(buttonBounds, buttonColor);

    if (isHovered) {
        DrawRectangleLinesEx(buttonBounds, 2, YELLOW);
    }

    DrawText(TextFormat("Tower %d", (int)(tower - availableTowers + 1)), buttonBounds.x + 10, buttonBounds.y + 30, 10, BLACK);
}

void DrawTowerPanel(int windowWidth, int windowHeight, int playerGold, int playerSanity) {
    const int hudHeight = 100;
    const int rightPanelWidth = windowWidth - (windowWidth / 3);

    const int panelX = windowWidth / 3;
    const int panelY = windowHeight - hudHeight;

    DrawRectangle(panelX, panelY, rightPanelWidth, hudHeight, LIGHTGRAY);

    Vector2 mousePos = GetMousePosition();

    for (int i = 0; i < towerCount; i++) {
        int buttonX = panelX + i * (towerButtonWidth + towerButtonSpacing) - towerPanelOffset;
        Rectangle buttonBounds = { buttonX, panelY + 20, towerButtonWidth, towerButtonWidth };

        bool canPlace = CanPlaceTower(playerGold, playerSanity, &availableTowers[i]);
        bool isHovered = CheckCollisionPointRec(mousePos, buttonBounds);

        DrawTowerButton(buttonBounds, &availableTowers[i], canPlace, isHovered);
    }
}
