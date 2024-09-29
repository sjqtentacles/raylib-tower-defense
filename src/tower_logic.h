#ifndef TOWER_LOGIC_H
#define TOWER_LOGIC_H

#include "towers.h"
#include "map.h"

// Function to place a tower at a specified grid position, checking the path
void PlaceTower(int towerIndex, Vector2 gridPos, int *playerGold, int *playerSanity, Path path);

#endif // TOWER_LOGIC_H
