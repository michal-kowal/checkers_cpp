#include "game.h"
#include <SFML/Graphics.hpp>
Game::Game(){
	startGame();
	selected = false;
	turn = true;
	playerHasToAttack = false;
};

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(board);
	for (int i = 0; i < blackPieces.size(); i++) {
		target.draw(*blackPieces[i]);
	}
	for (int i = 0; i < whitePieces.size(); i++) {
		target.draw(*whitePieces[i]);
	}
}

void Game::startGame() {
	loadTextures();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (game[i][j] == 2) {
				Piece *piece = new Piece(i, j, game[i][j], black, idCount++); //y,x
				blackPieces.push_back(piece);
			}
			else if (game[i][j] == 1) {
				Piece *piece = new Piece(i, j, game[i][j],white, idCount++);
				whitePieces.push_back(piece);
			}
		}
	}
}

void Game::loadTextures() {
	if (!white.loadFromFile("pieces/white.png"))
		std::cout << "error while loading white piece\n";
	if (!black.loadFromFile("pieces/black.png"))
		std::cout << "error while loading black piece\n";
	if (!whiteKing.loadFromFile("pieces/white_king.png"))
		std::cout << "error while loading white king piece\n";
	if (!blackKing.loadFromFile("pieces/black_king.png"))
		std::cout << "error while loading black king piece\n";
}

bool Game::choosePiece(int y, int x) {
	int size;
	nextAttack = false;
	if (turn) size = whitePieces.size();
	else size = blackPieces.size();
	for (int i = 0; i < size; i++) {
		if (!turn && blackPieces[i]->getPos_x() == x / 80 && blackPieces[i]->getPos_y() == y / 80) {
			selected = true;
			tmpPiece = blackPieces[i];
			tmpPieceIndex = i;
			ifPlayerHasToAttack();
			if(playerHasToAttack)
				searchForAttack();
			else {
				generateMoves();
			}
			break;
		}
		else if ( turn && whitePieces[i]->getPos_x() == x / 80 && whitePieces[i]->getPos_y() == y / 80) {
			selected = true;
			tmpPiece = whitePieces[i];
			tmpPieceIndex = i;
			ifPlayerHasToAttack();
			if (playerHasToAttack)
				searchForAttack();
			if (!tmpPiece->getPossibleAttack() && !playerHasToAttack)
				generateMoves();
			break;
		}
		else {
			selected = false;
			board.restoreBoard();
		}
	}
	return selected;
}

void Game::ifPlayerHasToAttack() {
	
	int newX, newY, currX, currY, size;//y, x
	std::vector<std::vector<int>> moves;
	if (turn) size = whitePieces.size();
	else size = blackPieces.size();
	for (int i = 0; i < size; i++) {
		if (turn) {
			currX = whitePieces[i]->getPos_x();
			currY = whitePieces[i]->getPos_y();
			moves = whitePieces[i]->moves(game);
		}
		else {
			currX = blackPieces[i]->getPos_x();
			currY = blackPieces[i]->getPos_y();
			moves = blackPieces[i]->moves(game);
		}
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i][1] > 0) newX = currX + moves[i][1] + 1;
			else newX = currX + moves[i][1] - 1;
			if (moves[i][0] > 0) newY = currY + moves[i][0] + 1;
			else newY = currY + moves[i][0] - 1;
			if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && (game[currY + moves[i][0]][currX + moves[i][1]] == 2 || game[currY + moves[i][0]][currX + moves[i][1]] == -2) && (tmpPiece->getPieceColor() == 1 || tmpPiece->getPieceColor() == -1) && game[newY][newX] == 0) {
				playerHasToAttack = true;
				return;
			}
			else if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && (game[currY + moves[i][0]][currX + moves[i][1]] == 1 || game[currY + moves[i][0]][currX + moves[i][1]] == -1) && (tmpPiece->getPieceColor() == 2 || tmpPiece->getPieceColor() == -2) && game[newY][newX] == 0) {
				playerHasToAttack = true;
				return;
			}
			else {
				playerHasToAttack = false;
			}
		}
	}
}

void Game::searchForAttack() {
	int currX = tmpPiece->getPos_x(), currY = tmpPiece->getPos_y(), newX, newY;
	std::vector<std::vector<int>> moves;
	moves = tmpPiece->moves(game);
	for (int i = 0; i < moves.size(); i++) {
		for (int j = 1; j <= tmpPiece->freeFields(); j++) {
			if (moves[i][1] > 0) newX = currX + moves[i][1] + j;
			else newX = currX + moves[i][1] - j;
			if (moves[i][0] > 0) newY = currY + moves[i][0] + j;
			else newY = currY + moves[i][0] - j;
			std::vector<int> temp = { newX, newY };
			if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && (game[currY + moves[i][0]][currX + moves[i][1]] == 2 || game[currY + moves[i][0]][currX + moves[i][1]] == -2) && (tmpPiece->getPieceColor() == 1 || tmpPiece->getPieceColor() == -1) && game[newY][newX] == 0) {
				tmpPiece->getPossibleMoves().push_back(temp);
				tmpPiece->setPossibleAttack(true);
				board.lightBoard(newX, newY, sf::Color::Red);
			}
			else if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && (game[currY + moves[i][0]][currX + moves[i][1]] == 1 || game[currY + moves[i][0]][currX + moves[i][1]] == -1) && (tmpPiece->getPieceColor() == 2 || tmpPiece->getPieceColor() == -2) && game[newY][newX] == 0) {
				tmpPiece->getPossibleMoves().push_back(temp);
				tmpPiece->setPossibleAttack(true);
				board.lightBoard(newX, newY, sf::Color::Red);
			}
			else break;
		}
	}
}

void Game::movePiece(int y, int x) {
	tmpPiece->setAttacked(false);
	int currX = tmpPiece->getPos_x(), currY = tmpPiece->getPos_y(), size;
	if (currX == x / 80 && currY == y / 80 && nextAttack) {
	}
	else if (currX == x / 80 && currY == y / 80 && !nextAttack) {
		selected = false;
		board.restoreBoard();
	}
	else {
		for (int i = 0; i < tmpPiece->getPossibleMoves().size(); i++) {
			if (tmpPiece->getPossibleMoves()[i][0] == x / 80 && tmpPiece->getPossibleMoves()[i][1] == y / 80) {
				if (tmpPiece->getPossibleAttack()) {
					int startX, endX, startY, endY, direction;
					bool stop = false;
					if (x / 80 < currX && y / 80 < currY) { startX = x / 80; endX = currX; startY = y / 80; endY = currY; direction = 1; }
					else if (x / 80 > currX && y / 80 < currY) { startX = currX; endX = x / 80; startY = currY; endY = y / 80; direction = -1; }
					else if (x / 80 < currX && y / 80 > currY) { startX = x / 80; endX = currX; startY = y / 80; endY = currY; direction = -1; }
					else { startX = currX; endX = x / 80; startY = currY; endY = y / 80; direction = 1; }
					int beatedX, beatedY;
					if (!turn) size = whitePieces.size();
					else size = blackPieces.size();
					for (int i = 0; i < size; i++) {
						beatedY = startY + direction;
						for (int j = startX + 1; j < endX; j++) {
							beatedX = j;
							if (turn && blackPieces[i]->getPos_x() == beatedX && blackPieces[i]->getPos_y() == beatedY) {
								blackPieces.erase(blackPieces.begin() + i);
								game[beatedY][beatedX] = 0;
								tmpPiece->setAttacked(true);
								stop = true;
								break;
							}
							else if (!turn && whitePieces[i]->getPos_x() == beatedX && whitePieces[i]->getPos_y() == beatedY) {
								whitePieces.erase(whitePieces.begin() + i);
								game[beatedY][beatedX] = 0;
								tmpPiece->setAttacked(true);
								stop = true;
								break;
							}
							beatedY = beatedY + direction;
						}
						if (stop) break;
					}
				}
				game[currY][currX] = 0;
				tmpPiece->setPosition(x, y);
				game[y / 80][x / 80] = tmpPiece->getPieceColor();
				tmpPiece->setPossibleAttack(false);
				searchForAttack();
				if (tmpPiece->getAttacked() && !tmpPiece->getPossibleAttack() || !tmpPiece->getAttacked()) {
					tmpPiece->setPossibleAttack(false);
					tmpPiece->setGradientAndDirection(0, 0);
					turn = !turn;
					nextAttack = false;
				}
				else nextAttack = true;
			}
		}
		gradient = (-(currY - y / 80) / (currX - x / 80));
		direction = x / 80 - currX;
		tmpPiece->setGradientAndDirection(gradient, direction);
	}
	tmpPiece->eraseMoves();
	board.restoreBoard();
	pieceToKing();
	if (!nextAttack) {
		tmpPiece->setGradientAndDirection(0, 0);
		selected = false;
		tmpPiece = NULL;
	}
	else if(nextAttack) {
		tmpPiece->eraseMoves();
		searchForAttack();
		if (tmpPiece->getPossibleMoves().size() == 0) {
			tmpPiece->setGradientAndDirection(0, 0);
			nextAttack = false;
			selected = false;
			tmpPiece = NULL;
			turn = !turn;
		}
		else {
			tmpPiece->eraseMoves();
			tmpPiece->setGradientAndDirection(gradient, direction);
			choosePiece(tmpPiece->getPos_y() * 80, tmpPiece->getPos_x() * 80);
		}
	}
}

void Game::generateMoves() {
	int currX = tmpPiece->getPos_x(), currY = tmpPiece->getPos_y(), newX, newY, count = 0;
	std::vector<std::vector<int>> moves;
	moves = tmpPiece->turnMoves();
	for (int i = 0; i < moves.size(); i++) {
		newX = currX + moves[i][1]; newY = currY + moves[i][0];
		if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && game[newY][newX] == 0) {
			std::vector<int> temp = { newX, newY };
			board.lightBoard(newX, newY, sf::Color::Red);
			tmpPiece->getPossibleMoves().push_back(temp);
		}
	}
}

void Game::pieceToKing() {
	if (tmpPiece->getPieceColor() == 2 && tmpPiece->getPos_y() == 7 && game[tmpPiece->getPos_y()][tmpPiece->getPos_x()] == 2) {
		game[tmpPiece->getPos_y()][tmpPiece->getPos_x()] = -2;
		King *king = new King(tmpPiece->getPos_y(), tmpPiece->getPos_x(), -2, blackKing, idCount++);
		king->setGradientAndDirection(0, 0);
		blackPieces.erase(blackPieces.begin() + tmpPieceIndex);
		blackPieces.push_back(king);
	}
	if (tmpPiece->getPieceColor() == 1 && tmpPiece->getPos_y() == 0 && game[tmpPiece->getPos_y()][tmpPiece->getPos_x()] == 1) {
		game[tmpPiece->getPos_y()][tmpPiece->getPos_x()] = -1;
		King* king = new King(tmpPiece->getPos_y(), tmpPiece->getPos_x(), -1, whiteKing, idCount++);
		king->setGradientAndDirection(0, 0);
		whitePieces.erase(whitePieces.begin() + tmpPieceIndex);
		whitePieces.push_back(king);
	}
}