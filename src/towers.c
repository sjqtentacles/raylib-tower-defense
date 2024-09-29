#include "towers.h"
#include "raylib.h"
#include <stddef.h>  // For NULL

static Tower towers[MAX_TOWERS];
static int towerCount = 0;

void InitializeTowers() {
    towerCount = 0;
}

// Add missing Vector2Equals function
bool Vector2Equals(Vector2 a, Vector2 b) {
    return a.x == b.x && a.y == b.y;
}

void AddTower(Vector2 position, int range, int damage, int rateOfFire, DamageType damageType, int goldCost, int specialCost, FirePattern firePattern, int towerIndex) {
    if (towerCount < MAX_TOWERS) {
        towers[towerCount] = (Tower){ position, range, damage, rateOfFire, damageType, goldCost, specialCost, firePattern, towerIndex };
        towerCount++;
    } else {
        DrawText("Max towers reached!", 10, 10, 20, RED);
    }
}

Tower* GetTowerAtPosition(Vector2 gridPos) {
    for (int i = 0; i < towerCount; i++) {
        if (Vector2Equals(towers[i].position, gridPos)) {
            return &towers[i];
        }
    }
    return NULL;
}

void DrawTowerStatsWithBackground(Tower *tower, int cellSize) {
    Vector2 center = (Vector2){ tower->position.x * cellSize + cellSize / 2, tower->position.y * cellSize + cellSize / 2 };
    int textX = center.x - 40;
    int textY = center.y - 30;

    // Draw background rectangle
    DrawRectangle(textX - 5, textY - 5, 150, 50, Fade(LIGHTGRAY, 0.8f));  // Semi-transparent background

    // Draw the tower stats
    DrawText(TextFormat("Range: %d", tower->range), textX, textY, 10, BLACK);
    DrawText(TextFormat("Dmg: %d, ROF: %d", tower->damage, tower->rateOfFire), textX, textY + 10, 10, BLACK);
    DrawText(TextFormat("Dmg Type: %s", (tower->damageType == DAMAGE_TYPE_PSCHIC) ? "Psychic" : "Material"), textX, textY + 20, 10, BLACK);
}

void DrawTowerShape(Tower* tower, Vector2 center, int cellSize) {
    switch (tower->towerIndex) {
        case 0:
            // Tower 1: Blue Circle
            DrawCircleV(center, cellSize / 3, BLUE);
            break;
        case 1:
            // Tower 2: Red Square
            DrawRectangle(center.x - cellSize / 3, center.y - cellSize / 3, cellSize / 1.5, cellSize / 1.5, RED);
            break;
        case 2:
            // Tower 3: Green Triangle
            DrawTriangle(
                (Vector2){center.x, center.y - cellSize / 3}, 
                (Vector2){center.x - cellSize / 3, center.y + cellSize / 3},
                (Vector2){center.x + cellSize / 3, center.y + cellSize / 3},
                GREEN
            );
            break;
        case 3:
            // Tower 4: Yellow Diamond
            DrawPoly(center, 4, cellSize / 2.5, 45.0f, ORANGE);
            break;
        case 4:
            // Tower 5: Purple X
            DrawLineEx((Vector2){center.x - cellSize / 3, center.y - cellSize / 3}, (Vector2){center.x + cellSize / 3, center.y + cellSize / 3}, 3, PURPLE);
            DrawLineEx((Vector2){center.x + cellSize / 3, center.y - cellSize / 3}, (Vector2){center.x - cellSize / 3, center.y + cellSize / 3}, 3, PURPLE);
            break;
        default:
            break;
    }
}


void DrawTowers(int cellSize, Tower *selectedTower) {
    for (int i = 0; i < towerCount; i++) {
        Vector2 center = (Vector2){ towers[i].position.x * cellSize + cellSize / 2, towers[i].position.y * cellSize + cellSize / 2 };
        
        // Draw different shapes based on tower type
        DrawTowerShape(&towers[i], center, cellSize);

        // Draw range if the tower is selected
        if (selectedTower == &towers[i]) {
            DrawCircleLines(center.x, center.y, towers[i].range * cellSize, DARKGRAY);
        }
    }

    // If a tower is selected, draw its stats with a background
    if (selectedTower) {
        DrawTowerStatsWithBackground(selectedTower, cellSize);
    }
}
