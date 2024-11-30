// Grid.h
#pragma once

#include <vector>
#include <string>
#include "Cell.h"

class Grid {
public:
    Grid(int width, int height);
    void update();
    void print() const;
    std::vector<std::vector<bool>> getCellStates() const;
    void toggleCellState(int x, int y);
    void clearGrid();

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width;
    int height;
    std::vector<std::vector<Cell>> cells;

    int countAliveNeighbors(int x, int y) const;
};
