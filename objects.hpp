#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <cmath>

#define DIM 72
const float SQUARES = DIM/12;


namespace objects {
    bool gameover = false;
    enum Direction {Right, Left, Up, Down, Boost};

    class Board {
        public:
        sf::RectangleShape space[DIM][DIM];
            void makeSpaces() {
                for(int i = 0; i < DIM; i++) {
                    for(int j = 0; j < DIM; j++) {
                        space[i][j] = sf::RectangleShape(sf::Vector2f(SQUARES,SQUARES));
                        space[i][j].setPosition(sf::Vector2f((SQUARES*i),(SQUARES*j)));
                        space[i][j].setFillColor(sf::Color::White);
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
        public:
        sf::Clock clock;
        sf::Clock boostClock;
        sf::Color color;
        Board *board;
        Direction direction;
        int x, y, numspaces, boosts;
        bool boost;
        Player(sf::Color c, int startx, int starty, Direction startdir, Board& b) {
                color = c;
                x = startx;
                y = starty;
                boosts = 5;
                direction = startdir;
                board = &b;
                board->setSpace(x,y,color);
            }
            void move(float iteration) {
                sf::Time elapsed = clock.getElapsedTime();
                if(gameover == false && elapsed.asSeconds() >= iteration) {
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
                        numspaces++;
                    }
                }
            }
            void updateGame() {
                if(boost){
                    move(0.01);
                    sf::Time elapsed = boostClock.getElapsedTime();
                    if (elapsed.asSeconds() >= 0.5) {
                        boost = false;
                    }
                }else {
                    move(0.04);
                }
            }
    };
    class Player1: public Player{
        public:
        using Player::Player;
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
                case sf::Keyboard::Enter:
                    if (boosts != 0) {
                    boost = true;
                    boostClock.restart();
                    }
                    break;
            }
        }
    };
    class Player2: public Player{
        public:
        using Player::Player;
        void changeDir(sf::Event& event) {
        switch(event.key.code){
            case sf::Keyboard::S:
                if(direction != Up) direction = Down;
                break;
            case sf::Keyboard::W:
                if(direction != Down) direction = Up;
                break;
            case sf::Keyboard::D:
                if(direction != Left) direction = Right;
                break;
            case sf::Keyboard::A:
                if(direction != Right) direction = Left;
                break;
            case sf::Keyboard::Tab:
                if (boosts != 0) {
                   boost = true;
                   boostClock.restart();
                }
                break;
            }
        }
    };
};
