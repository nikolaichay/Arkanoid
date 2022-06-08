#ifndef FUNC_H
#define FUNC_H
#include "fig.h"
template <class T1, class T2> bool isIntersecting(T1& A, T2& B);
void testCollision(Racket& racket, std::vector<Ball>& balls);
void testCollision(Brick& brick, std::vector<Ball>& balls, Player& player);
void testCollision(Racket& racket, Bonus& bonus);
void testCollision(Brick& brick, MovingBrick& movingBrick);
void testCollision(MovingBrick& movingBrickFirst, MovingBrick& movingBrickSecond);
void testCollision(Ball& white, Ball& red);
#endif 
