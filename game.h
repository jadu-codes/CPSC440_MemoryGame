#pragma once

class Game
{
private:
    int gridSize;
    int cellSize;
    int startX;
    int startY;

    bool revealed[5][5];

public:
    Game();

    void drawGrid();
    void drawRevealedBoxes();
    bool handleMouseClick(int mouseX, int mouseY);
};