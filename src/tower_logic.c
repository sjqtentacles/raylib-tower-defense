#include "tower_logic.h"
#include "map.h"
#include <stddef.h>

extern Tower availableTowers[5];  // Externally declared tower configurations

void PlaceTower(int towerIndex, Vector2 gridPos, int *playerGold, int *playerSanity, Path path) {
    const Tower* selectedTower = &availableTowers[towerIndex];

    // Check if a tower already exists at the position
    if (GetTowerAtPosition(gridPos) != NULL) {
        DrawText("Tower already exists at this location!", 10, 10, 20, RED);
        return;
    }

    // Ensure the tower isn't placed on or too close to the path
    if (!IsPositionOnPath(gridPos, path) &&
        *playerGold >= selectedTower->goldCost && 
        *playerSanity >= selectedTower->specialCost) {

        // Pass towerIndex when adding the tower
        AddTower(gridPos, selectedTower->range, selectedTower->damage, selectedTower->rateOfFire, 
                 selectedTower->damageType, selectedTower->goldCost, selectedTower->specialCost, 
                 selectedTower->firePattern, towerIndex);

        *playerGold -= selectedTower->goldCost;
        *playerSanity -= selectedTower->specialCost;
    } else {
        DrawText("Cannot place tower on or near the path!", 10, 10, 20, RED);
    }
}
