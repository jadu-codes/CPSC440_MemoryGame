#pragma once
#include <allegro5/allegro_font.h>

class Game
{
private:
    int pattern[5][5];
    bool alreadyPlayed[5][5];
    bool visible[5][5];

    int firstRow;
    int firstCol;
    int secondRow;
    int secondCol;
    int selectedCount;

    int matchedPairs;
    int remainingPairs;

    int gridSize;
    int cellSize;
    int startX;
    int startY;

public:
    Game();

    void resetClear();
    void randomCreate();
    int getShape(int row, int col);
    void setShape(int row, int col, int shape);
    bool handleMouseClick(int mouseX, int mouseY);
    bool compare();
    void hideUnmatched();
    bool gameWon();

    void drawGrid();
    void drawObjects();
    void drawShape(int shape, int centerX, int centerY);
    void drawStatus(ALLEGRO_FONT* font);
};