#include <SFML/Graphics.hpp>
#include "game.h"
#include <Windows.h>

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    Game game;
    int startX, startY;
    sf::RenderWindow win(sf::VideoMode(640, 640), "Checkers");
    while (win.isOpen())
    {        
    sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left) {
                    if (event.mouseButton.x >= 0 && event.mouseButton.x <= 640 && event.mouseButton.y >= 0 && event.mouseButton.y <= 640) {
                        startX = event.mouseButton.x;
                        startY = event.mouseButton.y;
                        if (!game.isSelected() ) {
                            game.choosePiece(startY, startX);
                        }
                        else {
                            game.movePiece(startY, startX);
                        }
                    }
                }
            }
        }
        win.draw(game);
        win.display();
    }
    return 0;
}