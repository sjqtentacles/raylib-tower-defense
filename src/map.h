// map.h
#ifndef MAP_H
#define MAP_H

#include "raylib.h"

// Structure representing a path in the map
typedef struct Path {
    Vector2* waypoints;  // Dynamic array of waypoints
    int length;          // Number of waypoints
    int gridWidth;       // Grid width for this map
    int gridHeight;      // Grid height for this map
    int cellSize;        // Cell size for this map
} Path;

// Function to draw the 2D grid
void Draw2DGrid(int gridWidth, int gridHeight, int cellSize);

// Function to draw the path and goal
void DrawPathAndGoal(Path path);

// Function to generate a path for the specified level
Path GeneratePathForLevel(int level);

// Function to free the allocated memory for a path
void FreePath(Path path);

// Function to check if a grid position is on the path
bool IsPositionOnPath(Vector2 gridPos, Path path);

#endif // MAP_H
