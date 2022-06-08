#include "fig.h"
#include "func.h"

template <class T1, class T2> bool isIntersecting(T1& A, T2& B) {
	return (A.right() >= B.left()) && (A.left() <= B.right()) && (A.bottom() >= B.top()) && (A.top() <= B.bottom());
}

void testCollision(Ball& white, Ball& red) {
	if (!isIntersecting(white, red)) {
		return;
	}

	float overlapLeft = white.right() - red.left();
	float overlapRight = red.right() - white.left();
	float overlapTop = white.bottom() - red.top();
	float overlapBottom = red.bottom() - white.top();

	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
	float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

	if (abs(minOverlapX) < abs(minOverlapY)) {
		white.setXVelocity(ballFromLeft ? -abs(white.getVelocity().x) : abs(white.getVelocity().y));
		red.setXVelocity(ballFromLeft ? abs(red.getVelocity().x) : -abs(red.getVelocity().y));
	}
	else {
		white.setYVelocity(ballFromTop ? -abs(white.getVelocity().x) : abs(white.getVelocity().y));
		red.setYVelocity(ballFromTop ? abs(red.getVelocity().x) : -abs(red.getVelocity().y));
	}


}
void testCollision(Racket& racket, std::vector<Ball>& balls) {
	for (auto& ball : balls) {
		if (isIntersecting(racket, ball)) {
			ball.setYVelocity(-ballVelocity);
			if (ball.x() < racket.x()) {
				ball.setXVelocity(-ballVelocity);
			}
			else {
				ball.setXVelocity(ballVelocity);
			}
		}
	}
}

void testCollision(Brick& brick, std::vector<Ball>& balls, Player& player) {
	for (auto& ball : balls) {
		if (isIntersecting(brick, ball)) {
			if (brick.getHealth() > 0) {
				player.scoreIncrease();
				brick.healthDecrease();
			}
			/*We delete only destructible blocks. Setting status "destroyed" to delete later*/
			if (brick.getDestructibility() && (brick.getHealth() == 0)) {
				brick.setStatus(true);
			}
			/*Speed boost*/
			if (brick.getVelocityBoost() == 1.f) {
				ball.setVelocity({ (ball.getVelocity().x > 0) ? ballVelocity : -ballVelocity,(ball.getVelocity().y > 0) ? ballVelocity : -ballVelocity });
			}
			else ball.setVelocity({ ball.getVelocity().x * brick.getVelocityBoost(), ball.getVelocity().y * brick.getVelocityBoost() });



			float overlapLeft = ball.right() - brick.left();
			float overlapRight = brick.right() - ball.left();
			float overlapTop = ball.bottom() - brick.top();
			float overlapBottom = brick.bottom() - ball.top();

			bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
			bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

			float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
			float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

			if (abs(minOverlapX) < abs(minOverlapY)) {
				ball.setXVelocity(ballFromLeft ? -abs(ball.getVelocity().x) : abs(ball.getVelocity().x));
			}
			else {
				ball.setYVelocity(ballFromTop ? -abs(ball.getVelocity().y) : abs(ball.getVelocity().y));
			}
		}
	}
}

void testCollision(Racket& racket, Bonus& bonus) {
	if (!isIntersecting(racket, bonus)) {
		return;
	}
	else {
		bonus.setStatus(true);
	}
}

void testCollision(Brick& brick, MovingBrick& movingBrick) {
	if (!isIntersecting(brick, movingBrick)) {
		return;
	}
	float overlapLeft = movingBrick.right() - brick.left();
	float overlapRight = brick.right() - movingBrick.left();
	float overlapTop = movingBrick.bottom() - brick.top();
	float overlapBottom = brick.bottom() - movingBrick.top();

	bool movingBrickFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool movingBrickFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverlapX = movingBrickFromLeft ? overlapLeft : overlapRight;
	float minOverlapY = movingBrickFromTop ? overlapTop : overlapBottom;

	if (abs(minOverlapX) < abs(minOverlapY)) {
		movingBrick.setXVelocity(movingBrickFromLeft ? -abs(movingBrick.getVelocity().x) : abs(movingBrick.getVelocity().x));
	}
	else {
		movingBrick.setYVelocity(movingBrickFromTop ? -abs(movingBrick.getVelocity().y) : abs(movingBrick.getVelocity().y));
	}
}

void testCollision(MovingBrick& movingBrickFirst, MovingBrick& movingBrickSecond) {
	if (!isIntersecting(movingBrickFirst, movingBrickSecond)) {
		return;
	}
	float overlapLeft = movingBrickSecond.right() - movingBrickFirst.left();
	float overlapRight = movingBrickFirst.right() - movingBrickSecond.left();
	float overlapTop = movingBrickSecond.bottom() - movingBrickFirst.top();
	float overlapBottom = movingBrickFirst.bottom() - movingBrickSecond.top();

	bool movingBrickFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool movingBrickFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverlapX = movingBrickFromLeft ? overlapLeft : overlapRight;
	float minOverlapY = movingBrickFromTop ? overlapTop : overlapBottom;

	if (abs(minOverlapX) < abs(minOverlapY)) {
		movingBrickSecond.setXVelocity(movingBrickFromLeft ? -abs(movingBrickSecond.getVelocity().x) : abs(movingBrickSecond.getVelocity().x));
	}
	else {
		movingBrickSecond.setYVelocity(movingBrickFromTop ? -abs(movingBrickSecond.getVelocity().y) : abs(movingBrickSecond.getVelocity().y));
	}
}