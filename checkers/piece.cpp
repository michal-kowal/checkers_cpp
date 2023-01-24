#include "piece.h"
#include <SFML/Graphics.hpp>

Piece::Piece() {};

Piece::Piece(int i, int j, int col, sf::Texture& tex, int setId) {
	pos_x = j;
	pos_y = i;
	color = col;
	sprite = sf::Sprite();
	sprite.setTexture(tex);
	possibleAttack = false;
	pieceId = setId;
	if (color == 1) {
		sprite.setPosition(sf::Vector2f(j * 80.f, i * 80.f));
	}
	else if (color == 2) {
		sprite.setPosition(sf::Vector2f(j * 80.f, i * 80.f));
	}
}

std::vector<std::vector<int>> Piece::moves(std::vector<std::vector<int>> game)
{
	std::vector<std::vector<int>> moves{{-1,-1},{-1,1},{1,-1},{1,1}};
	return moves;
}

std::vector<std::vector<int>> Piece::turnMoves()
{
	std::vector<std::vector<int>> turnMoves;
	if (color == 1)
		turnMoves = { {-1,-1},{-1,1} };
	else if (color == 2)
		turnMoves = { {1,-1},{1,1} };
	return turnMoves;
}

