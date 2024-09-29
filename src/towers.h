#ifndef TOWERS_H
#define TOWERS_H

#include "raylib.h"

#define MAX_TOWERS 100

typedef enum {
    DAMAGE_TYPE_PSCHIC,
    DAMAGE_TYPE_MATERIAL,
} DamageType;

typedef struct FirePattern {
    int bulletSpeed;
    int bulletSize;
    Color bulletColor;
} FirePattern;

typedef struct Tower {
    Vector2 position;
    int range;
    int damage;
    int rateOfFire;
    DamageType damageType;
    int goldCost;
    int specialCost;
    FirePattern firePattern;
    int towerIndex;  // Track the type of tower placed (e.g., 0 for blue circle, 1 for red square, etc.)
} Tower;


// Functions related to towers
void InitializeTowers();
void AddTower(Vector2 position, int range, int damage, int rateOfFire, DamageType damageType, int goldCost, int specialCost, FirePattern firePattern, int towerIndex);
void DrawTowers(int cellSize, Tower *selectedTower);
Tower* GetTowerAtPosition(Vector2 gridPos);

// Declare DrawTowerStatsWithBackground so it's known in main.c
void DrawTowerStatsWithBackground(Tower *tower, int cellSize);

#endif // TOWERS_H
