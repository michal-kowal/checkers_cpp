#include "PieceAbs.h"
#include <SFML/Graphics.hpp>

void PieceAbs::setPosition(int j, int i) {
	pos_x = j / 80;
	pos_y = i / 80;
	move();
}

void PieceAbs::move() {
	sprite.setPosition(sf::Vector2f(pos_x * 80.f, pos_y * 80.f));
}


