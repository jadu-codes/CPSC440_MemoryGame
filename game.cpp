// Joel Adu - Memory Matching Game Logic

#include "game.h"
#include <allegro5/allegro_primitives.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>

Game::Game()
{
    gridSize = 5;
    cellSize = 100;
    startX = 50;
    startY = 50;

    srand((unsigned int)time(0));
    resetClear();
    randomCreate();
}

void Game::resetClear()
{
    matchedPairs = 0;
    remainingPairs = 12;
    selectedCount = 0;

    firstRow = -1;
    firstCol = -1;
    secondRow = -1;
    secondCol = -1;

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            pattern[row][col] = 0;
            alreadyPlayed[row][col] = false;
            visible[row][col] = false;
        }
    }
}

void Game::randomCreate()
{
    std::vector<int> shapes;

    for (int shape = 1; shape <= 12; shape++)
    {
        shapes.push_back(shape);
        shapes.push_back(shape);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shapes.begin(), shapes.end(), g);

    int index = 0;

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (row == 4 && col == 4)
            {
                pattern[row][col] = 0;
            }
            else
            {
                pattern[row][col] = shapes[index];
                index++;
            }
        }
    }
}

int Game::getShape(int row, int col)
{
    if (row < 0 || row >= 5 || col < 0 || col >= 5)
        return 0;

    return pattern[row][col];
}

void Game::setShape(int row, int col, int shape)
{
    if (row >= 0 && row < 5 && col >= 0 && col < 5)
    {
        pattern[row][col] = shape;
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

    if (row == 4 && col == 4)
        return false;

    if (alreadyPlayed[row][col] || visible[row][col])
        return false;

    visible[row][col] = true;

    if (selectedCount == 0)
    {
        firstRow = row;
        firstCol = col;
        selectedCount = 1;
    }
    else if (selectedCount == 1)
    {
        secondRow = row;
        secondCol = col;
        selectedCount = 2;
    }

    return true;
}

bool Game::compare()
{
    if (selectedCount != 2)
        return false;

    if (pattern[firstRow][firstCol] == pattern[secondRow][secondCol])
    {
        alreadyPlayed[firstRow][firstCol] = true;
        alreadyPlayed[secondRow][secondCol] = true;

        matchedPairs++;
        remainingPairs--;

        selectedCount = 0;
        firstRow = -1;
        firstCol = -1;
        secondRow = -1;
        secondCol = -1;

        return true;
    }

    return false;
}

void Game::hideUnmatched()
{
    if (selectedCount == 2)
    {
        visible[firstRow][firstCol] = false;
        visible[secondRow][secondCol] = false;

        selectedCount = 0;
        firstRow = -1;
        firstCol = -1;
        secondRow = -1;
        secondCol = -1;
    }
}

bool Game::gameWon()
{
    return matchedPairs == 12;
}

void Game::drawGrid()
{
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            int x1 = startX + col * cellSize;
            int y1 = startY + row * cellSize;
            int x2 = x1 + cellSize;
            int y2 = y1 + cellSize;

            if (row == 4 && col == 4)
            {
                al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 80, 0));
            }

            al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(255, 255, 255), 2);
        }
    }
}

void Game::drawObjects()
{
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (visible[row][col] || alreadyPlayed[row][col])
            {
                int centerX = startX + col * cellSize + 50;
                int centerY = startY + row * cellSize + 50;

                drawShape(pattern[row][col], centerX, centerY);
            }
        }
    }
}

void Game::drawShape(int shape, int centerX, int centerY)
{
    if (shape == 1)
        al_draw_filled_circle(centerX, centerY, 25, al_map_rgb(0, 200, 255));

    else if (shape == 2)
        al_draw_filled_rectangle(centerX - 30, centerY - 25, centerX + 30, centerY + 25, al_map_rgb(255, 0, 0));

    else if (shape == 3)
        al_draw_filled_triangle(centerX, centerY - 35, centerX - 35, centerY + 30, centerX + 35, centerY + 30, al_map_rgb(255, 255, 0));

    else if (shape == 4)
    {
        al_draw_filled_triangle(centerX, centerY - 35, centerX - 35, centerY, centerX, centerY + 35, al_map_rgb(180, 0, 255));
        al_draw_filled_triangle(centerX, centerY - 35, centerX + 35, centerY, centerX, centerY + 35, al_map_rgb(180, 0, 255));
    }

    else if (shape == 5)
        al_draw_filled_ellipse(centerX, centerY, 35, 20, al_map_rgb(0, 255, 100));

    else if (shape == 6)
    {
        al_draw_filled_rectangle(centerX - 25, centerY - 25, centerX + 25, centerY + 25, al_map_rgb(255, 140, 0));
        al_draw_filled_triangle(centerX - 25, centerY - 25, centerX, centerY - 40, centerX + 25, centerY - 25, al_map_rgb(255, 140, 0));
        al_draw_filled_triangle(centerX - 25, centerY + 25, centerX, centerY + 40, centerX + 25, centerY + 25, al_map_rgb(255, 140, 0));
    }

    else if (shape == 7)
        al_draw_rectangle(centerX - 30, centerY - 30, centerX + 30, centerY + 30, al_map_rgb(255, 255, 255), 5);

    else if (shape == 8)
        al_draw_circle(centerX, centerY, 30, al_map_rgb(255, 0, 255), 5);

    else if (shape == 9)
    {
        al_draw_line(centerX - 30, centerY - 30, centerX + 30, centerY + 30, al_map_rgb(0, 255, 255), 5);
        al_draw_line(centerX + 30, centerY - 30, centerX - 30, centerY + 30, al_map_rgb(0, 255, 255), 5);
    }

    else if (shape == 10)
    {
        al_draw_filled_circle(centerX - 15, centerY, 18, al_map_rgb(255, 100, 100));
        al_draw_filled_circle(centerX + 15, centerY, 18, al_map_rgb(255, 100, 100));
    }

    else if (shape == 11)
    {
        al_draw_filled_rectangle(centerX - 35, centerY - 10, centerX + 35, centerY + 10, al_map_rgb(100, 100, 255));
        al_draw_filled_rectangle(centerX - 10, centerY - 35, centerX + 10, centerY + 35, al_map_rgb(100, 100, 255));
    }

    else if (shape == 12)
    {
        al_draw_filled_triangle(centerX, centerY - 35, centerX - 30, centerY + 25, centerX + 30, centerY + 25, al_map_rgb(0, 200, 100));
        al_draw_circle(centerX, centerY, 18, al_map_rgb(255, 255, 255), 4);
    }
}

void Game::drawStatus(ALLEGRO_FONT* font)
{
    int x1 = startX + 4 * cellSize;
    int y1 = startY + 4 * cellSize;

    al_draw_filled_rectangle(x1, y1, x1 + cellSize, y1 + cellSize, al_map_rgb(0, 80, 0));
    al_draw_rectangle(x1, y1, x1 + cellSize, y1 + cellSize, al_map_rgb(255, 255, 255), 2);

    al_draw_textf(font, al_map_rgb(255, 255, 255), x1 + 8, y1 + 25, 0, "Matched: %d", matchedPairs);
    al_draw_textf(font, al_map_rgb(255, 255, 255), x1 + 8, y1 + 50, 0, "Left: %d", remainingPairs);
}