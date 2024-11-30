// Grid.cpp
#include "Grid.h"
#include <iostream>

// Constructeur
Grid::Grid(int width, int height)
    : width(width), height(height), cells(width, std::vector<Cell>(height)) {}

// Mise à jour de la grille selon les règles du jeu
void Grid::update() {
    std::vector<std::vector<Cell>> next = cells;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int aliveNeighbors = countAliveNeighbors(x, y);
            if (cells[x][y].getState()) {
                next[x][y].setState(aliveNeighbors == 2 || aliveNeighbors == 3);
            } else {
                next[x][y].setState(aliveNeighbors == 3);
            }
        }
    }

    cells = next;
}

// Calcul des voisins vivants
int Grid::countAliveNeighbors(int x, int y) const {
    static const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int count = 0;

    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
            count += cells[nx][ny].getState() ? 1 : 0;
        }
    }

    return count;
}

// Affichage de la grille dans la console (optionnel)
void Grid::print() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << (cells[x][y].getState() ? "O" : ".");
        }
        std::cout << std::endl;
    }
}

// Obtention des états des cellules
std::vector<std::vector<bool>> Grid::getCellStates() const {
    std::vector<std::vector<bool>> states(width, std::vector<bool>(height));
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            states[x][y] = cells[x][y].getState();
        }
    }
    return states;
}

// Changer l'état d'une cellule (lors d'un clic)
void Grid::toggleCellState(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        bool currentState = cells[x][y].getState();
        cells[x][y].setState(!currentState);
    }
}

// Réinitialiser la grille (toutes les cellules mortes)
void Grid::clearGrid() {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            cells[x][y].setState(false);
        }
    }
}
