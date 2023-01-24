#include "board.h"

Board::Board() {
    load(sf::Color(255, 232, 136, 100), sf::Color(69, 43, 65, 27));
};

void Board::load(sf::Color col1, sf::Color col2) {
    for (int i = 0; i < 8; i++) {
        sf::Color col;
        if (i % 2 == 0)
            col = col2;
        else
            col = col1;
        for (int j = 0; j < 8; j++) {
            if (col == col1)
                col = col2;
            else
                col = col1;
            board[i][j].setPosition(sf::Vector2f(i * 80.f, j * 80.f));
            board[i][j].setSize(sf::Vector2f(80.f, 80.f));
            board[i][j].setFillColor(col);
        }
    }
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            target.draw(board[i][j]);
        }
    }
}

void Board::lightBoard(int x, int y, sf::Color col) {
    board[x][y].setFillColor(col);
}

void Board::restoreBoard() {
    int j;
    for (int i = 0; i < 8; i++) {
        if (i % 2 == 0)
            j = 1;
        else
            j = 0;
        for (; j < 8; j += 2) {
            board[i][j].setFillColor(sf::Color(69, 43, 65, 27));
        }
    }
}