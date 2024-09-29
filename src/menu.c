#include "menu.h"
#include "raylib.h"

static int selectedOption = 0;  // 0 = Resume, 1 = Exit

void DrawPauseMenu(int windowWidth, int windowHeight) {
    // Draw semi-transparent background
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.6f));
    
    // Draw menu box
    int menuWidth = 200;
    int menuHeight = 150;
    int menuX = (windowWidth - menuWidth) / 2;
    int menuY = (windowHeight - menuHeight) / 2;

    DrawRectangle(menuX, menuY, menuWidth, menuHeight, DARKGRAY);
    
    // Highlight the selected option
    Color resumeColor = (selectedOption == 0) ? YELLOW : WHITE;
    Color exitColor = (selectedOption == 1) ? YELLOW : WHITE;
    
    // Draw "Resume" and "Exit" options
    DrawText("Resume", menuX + 50, menuY + 30, 20, resumeColor);
    DrawText("Exit", menuX + 50, menuY + 80, 20, exitColor);
}

GameState HandlePauseMenuInput() {
    // Switch between options
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        selectedOption = (selectedOption + 1) % 2;  // Cycle through options
    }
    
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        selectedOption = (selectedOption - 1 + 2) % 2;  // Cycle through options
    }

    // Handle selection
    if (IsKeyPressed(KEY_ENTER)) {
        if (selectedOption == 0) {
            return GAME_RUNNING;  // Resume the game
        } else if (selectedOption == 1) {
            return GAME_EXIT;  // Exit the game
        }
    }

    return GAME_PAUSED;  // Stay in pause mode if no valid input is detected
}
