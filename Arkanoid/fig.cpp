#include "fig.h"

float Ball::x() { return this->getPosition().x; }
float Ball::y() { return this->getPosition().y; }
float Ball::left() { return x() - this->getRadius(); }
float Ball::right() { return x() + this->getRadius(); }
float Ball::top() { return y() - this->getRadius(); }
float Ball::bottom() { return y() + this->getRadius(); }
void Ball::update(Player& player) {
	this->move(_velocity);
	if (left() < 0) {
		_velocity.x = abs(_velocity.x);
	}
	else if (right() > windowWidth) {
		_velocity.x = -abs(_velocity.x);
	}
	if (top() < 0) {
		_velocity.y = abs(_velocity.y);
	}
	else if (bottom() > windowHeight) {
		if (player.getHealth() > 0) {
			player.healthDecrease();
		}
		if (player.getScore() > 0) {
			player.scoreDecrease();
		}
		_velocity.y = -abs(_velocity.y);
	}

}

float Racket::x() { return this->getPosition().x; }
float Racket::y() { return this->getPosition().y; }
float Racket::left() { return x() - this->getSize().x / 2.f; }
float Racket::right() { return x() + this->getSize().x / 2.f; }
float Racket::top() { return y() - this->getSize().y / 2.f; }
float Racket::bottom() { return y() + this->getSize().y / 2.f; }

void Racket::update() {
	this->move(_velocity);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && left() > 0) {
		setXVelocity(-racketVelocity);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && right() < windowWidth) {
		setXVelocity(racketVelocity);
	}
	else {
		setXVelocity(0);
	}
}

float Brick::x() { return this->getPosition().x; }
float Brick::y() { return this->getPosition().y; }
float Brick::left() { return x() - this->getSize().x / 2.f; }
float Brick::right() { return x() + this->getSize().x / 2.f; }
float Brick::top() { return y() - this->getSize().y / 2.f; }
float Brick::bottom() { return y() + this->getSize().y / 2.f; }

float Bonus::x() { return this->getPosition().x; }
float Bonus::y() { return this->getPosition().y; }
float Bonus::left() { return x() - this->getSize().x / 2.f; }
float Bonus::right() { return x() + this->getSize().x / 2.f; }
float Bonus::top() { return y() - this->getSize().y / 2.f; }
float Bonus::bottom() { return y() + this->getSize().y / 2.f; }

void Bonus::update() {
	this->move(_velocity);
	if (bottom() > windowHeight) {
		this->setFailStatus(true);
	}
}

void MovingBrick::update() {
	this->move(_velocity);
	if (left() < 0) {
		_velocity.x = abs(_velocity.x);
	}
	if (right() > windowWidth) {
		_velocity.x = -abs(_velocity.x);
	}
}

void Bonus::spawnMovingBrick(std::vector <MovingBrick>& movingBricks) {
	movingBricks.emplace_back((movingBricks.size()) * windowWidth / 6, windowHeight / 4);
	movingBricks.back().setAliveStatus(true);
	movingBricks.back().setDestructibility(true);
	movingBricks.back().setHealth(2);
}

void Bonus::spawnBall(std::vector<Ball>& balls) {
	balls.emplace_back(windowWidth / 2, 3 * windowHeight / 4);
	balls.back().setFillColor(sf::Color::Magenta);
}