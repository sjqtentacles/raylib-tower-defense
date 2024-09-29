// menu.h
#ifndef MENU_H
#define MENU_H

// Enum to manage the current state of the game
typedef enum {
    GAME_RUNNING,
    GAME_PAUSED,
    GAME_EXIT
} GameState;

// Function to draw the pause menu
void DrawPauseMenu(int windowWidth, int windowHeight);

// Function to handle input for the pause menu
GameState HandlePauseMenuInput();

#endif // MENU_H
