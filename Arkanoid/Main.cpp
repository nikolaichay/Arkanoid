#include <iostream>
#include <ctime>
#include <string>
#include "func.h"
#include "fig.h"
#include <sstream>
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 680), "Arkanoid");
	window.setFramerateLimit(120);
	Player player;
	sf::Font font;
	const std::string fontName("arial.ttf");
	font.loadFromFile(fontName);

	sf::Text scoreText;
	sf::Text healthText;
	sf::Text lossText;
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setPosition(500, 450);

	healthText.setFillColor(sf::Color::Yellow);
	healthText.setFont(font);
	healthText.setCharacterSize(20);
	healthText.setPosition(500, 475);

	lossText.setFillColor(sf::Color::Red);
	lossText.setFont(font);
	lossText.setCharacterSize(50);
	lossText.setPosition(windowWidth / 5, windowHeight / 2);
	lossText.setString("YOU LOSE");

	Racket rack(windowWidth / 2, windowHeight - 50);

	std::vector <Ball> bl;
	std::vector <Brick> standardBricks;
	std::vector <Brick> velocityBoostBricks;
	std::vector <Brick> indestructibleBricks;
	std::vector <Brick> strongerHealthBricks;
	std::vector <Brick> bonusBlocks;
	std::vector <Bonus> bonuses;
	std::vector <MovingBrick> movingBricks;

	bl.emplace_back(windowWidth / 2, 3 * windowHeight / 4);
	/*bl.emplace_back(windowWidth / 2, windowHeight / 2);
	bl[1].setFillColor(sf::Color::Blue);*/
	bonusBlocks.emplace_back(0.85 * windowHeight / 4, windowWidth / 4);
	bonusBlocks.emplace_back(0.55 * windowHeight / 4, 1.3 * windowWidth / 4);
	bonusBlocks[0].setFillColor(sf::Color::Red);
	bonusBlocks[1].setFillColor(sf::Color::Red);
	bonuses.emplace_back(0.85 * windowHeight / 4, windowWidth / 4);
	bonuses[0].setBonusType(bonusType::MOVINGBRICK);

	bonuses.emplace_back(0.55 * windowHeight / 4, 1.3 * windowWidth / 4);
	bonuses[1].setBonusType(bonusType::ADDBALL);

	/*Standard blocks generation*/
	for (int iX = 0; iX < countStandardX; iX++) {
		for (int iY = 0; iY < countStandardY; iY++) {
			standardBricks.emplace_back((iX + 1) * (blockWidth + 3) + 50,
				(iY + 2) * (blockHeight + 25));
		}
	}
	/*Velocity boost blocks*/
	for (int iX = 0; iX < countVelocityBoostBlocks; iX++) {
		velocityBoostBricks.emplace_back(3 * windowWidth / 4, (iX + 2) * (blockHeight + 25));
		velocityBoostBricks[iX].setVelocityBoost(ballVelocityBoost);
		velocityBoostBricks[iX].setFillColor(sf::Color::Green);

	}
	/*Indestructible blocks*/
	for (int iX = 0; iX < countIndestructibleBlocks; iX++) {
		indestructibleBricks.emplace_back(2 * windowWidth / 6, (iX + 2) * (blockHeight + 50));
		indestructibleBricks[iX].setDestructibility(false);
		indestructibleBricks[iX].setFillColor(sf::Color::Blue);
		indestructibleBricks[iX].setHealth(-1);
	}
	/*Stronger health blocks */
	for (int iX = 0; iX < countIndestructibleBlocks; iX++) {
		strongerHealthBricks.emplace_back(3 * windowWidth / 6, (iX + 2) * (blockHeight + 25));
		strongerHealthBricks[iX].setFillColor(sf::Color::Cyan);
		strongerHealthBricks[iX].setHealth(2);
	}


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}

		for (auto& brick : standardBricks) {
			testCollision(brick, bl, player);
			for (auto& movingBrick : movingBricks) {
				testCollision(brick, movingBrick);
			}
		}

		for (auto& brick : velocityBoostBricks) {
			testCollision(brick, bl, player);
			for (auto& movingBrick : movingBricks) {
				testCollision(brick, movingBrick);
			}
		}

		for (auto& brick : indestructibleBricks) {
			testCollision(brick, bl, player);
			for (auto& movingBrick : movingBricks) {
				testCollision(brick, movingBrick);
			}
		}

		for (auto& brick : strongerHealthBricks) {
			testCollision(brick, bl, player);
			for (auto& movingBrick : movingBricks) {
				testCollision(brick, movingBrick);
			}
		}
		for (auto& movingBrick : movingBricks) {
			testCollision(movingBrick, bl, player);
			for (auto& innerMovingBrick : movingBricks) {
				testCollision(movingBrick, innerMovingBrick);
			}
		}

		for (int i = 0; i < bonusBlocks.size(); i++) {
			testCollision(bonusBlocks[i], bl, player);
			if (bonusBlocks[i].getStatus()) {
				bonusBlocks[i].setFillColor(sf::Color::Black);
				bonusBlocks[i].setPosition({ -100,-100 });
				bonuses[i].setMovingStatus(true);
			}

		}

		standardBricks.erase(remove_if(begin(standardBricks), end(standardBricks), [](Brick& brick) {return brick.getStatus(); }), end(standardBricks));
		velocityBoostBricks.erase(remove_if(begin(velocityBoostBricks), end(velocityBoostBricks), [](Brick& brick) {return brick.getStatus(); }), end(velocityBoostBricks));
		indestructibleBricks.erase(remove_if(begin(indestructibleBricks), end(indestructibleBricks), [](Brick& brick) {return brick.getStatus(); }), end(indestructibleBricks));
		strongerHealthBricks.erase(remove_if(begin(strongerHealthBricks), end(strongerHealthBricks), [](Brick& brick) {return brick.getStatus(); }), end(strongerHealthBricks));
		movingBricks.erase(remove_if(begin(movingBricks), end(movingBricks), [](Brick& brick) {return brick.getStatus(); }), end(movingBricks));
		std::ostringstream scorestream;
		std::ostringstream healthtream;
		healthtream << player.getHealth();
		scorestream << player.getScore();
		std::string scoretext = "Score: " + scorestream.str();
		scoreText.setString(scoretext);
		healthText.setString("Health: " + healthtream.str());

		rack.update();
		for (auto& ball : bl) {
			ball.update(player);
		}
		testCollision(rack, bl);
		if (bl[1].getFillColor() == sf::Color::Blue) {
			testCollision(bl[0], bl[1]);
		}
		for (auto& bonus : bonuses) {
			testCollision(rack, bonus);
		}
		window.clear();
		for (auto& ball : bl) {
			window.draw(ball);
		}
		window.draw(rack);
		window.draw(scoreText);
		window.draw(healthText);
		for (auto& brick : standardBricks) {
			window.draw(brick);
		}
		for (auto& brick : velocityBoostBricks) {
			window.draw(brick);
		}
		for (auto& brick : indestructibleBricks) {
			window.draw(brick);
		}
		for (auto& brick : strongerHealthBricks) {
			window.draw(brick);
		}
		for (auto& brick : bonusBlocks) {
			window.draw(brick);
		}
		for (auto& movingBrick : movingBricks) {
			if (movingBrick.getAliveStatus()) {
				window.draw(movingBrick);
			}
		}
		for (auto& bonus : bonuses) {
			if ((!bonus.getStatus()) && (bonus.getMovingStatus())) {
				bonus.update();
			}
			window.draw(bonus);
		}
		for (auto& bonus : bonuses) {
			if (bonus.getStatus()) {
				if (bonus.getBonusType() == bonusType::MOVINGBRICK) {
					bonus.spawnMovingBrick(movingBricks);
				}
				if (bonus.getBonusType() == bonusType::ADDBALL) {
					bonus.spawnBall(bl);
				}
				bonuses.erase(remove_if(begin(bonuses), end(bonuses), [](Bonus& bonus) {return bonus.getStatus(); }), end(bonuses));
			}
		}
		for (auto& movingBrick : movingBricks) {
			if (movingBrick.getAliveStatus()) {
				movingBrick.update();
			}
		}
		if (player.getScore() > 25) {
			lossText.setString("YOU WIN");
			lossText.setFillColor(sf::Color::Green);
			for (auto& ball : bl) {
				ball.setVelocity({ 0,0 });
			}
			window.draw(lossText);
		}
		if (player.getHealth() == 0) {
			for (auto& ball : bl) {
				ball.setVelocity({ 0,0 });
			}
			window.draw(lossText);
		}
		window.display();
	}
	bonusBlocks.erase(remove_if(begin(bonusBlocks), end(bonusBlocks), [](Brick& brick) {return brick.getStatus(); }), end(bonusBlocks));
	return 0;
}