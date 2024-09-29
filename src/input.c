// input.c
#include "input.h"
#include "raylib.h"

// Get the grid position from the mouse position based on cell size
Vector2 GetMouseGridPosition(int cellSize) {
    Vector2 mousePos = GetMousePosition();
    int gridX = mousePos.x / cellSize;
    int gridY = mousePos.y / cellSize;
    return (Vector2){ gridX, gridY };
}
