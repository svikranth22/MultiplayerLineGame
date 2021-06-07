#include <SFML/Graphics.hpp>
#include "objects.hpp"
#include <iostream>
using namespace objects;

int main() {
    sf:: RenderWindow window(sf::VideoMode(DIM*SQUARES, DIM*SQUARES), "main window");
    window.setVerticalSyncEnabled(true);
    Board board;
    board.makeSpaces();
    Player1 player1(sf::Color::Blue,53,35,Left,board);
    Player2 player2(sf::Color::Red,17,35,Right,board);
    
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                player1.changeDir(event);
                player2.changeDir(event);
            }
        }
        window.clear(sf::Color::Black);
        board.drawSpaces(window);
        player1.updateGame();
        player2.updateGame();
        window.display();
    }
}



