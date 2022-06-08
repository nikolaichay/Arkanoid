#ifndef FIG_H
#define FIG_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
/*Constants*/
constexpr float ballRadius{ 8 }, ballVelocity{ 4.f }, ballVelocityBoost{ 3.f };
constexpr int windowWidth{ 800 }, windowHeight{ 680 };
constexpr float racketWidth{ 70.f }, racketHeight{ 13.f }, racketVelocity{ 15.f };
constexpr float blockWidth{ 38.f }, blockHeight{ 13.f };
constexpr int countStandardX{ 4 }, countStandardY{ 4 }, countIndestructibleBlocks{ 7 }, countVelocityBoostBlocks{ 2 }, countStrongBlocks{ 3 };
constexpr float bonusVelocity{ 3.f };
constexpr float brickVelocity{ 3.f };
enum class bonusType { NONE, MOVINGBRICK, ADDBALL };
class Player;
class Bonus;
class MovingBrick;
class Ball :public sf::CircleShape {
public:
	Ball(float mX, float mY) {
		this->setPosition(mX, mY);
		this->setRadius(ballRadius);
		this->setOrigin(ballRadius, ballRadius);
	}
	void update(Player& player);
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();

	sf::Vector2f getVelocity() { return this->_velocity; }

	void setVelocity(sf::Vector2f velocity) { this->_velocity = velocity; }
	void setXVelocity(float xvelocity) { this->_velocity.x = xvelocity; }
	void setYVelocity(float yvelocity) { this->_velocity.y = yvelocity; }
private:
	bool _additional = false;
	sf::Vector2f _velocity{ -ballVelocity, -ballVelocity };
};
class Racket : public sf::RectangleShape {
public:
	Racket(float mX, float mY) {
		this->setPosition(mX, mY);
		this->setSize({ racketWidth, racketHeight });
		this->setOrigin(racketWidth / 2, racketHeight / 2);
	}
	void update();
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();

	sf::Vector2f getVelocity() { return this->_velocity; }

	void setVelocity(sf::Vector2f velocity) { this->_velocity = velocity; }
	void setXVelocity(float xvelocity) { this->_velocity.x = xvelocity; }
	void setYVelocity(float yvelocity) { this->_velocity.y = yvelocity; }
private:
	sf::Vector2f _velocity{ -racketVelocity, 0 };
};
class Brick : public sf::RectangleShape {
public:
	Brick(float mX, float mY) {
		this->setPosition(mX, mY);
		this->setSize({ blockWidth, blockHeight });
		this->setFillColor(sf::Color::Yellow);
		this->setOrigin(blockWidth / 2.f, blockHeight / 2.f);
	}
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();

	bool getStatus() { return this->_destroyed; }
	void setStatus(bool status) { this->_destroyed = status; }

	bool getDestructibility() { return this->_isDestructible; }
	void setDestructibility(bool status) {
		this->_isDestructible = status;
	}

	float getVelocityBoost() { return this->_velocityBoost; }
	void setVelocityBoost(float velocityBoost) { this->_velocityBoost = velocityBoost; }

	int getHealth() { return this->_health; }
	void setHealth(int hitCount) { this->_health = hitCount; }
	void healthDecrease() { this->_health--; }

private:
	bool _destroyed = false;
	bool _isDestructible = true;
	float _velocityBoost = 1.f;
	int _health = 1;
};

class MovingBrick : public Brick {
public:
	MovingBrick(float mX, float mY) : Brick(mX, mY) {};
	void update();
	bool getAliveStatus() { return this->_isAlive; }
	void setAliveStatus(bool status) { this->_isAlive = status; }

	sf::Vector2f getVelocity() { return this->_velocity; }

	void setVelocity(sf::Vector2f velocity) { this->_velocity = velocity; }
	void setXVelocity(float xvelocity) { this->_velocity.x = xvelocity; }
	void setYVelocity(float yvelocity) { this->_velocity.y = yvelocity; }
private:
	sf::Vector2f _velocity{ brickVelocity, 0 };
	bool _isAlive = false;
};
class Player {
public:
	int getHealth() { return this->_health; }
	void healthIncrease() { this->_health++; }
	void healthDecrease() { this->_health--; }

	int getScore() { return this->_score; }
	void scoreIncrease() { this->_score++; }
	void scoreDecrease() { this->_score--; }

private:
	int _health = 20;
	int _score = 0;
};

class Bonus : public sf::RectangleShape {
public:
	Bonus(float mX, float mY) {
		this->setPosition(mX, mY);
		this->setSize({ 10, 10 });
		this->setFillColor(sf::Color::White);
		this->setOrigin(5, 5);
	}
	void update();
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();
	sf::Vector2f getVelocity() { return this->_velocity; }
	bool getStatus() { return this->_isCaught; }
	void setStatus(bool status) { this->_isCaught = status; }

	bool getMovingStatus() { return this->_isMoving; }
	void setMovingStatus(bool status) { this->_isMoving = status; }

	bool getFailStatus() { return this->_isFailed; }
	void setFailStatus(bool status) { this->_isFailed = status; }
	void setCoordinates(float mX, float mY) {
		this->_bonusCoordinates.x = mX;
		this->_bonusCoordinates.y = mY;
	}

	bonusType getBonusType() { return this->_bonus; }
	void setBonusType(bonusType bonus) { this->_bonus = bonus; }


	void spawnMovingBrick(std::vector <MovingBrick>& movingBricks);
	void spawnBall(std::vector<Ball>& balls);
private:
	sf::Vector2f _bonusCoordinates{ 0,0 };
	sf::Vector2f _velocity{ 0, bonusVelocity };
	bool _isCaught = false;
	bool _isMoving = false;
	bool _isFailed = false;
	bonusType _bonus = bonusType::NONE;
};
#endif