#pragma once

class Game
{
private:
    int gridSize;
    int cellSize;
    int startX;
    int startY;

public:
    Game();

    void drawGrid();
};