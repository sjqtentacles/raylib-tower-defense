#include "raylib.h"

void DrawHUD(int windowWidth, int windowHeight, int playerGold, int playerSanity) {
    int hudHeight = 100;
    int leftWidth = windowWidth / 3;
    
    DrawRectangle(0, windowHeight - hudHeight, leftWidth, hudHeight, DARKGRAY);
    DrawText(TextFormat("Gold: %d", playerGold), 10, windowHeight - hudHeight + 20, 20, RAYWHITE);
    DrawText(TextFormat("Sanity: %d", playerSanity), 10, windowHeight - hudHeight + 50, 20, RAYWHITE);
}
