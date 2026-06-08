#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"

Game::Game()
{
    gridSize = 5;
    cellSize = 100;
    startX = 50;
    startY = 50;

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            revealed[row][col] = false;
        }
    }
}

void Game::drawGrid()
{
    for (int row = 0; row < gridSize; row++)
    {
        for (int col = 0; col < gridSize; col++)
        {
            int x1 = startX + (col * cellSize);
            int y1 = startY + (row * cellSize);
            int x2 = x1 + cellSize;
            int y2 = y1 + cellSize;

            al_draw_rectangle(
                x1,
                y1,
                x2,
                y2,
                al_map_rgb(255, 255, 255),
                2
            );
        }
    }
}

void Game::drawRevealedBoxes()
{
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (revealed[row][col])
            {
                int x1 = startX + (col * cellSize);
                int y1 = startY + (row * cellSize);

                int centerX = x1 + 50;
                int centerY = y1 + 50;

                al_draw_filled_circle(
                    centerX,
                    centerY,
                    25,
                    al_map_rgb(0, 200, 255)
                );
            }
        }
    }
}

bool Game::handleMouseClick(int mouseX, int mouseY)
{
    if (mouseX < startX || mouseY < startY)
        return false;

    int col = (mouseX - startX) / cellSize;
    int row = (mouseY - startY) / cellSize;

    if (row < 0 || row >= 5 || col < 0 || col >= 5)
        return false;

    revealed[row][col] = true;

    return true;
}