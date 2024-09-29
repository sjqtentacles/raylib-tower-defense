// map.c
#include "map.h"
#include "raylib.h"

// Function to draw a black and white 2D grid with the given cell size
void Draw2DGrid(int gridWidth, int gridHeight, int cellSize) {
    // Draw vertical lines
    for (int i = 0; i <= gridWidth; i++) {
        DrawLine(i*cellSize, 0, i*cellSize, gridHeight*cellSize, BLACK);
    }

    // Draw horizontal lines
    for (int i = 0; i <= gridHeight; i++) {
        DrawLine(0, i*cellSize, gridWidth*cellSize, i*cellSize, BLACK);
    }
}