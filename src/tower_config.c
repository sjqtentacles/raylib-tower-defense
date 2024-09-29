#include "tower_config.h"

void ConfigureTowers(Tower towers[], int *towerCount) {
    // Configure the 5 kinds of towers with specific characteristics

    // Small radius, high damage, fast firing tower (material damage)
    towers[0].range = 2;
    towers[0].damage = 20;
    towers[0].rateOfFire = 10;
    towers[0].damageType = DAMAGE_TYPE_MATERIAL;
    towers[0].goldCost = 50;
    towers[0].specialCost = 10;

    // Large radius, low damage, fast firing tower (material damage)
    towers[1].range = 5;
    towers[1].damage = 5;
    towers[1].rateOfFire = 10;
    towers[1].damageType = DAMAGE_TYPE_MATERIAL;
    towers[1].goldCost = 60;
    towers[1].specialCost = 15;

    // Large radius, high damage, slow firing tower (psychic damage)
    towers[2].range = 5;
    towers[2].damage = 50;
    towers[2].rateOfFire = 3;
    towers[2].damageType = DAMAGE_TYPE_PSCHIC;
    towers[2].goldCost = 100;
    towers[2].specialCost = 20;

    // Medium radius, medium damage, medium firing tower (material damage)
    towers[3].range = 3;
    towers[3].damage = 15;
    towers[3].rateOfFire = 7;
    towers[3].damageType = DAMAGE_TYPE_MATERIAL;
    towers[3].goldCost = 75;
    towers[3].specialCost = 12;

    // Medium radius, low damage, high firing rate tower (psychic damage)
    towers[4].range = 3;
    towers[4].damage = 8;
    towers[4].rateOfFire = 15;
    towers[4].damageType = DAMAGE_TYPE_PSCHIC;
    towers[4].goldCost = 80;
    towers[4].specialCost = 18;

    *towerCount = 5;  // We have 5 configured towers
}
