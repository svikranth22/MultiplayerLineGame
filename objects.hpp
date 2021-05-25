#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <cmath>

#define DIM 32
const float SQUARES = DIM/2;

namespace objects {
    bool gameover = false;
    enum Direction {Right, Left, Up, Down};

    class Board {
        sf::RectangleShape space[DIM][DIM];
        public:
            void makeSpaces() {
                for(int i = 0; i < DIM; i++) {
                    for(int j = 0; j < DIM; j++) {
                        space[i][j] = sf::RectangleShape(sf::Vector2f(SQUARES,SQUARES));
                        space[i][j].setPosition(sf::Vector2f((SQUARES*i),(SQUARES*j)));
                        space[i][j].setFillColor(sf::Color::White);
                        space[i][j].setOutlineThickness(2.f);
                        space[i][j].setOutlineColor(sf::Color(0,0,0));
                    }
                }
            }
            void drawSpaces(sf::RenderWindow& window) {
                for(int i = 0; i < DIM; i++) {
                    for(int j = 0; j < DIM; j++) {
                    window.draw(space[i][j]);
                    }
                }
            }
            void setSpace(int x, int y, sf::Color playerColor){
                space[x][y].setFillColor(playerColor);
            }
            sf::Color getSpace(int x, int y) {
                return space[x][y].getFillColor();
            }
    };

    class Player {
        sf::Color color;
        int x, y;
        Direction direction;
        Board *board;
        sf::Clock clock;
        sf:SC
        public:
            Player(sf::Color c, int startx, int starty, Direction startdir, Board& b) {
                color = c;
                x = startx;
                y = starty;
                direction = startdir;
                board = &b;
                board->setSpace(x,y,color);
            }
            void move() {
                sf::Time elapsed = clock.getElapsedTime();
                if(elapsed.asSeconds() >= 0.1) {
                    switch(direction) {
                        case Right:
                            x++;
                            break;
                        case Left:
                            x--;
                            break;
                        case Up:
                            y--;
                            break;
                        case Down:
                            y++;
                            break;
                    }
                    clock.restart();
                    if(board->getSpace(x,y) != sf::Color::White || x > (DIM-1) || y > (DIM-1) || x < 0 || y < 0) {
                        gameover = true;
                    }else {
                        board->setSpace(x,y,color);
                    }
                }
            }
            void changeDir(sf::Event& event) {
                switch(event.key.code){
                    case sf::Keyboard::Down:
                        if(direction != Up) direction = Down;
                        break;
                    case sf::Keyboard::Up:
                        if(direction != Down) direction = Up;
                        break;
                    case sf::Keyboard::Right:
                        if(direction != Left) direction = Right;
                        break;
                    case sf::Keyboard::Left:
                        if(direction != Right) direction = Left;
                        break;
                }
            }
    };
};
