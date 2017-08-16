#include "Vector2.h"
#include <math.h>

Vector2::Vector2(int x, int y)
{
	this->x = x;
	this->y = y;
}
Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

int Vector2::getX()
{
	return x;
}
int Vector2::getY()
{
	return y;
}
float Vector2::Distance(Vector2 alpha, Vector2 beta)
{
	float xDelta = alpha.getX() - beta.getX();
	float yDelta = alpha.getY() - beta.getY();
	return sqrt(xDelta*xDelta + yDelta*yDelta);
}
Vector2::~Vector2()
{
}