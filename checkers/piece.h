#ifndef _PIECE_H
#define _PIECE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "PieceAbs.h"

class Piece : public PieceAbs
{
public:
	Piece();
	Piece(int x, int y, int col, sf::Texture& tex, int setId);
	virtual std::vector<std::vector<int>> moves(std::vector<std::vector<int>> game);
	virtual std::vector<std::vector<int>> turnMoves();
	virtual int freeFields() { return 1; }
};

#endif