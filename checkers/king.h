#ifndef _KING_H
#define _KING_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "PieceAbs.h"
#include "game.h"

class King : public PieceAbs
{
private:
	std::vector<std::vector<int>> kingMoves;
public:
	King();
	King(int x, int y, int col, sf::Texture& tex, int setId);
	virtual std::vector<std::vector<int>> moves(std::vector<std::vector<int>>);
	virtual std::vector<std::vector<int>> turnMoves();
	void findDiagonalMove(int x, int y, std::vector<std::vector<int>> game);
	virtual int freeFields() { return 6; }
};

#endif