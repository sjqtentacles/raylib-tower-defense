#include "tower_logic.h"

extern Tower availableTowers[5];  // Externally declared tower configurations

void PlaceTower(int towerIndex, Vector2 gridPos, int *playerGold, int *playerSanity) {
    const Tower* selectedTower = &availableTowers[towerIndex];

    if (*playerGold >= selectedTower->goldCost && *playerSanity >= selectedTower->specialCost) {
        AddTower(gridPos, selectedTower->range, selectedTower->damage, selectedTower->rateOfFire, 
                 selectedTower->damageType, selectedTower->goldCost, selectedTower->specialCost, selectedTower->firePattern);

        *playerGold -= selectedTower->goldCost;
        *playerSanity -= selectedTower->specialCost;
    }
}
