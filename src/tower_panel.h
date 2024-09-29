#ifndef TOWER_PANEL_H
#define TOWER_PANEL_H

// Declare shared tower button dimensions
extern int towerButtonWidth;
extern int towerButtonSpacing;

// Function to draw the scrollable tower selection panel
void DrawTowerPanel(int windowWidth, int windowHeight, int playerGold, int playerSanity);

#endif // TOWER_PANEL_H
