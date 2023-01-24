#ifndef _BOARD_H
#define _BOARD_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <array>
#include <iostream>

class Board: public sf::Drawable
{
public:
    Board();
    void load(sf::Color col1, sf::Color col2);
    ~Board() = default;
    void lightBoard(int x, int y, sf::Color col);
    void restoreBoard();

private:
    std::array<std::array<sf::RectangleShape, 8>, 8> board;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif