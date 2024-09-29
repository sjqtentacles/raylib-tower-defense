// towers.h
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
    FirePattern firePattern;  // New fire pattern field
} Tower;

// Functions related to towers
void InitializeTowers();
void AddTower(Vector2 position, int range, int damage, int rateOfFire, DamageType damageType, int goldCost, int specialCost, FirePattern firePattern);
void DrawTowers(int cellSize, Tower *selectedTower);
Tower* GetTowerAtPosition(Vector2 gridPos);

#endif // TOWERS_H
