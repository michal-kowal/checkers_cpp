#include "king.h"

King::King()
{
}

King::King(int i, int j, int col, sf::Texture& tex, int setId)
{
	pos_x = j;
	pos_y = i;
	color = col;
	sprite = sf::Sprite();
	sprite.setTexture(tex);
	pieceId = setId;
	possibleAttack = false;
	if (color == -1) {
		sprite.setPosition(sf::Vector2f(j * 80.f, i * 80.f));
	}
	else if (color == -2) {
		sprite.setPosition(sf::Vector2f(j * 80.f, i * 80.f));
	}
}

std::vector<std::vector<int>> King::moves(std::vector<std::vector<int>> game)
{
	kingMoves.clear();
	if (previousGradient > 0 && direction > 0)
	{
		findDiagonalMove(-1, -1, game);
		findDiagonalMove(1, -1, game);
		findDiagonalMove(1, 1, game);
	}
	else if (previousGradient > 0 && direction < 0) {
		findDiagonalMove(-1, -1, game);
		findDiagonalMove(-1, 1, game);
		findDiagonalMove(1, 1, game);
	}
	else if (previousGradient < 0 && direction < 0) {
		findDiagonalMove(-1, -1, game);
		findDiagonalMove(1, -1, game);
		findDiagonalMove(-1, 1, game);
	}
	else if (previousGradient < 0 && direction > 0) {
		findDiagonalMove(1, -1, game);
		findDiagonalMove(-1, 1, game);
		findDiagonalMove(1, 1, game);
	}
	else {
		findDiagonalMove(-1, -1, game);
		findDiagonalMove(1, -1, game);
		findDiagonalMove(-1, 1, game);
		findDiagonalMove(1, 1, game);
		previousGradient = 0; direction = 0;
	}
	std::vector<std::vector<int>> moves = kingMoves;
	return moves;
}

void King::findDiagonalMove(int x, int y, std::vector<std::vector<int>> game) {
	int CurrX = getPos_x(); int CurrY = getPos_y(), opponetColor;
	bool avoidDoubleAttack = false;
	if (color == 1 || color == -1) opponetColor = 2;
	else if (color == 2 || color == -2) opponetColor = 1;
	for (int i = 1; i < 8; i++) {
		if (CurrX + x * i < 0 || CurrX + x * i > 7 || CurrY + y * i < 0 || CurrY + y * i > 7)
			continue;
		else {
			if (game[CurrY + y * i][CurrX + x * i] == color || game[CurrY + y * i][CurrX + x * i] == -color) 
				break;
			else if (CurrY + y * (i - 1) >=0 && CurrX + x * (i - 1)>=0 && game[CurrY + y * i][CurrX + x * i] != 0 && game[CurrY + y * i][CurrX + x * i] == game[CurrY + y * (i - 1)][CurrX + x * (i - 1)]) {
				break;
			}
			else if (game[CurrY + y * i][CurrX + x * i] == opponetColor || game[CurrY + y * i][CurrX + x * i] == -opponetColor) {
				if (!avoidDoubleAttack) { avoidDoubleAttack = true; kingMoves.push_back({ y * i, x * i });}
				else break;
			}
			else  {
				kingMoves.push_back({ y * i, x * i });
			}
		}
	}
}

std::vector<std::vector<int>> King::turnMoves()
{
	return kingMoves;
}
