#ifndef _GAME_H
#define _GAME_H
#include <SFML/Graphics.hpp>
#include "piece.h"
#include "board.h"
#include "king.h"
#include <iostream>
#include <vector>

class Game: public sf::Drawable
{
private:
	Board board;
	PieceAbs *tmpPiece;
	int tmpPieceIndex;
	std::vector<PieceAbs*> blackPieces;
	std::vector<PieceAbs*> whitePieces;
	sf::Texture white;
	sf::Texture black;
	sf::Texture whiteKing;
	sf::Texture blackKing;
	bool selected;
	bool nextAttack;
	bool turn; // true-white, false-black
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<std::vector<int>> game{ {0,2,0,2,0,2,0,2},
					{2,0,2,0,2,0,2,0},
					{0,2,0,2,0,2,0,2},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{1,0,1,0,1,0,1,0},
					{0,1,0,1,0,1,0,1},
					{1,0,1,0,1,0,1,0} }; //0-empty, 1-white, 2-black
	bool playerHasToAttack;
	int idCount = 0, gradient, direction;
public:
	Game();
	void startGame();
	void loadTextures();
	bool isSelected() { return selected; };
	bool choosePiece(int y, int x);
	void movePiece(int y, int x);
	void generateMoves();
	void searchForAttack();
	void ifPlayerHasToAttack();
	void pieceToKing();
	std::vector<std::vector<int>> getGame() { return game; };
};

#endif
