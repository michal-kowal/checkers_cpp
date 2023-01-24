#ifndef _PIECEABS_H
#define _PIECEABS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class PieceAbs : public sf::Sprite
{
protected:
	int pos_x, pos_y, color;
	sf::Sprite sprite;
	std::vector<std::vector<int>> PossibleMoves;
	bool possibleAttack;
	bool attacked;
	int pieceId;
	int previousGradient;
	int direction;
public:
	virtual std::vector<std::vector<int>> moves(std::vector<std::vector<int>> game)=0;
	virtual std::vector<std::vector<int>> turnMoves()=0;
	virtual int freeFields()=0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite);
	}
	int getPos_x() { return pos_x; }
	int getPos_y() { return pos_y; }
	int getPieceColor() { return color; }
	void setPosition(int x, int y);
	void move();
	std::vector<std::vector<int>>& getPossibleMoves() { return PossibleMoves; }
	void eraseMoves() { PossibleMoves.clear(); }
	bool getPossibleAttack() { return possibleAttack; }
	void setPossibleAttack(bool x) { possibleAttack = x; }
	bool getAttacked() { return attacked; }
	void setAttacked(bool x) { attacked = x; }
	void setGradientAndDirection(int x, int y) { previousGradient = x; direction = y; }
};


#endif