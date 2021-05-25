#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "objects.hpp"
using namespace objects;

int main() {
    sf:: RenderWindow window(sf::VideoMode(DIM*SQUARES, DIM*SQUARES), "main window");
    Board board;
    board.makeSpaces();
    Player player1(sf::Color::Blue,0,0,Right,board);
    
    sf::UdpSocket socket;
    socket.bind(54000);
    char data[10] = "hello"
    sf::IpAddress recipient = "192.168.1.221";
    unsigned short port = 54000;
    socket.send(data, 10 , recipient, port);
    
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                player1.changeDir(event);
            }
        }
        window.clear(sf::Color::Black);
        board.drawSpaces(window);
        if(gameover == false) {
            player1.move();
        }
        window.display();
    }
}


