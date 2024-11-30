// Game.cpp
#include "Game.h"

Game::Game(int width, int height, int maxIterations)
    : grid(width, height), state(Edition), iterations(0), maxIterations(maxIterations) {}

int Game::getIterations() const {
    return iterations;
}

void Game::setIterations(int value) {
    iterations = value;
}

int Game::getMaxIterations() const {
    return maxIterations;
}

void Game::setMaxIterations(int value) {
    maxIterations = value;
}

const std::vector<std::vector<bool>>& Game::getPreviousStates() const {
    return previousStates;
}

void Game::setPreviousStates(const std::vector<std::vector<bool>>& states) {
    previousStates = states;
}

bool Game::isStable() const {
    return grid.getCellStates() == previousStates;
}
