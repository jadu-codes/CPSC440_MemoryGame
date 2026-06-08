#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"

Game::Game()
{
    gridSize = 5;
    cellSize = 100;

    // Center grid
    startX = 50;
    startY = 50;
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