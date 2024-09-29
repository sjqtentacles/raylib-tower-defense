#include "towers.h"
#include "raylib.h"
#include <stddef.h>

static Tower towers[MAX_TOWERS]; // Internal storage for towers
static int towerCount = 0;       // Internal tower count

// Initialize the tower array
void InitializeTowers() {
    towerCount = 0;  // Reset tower count at the start
}


// Add a tower to the array
void AddTower(Vector2 position, int range, int damage, int rateOfFire, DamageType damageType, int goldCost, int specialCost, FirePattern firePattern) {
    if (towerCount < MAX_TOWERS) {  // Ensure we don't exceed the maximum tower limit
        towers[towerCount].position = position;
        towers[towerCount].range = range;
        towers[towerCount].damage = damage;
        towers[towerCount].rateOfFire = rateOfFire;
        towers[towerCount].damageType = damageType;
        towers[towerCount].goldCost = goldCost;
        towers[towerCount].specialCost = specialCost;
        towers[towerCount].firePattern = firePattern;

        towerCount++;  // Increment tower count correctly
    } else {
        DrawText("Max towers reached!", 10, 10, 20, RED);  // Optional: Display warning if max towers reached
    }
}


// Get a tower at the specific grid position
Tower* GetTowerAtPosition(Vector2 gridPos) {
    for (int i = 0; i < towerCount; i++) {
        if (towers[i].position.x == gridPos.x && towers[i].position.y == gridPos.y) {
            return &towers[i]; // Return the pointer to the tower
        }
    }
    return NULL; // No tower found at this position
}

// Draw all towers, and draw stats for the selected tower if any
void DrawTowers(int cellSize, Tower *selectedTower) {
    for (int i = 0; i < towerCount; i++) {
        // Draw each tower as a blue circle in the center of the cell
        Vector2 center = (Vector2){ towers[i].position.x * cellSize + cellSize / 2, 
                                    towers[i].position.y * cellSize + cellSize / 2 };
        DrawCircleV(center, cellSize / 3, BLUE);

        // Optionally, draw the tower's range as a circle
        DrawCircleLines(center.x, center.y, towers[i].range * cellSize, DARKGRAY);
    }

    // Draw stats for the selected tower if one is selected
    if (selectedTower != NULL) {
        Vector2 center = (Vector2){ selectedTower->position.x * cellSize + cellSize / 2, 
                                    selectedTower->position.y * cellSize + cellSize / 2 };
        // Draw text indicating the tower's stats
        DrawText(TextFormat("Range: %d", selectedTower->range), center.x - 40, center.y - 20, 10, BLACK);
        DrawText(TextFormat("Dmg: %d, ROF: %d", selectedTower->damage, selectedTower->rateOfFire), 
                 center.x - 40, center.y - 10, 10, BLACK);
        DrawText(TextFormat("Dmg Type: %s", (selectedTower->damageType == DAMAGE_TYPE_PSCHIC) ? "Psychic" : "Material"), 
                 center.x - 40, center.y, 10, BLACK);
    }
}
