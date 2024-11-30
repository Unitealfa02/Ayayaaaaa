// main.cpp
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const int cellSize = 10;

int main() {
    int width = 80;
    int height = 80;
    int maxIterations = 1000; // Nombre maximum d'itérations

    Game game(width, height, maxIterations);

    sf::RenderWindow window(sf::VideoMode(width * cellSize, height * cellSize + 50), "Jeu de la Vie");
    window.setFramerateLimit(60);

    // Bouton "Lancer"
    sf::RectangleShape button(sf::Vector2f(100, 30));
    button.setPosition(width * cellSize / 2 - 160, height * cellSize + 10);
    button.setFillColor(sf::Color::Blue);

    // Symbole "Play"
    sf::CircleShape playSymbol(10, 3); // Triangle équilatéral
    playSymbol.setFillColor(sf::Color::White);
    playSymbol.setPosition(button.getPosition().x + 45, button.getPosition().y + 5);
    playSymbol.setRotation(90);

    // Bouton "Pause"
    sf::RectangleShape pauseButton(sf::Vector2f(100, 30));
    pauseButton.setPosition(width * cellSize / 2 - 50, height * cellSize + 10);
    pauseButton.setFillColor(sf::Color::Yellow);

    // Symboles "Pause" (deux rectangles)
    sf::RectangleShape pauseSymbol1(sf::Vector2f(8, 20));
    pauseSymbol1.setFillColor(sf::Color::White);
    pauseSymbol1.setPosition(pauseButton.getPosition().x + 35, pauseButton.getPosition().y + 5);

    sf::RectangleShape pauseSymbol2(sf::Vector2f(8, 20));
    pauseSymbol2.setFillColor(sf::Color::White);
    pauseSymbol2.setPosition(pauseButton.getPosition().x + 55, pauseButton.getPosition().y + 5);

    // Bouton "Restart"
    sf::RectangleShape restartButton(sf::Vector2f(100, 30));
    restartButton.setPosition(width * cellSize / 2 + 60, height * cellSize + 10);
    restartButton.setFillColor(sf::Color::Red);

    // Symbole "Restart" (carré)
    sf::RectangleShape restartSymbol(sf::Vector2f(20, 20));
    restartSymbol.setFillColor(sf::Color::White);
    restartSymbol.setPosition(restartButton.getPosition().x + 40, restartButton.getPosition().y + 5);

    bool isRunning = true;

    while (window.isOpen() && isRunning) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    // Vérifier si le clic est sur le bouton "Restart"
                    if (mouseX >= restartButton.getPosition().x && mouseX <= restartButton.getPosition().x + restartButton.getSize().x &&
                        mouseY >= restartButton.getPosition().y && mouseY <= restartButton.getPosition().y + restartButton.getSize().y) {
                        // Réinitialiser le jeu
                        game.grid.clearGrid();
                        game.state = Game::Edition;
                        game.setIterations(0);
                    }

                    // Vérifier si le clic est sur le bouton "Pause"
                    if (game.state == Game::Simulation || game.state == Game::Paused) {
                        if (mouseX >= pauseButton.getPosition().x && mouseX <= pauseButton.getPosition().x + pauseButton.getSize().x &&
                            mouseY >= pauseButton.getPosition().y && mouseY <= pauseButton.getPosition().y + pauseButton.getSize().y) {
                            // Basculer entre l'état "Simulation" et "Paused"
                            if (game.state == Game::Simulation) {
                                game.state = Game::Paused;
                            } else if (game.state == Game::Paused) {
                                game.state = Game::Simulation;
                            }
                        }
                    }

                    if (game.state == Game::Edition) {
                        // Vérifier si le clic est sur le bouton "Lancer"
                        if (mouseX >= button.getPosition().x && mouseX <= button.getPosition().x + button.getSize().x &&
                            mouseY >= button.getPosition().y && mouseY <= button.getPosition().y + button.getSize().y) {
                            game.state = Game::Simulation;
                            game.setPreviousStates(game.grid.getCellStates());
                            game.setIterations(0);
                        } else if (mouseY < height * cellSize) {
                            // Calculer les coordonnées de la cellule cliquée
                            int cellX = mouseX / cellSize;
                            int cellY = mouseY / cellSize;

                            // Changer l'état de la cellule
                            game.grid.toggleCellState(cellX, cellY);
                        }
                    }
                }
            }
        }

        // Mise à jour de la grille en mode simulation
        if (game.state == Game::Simulation) {
            if (game.getIterations() < game.getMaxIterations()) {
                game.grid.update();
                game.setIterations(game.getIterations() + 1);

                // Vérifier si la grille est stable
                if (game.isStable()) {
                    game.state = Game::Finished;
                } else {
                    game.setPreviousStates(game.grid.getCellStates());
                }
            } else {
                game.state = Game::Finished;
            }
        }

        // Rendu de la grille
        window.clear();

        // Dessiner les cellules
        sf::RectangleShape cellShape(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
        cellShape.setFillColor(sf::Color::White);

        auto currentStates = game.grid.getCellStates();

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (currentStates[x][y]) {
                    cellShape.setPosition(x * cellSize, y * cellSize);
                    window.draw(cellShape);
                }
            }
        }

        // Dessiner les boutons
        if (game.state == Game::Edition) {
            window.draw(button);
            window.draw(playSymbol);
        } else if (game.state == Game::Simulation || game.state == Game::Paused) {
            window.draw(pauseButton);
            window.draw(pauseSymbol1);
            window.draw(pauseSymbol2);
        }

        if (game.state == Game::Edition || game.state == Game::Simulation || game.state == Game::Paused || game.state == Game::Finished) {
            window.draw(restartButton);
            window.draw(restartSymbol);
        }

        window.display();

        if (game.state == Game::Simulation) {
            sf::sleep(sf::milliseconds(100)); // Contrôle de la vitesse de simulation
        }
    }

    return 0;
}
