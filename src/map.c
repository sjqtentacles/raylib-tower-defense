#include "map.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>  // For dynamic memory allocation
#include <math.h>

// Function to draw a black and white 2D grid with the given cell size
void Draw2DGrid(int gridWidth, int gridHeight, int cellSize) {
    for (int i = 0; i <= gridWidth; i++) {
        DrawLine(i * cellSize, 0, i * cellSize, gridHeight * cellSize, BLACK);
    }

    for (int i = 0; i <= gridHeight; i++) {
        DrawLine(0, i * cellSize, gridWidth * cellSize, i * cellSize, BLACK);
    }
}

// Function to draw the path and goal
void DrawPathAndGoal(Path path) {
    // Draw the path by connecting the waypoints
    for (int i = 0; i < path.length - 1; i++) {
        Vector2 start = { path.waypoints[i].x * path.cellSize + path.cellSize / 2, path.waypoints[i].y * path.cellSize + path.cellSize / 2 };
        Vector2 end = { path.waypoints[i + 1].x * path.cellSize + path.cellSize / 2, path.waypoints[i + 1].y * path.cellSize + path.cellSize / 2 };
        DrawLineEx(start, end, 5, BLUE);
    }

    // Draw the goal as a red square at the last waypoint
    Vector2 goal = path.waypoints[path.length - 1];
    DrawRectangle(goal.x * path.cellSize, goal.y * path.cellSize, path.cellSize, path.cellSize, RED);
}

bool IsPointOnLineSegment(Vector2 point, Vector2 lineStart, Vector2 lineEnd) {
    // Calculate the distance from the point to the line segment
    float dist1 = Vector2Distance(point, lineStart);
    float dist2 = Vector2Distance(point, lineEnd);
    float lineDist = Vector2Distance(lineStart, lineEnd);
    
    // Check if the point lies exactly on the line (with some tolerance)
    return (fabs(dist1 + dist2 - lineDist) < 0.1f); // 0.1f as tolerance
}

// Function to calculate the perpendicular distance from a point to a line segment
float DistanceToSegment(Vector2 point, Vector2 lineStart, Vector2 lineEnd) {
    float lineLengthSquared = pow(Vector2Distance(lineStart, lineEnd), 2);
    if (lineLengthSquared == 0) {
        return Vector2Distance(point, lineStart);  // lineStart == lineEnd, so it's just the distance to the point
    }

    // Project the point onto the line (parameterized by t)
    float t = ((point.x - lineStart.x) * (lineEnd.x - lineStart.x) + 
               (point.y - lineStart.y) * (lineEnd.y - lineStart.y)) / lineLengthSquared;

    // Clamp t to the range [0, 1] to limit the projection to the line segment
    t = fmax(0, fmin(1, t));

    // Find the closest point on the segment
    Vector2 projection = {
        lineStart.x + t * (lineEnd.x - lineStart.x),
        lineStart.y + t * (lineEnd.y - lineStart.y)
    };

    // Return the distance from the point to the closest point on the segment
    return Vector2Distance(point, projection);
}

bool IsPositionOnPath(Vector2 gridPos, Path path) {
    // Loop through all waypoints and the segments connecting them
    for (int i = 0; i < path.length - 1; i++) {
        // Get the current waypoint and the next waypoint
        Vector2 start = path.waypoints[i];
        Vector2 end = path.waypoints[i + 1];

        // Handle horizontal path segments
        if (start.y == end.y) {
            int xStart = fmin(start.x, end.x);
            int xEnd = fmax(start.x, end.x);
            if ((int)gridPos.y == (int)start.y && (int)gridPos.x >= xStart && (int)gridPos.x <= xEnd) {
                return true; // The grid position is on a horizontal segment of the path
            }
        }

        // Handle vertical path segments
        if (start.x == end.x) {
            int yStart = fmin(start.y, end.y);
            int yEnd = fmax(start.y, end.y);
            if ((int)gridPos.x == (int)start.x && (int)gridPos.y >= yStart && (int)gridPos.y <= yEnd) {
                return true; // The grid position is on a vertical segment of the path
            }
        }
    }

    // If no match is found, the position is not on the path
    return false;
}



// Helper function to generate paths and grid sizes for different levels
Path GeneratePathForLevel(int level) {
    Path path;

    if (level == 1) {
        path.gridWidth = 20;
        path.gridHeight = 15;
        path.cellSize = 40;
        path.length = 6;
        path.waypoints = malloc(path.length * sizeof(Vector2));
        path.waypoints[0] = (Vector2){ 1, 1 };
        path.waypoints[1] = (Vector2){ 5, 1 };
        path.waypoints[2] = (Vector2){ 5, 5 };
        path.waypoints[3] = (Vector2){ 10, 5 };
        path.waypoints[4] = (Vector2){ 10, 10 };
        path.waypoints[5] = (Vector2){ 15, 10 };
    } else if (level == 2) {
        path.gridWidth = 25;
        path.gridHeight = 18;
        path.cellSize = 35;
        path.length = 5;
        path.waypoints = malloc(path.length * sizeof(Vector2));
        path.waypoints[0] = (Vector2){ 0, 3 };
        path.waypoints[1] = (Vector2){ 3, 3 };
        path.waypoints[2] = (Vector2){ 6, 7 };
        path.waypoints[3] = (Vector2){ 10, 7 };
        path.waypoints[4] = (Vector2){ 15, 12 };
    } else {
        path.gridWidth = 30;
        path.gridHeight = 20;
        path.cellSize = 30;
        path.length = 4;
        path.waypoints = malloc(path.length * sizeof(Vector2));
        path.waypoints[0] = (Vector2){ 2, 2 };
        path.waypoints[1] = (Vector2){ 5, 10 };
        path.waypoints[2] = (Vector2){ 8, 8 };
        path.waypoints[3] = (Vector2){ 12, 12 };
    }

    return path;
}

void FreePath(Path path) {
    free(path.waypoints);
}
