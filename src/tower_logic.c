#include "tower_logic.h"
#include "map.h"

extern Tower availableTowers[5];  // Externally declared tower configurations

void PlaceTower(int towerIndex, Vector2 gridPos, int *playerGold, int *playerSanity, Path path) {
    const Tower* selectedTower = &availableTowers[towerIndex];

    // Check if the position is not on or near the path before placing the tower
    if (!IsPositionOnPath(gridPos, path)) {
        if (*playerGold >= selectedTower->goldCost && *playerSanity >= selectedTower->specialCost) {
            AddTower(gridPos, selectedTower->range, selectedTower->damage, selectedTower->rateOfFire, 
                     selectedTower->damageType, selectedTower->goldCost, selectedTower->specialCost, selectedTower->firePattern);

            *playerGold -= selectedTower->goldCost;
            *playerSanity -= selectedTower->specialCost;
        }
    } else {
        // If trying to place a tower on or too close to the path, show an error
        DrawText("Cannot place tower on or near the path!", 10, 10, 20, RED);
    }
}
