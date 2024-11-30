// Game.h
#pragma once
#include "Grid.h"
#include <string>

class Game {
public:
    enum GameState { Edition, Simulation, Paused, Finished };

    Game(int width, int height, int maxIterations);
    void run();

    Grid grid;
    GameState state;

    // Méthodes publiques pour accéder aux membres privés
    int getIterations() const;
    void setIterations(int value);

    int getMaxIterations() const;
    void setMaxIterations(int value);

    const std::vector<std::vector<bool>>& getPreviousStates() const;
    void setPreviousStates(const std::vector<std::vector<bool>>& states);

    bool isStable() const;

private:
    int iterations;
    int maxIterations;
    std::vector<std::vector<bool>> previousStates;
};
