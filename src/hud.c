#include "raylib.h"

// Function to draw the HUD and player stats
void DrawHUD(int windowWidth, int windowHeight, int playerGold, int playerSanity) {
    // Draw the player stats on the left, 1/3 of the screen width
    int hudHeight = 100;
    int leftWidth = windowWidth / 3;
    
    DrawRectangle(0, windowHeight - hudHeight, leftWidth, hudHeight, DARKGRAY);
    DrawText(TextFormat("Gold: %d", playerGold), 10, windowHeight - hudHeight + 20, 20, RAYWHITE);
    DrawText(TextFormat("Sanity: %d", playerSanity), 10, windowHeight - hudHeight + 50, 20, RAYWHITE);
}
