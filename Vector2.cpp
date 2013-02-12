#include "Vector2.h"


Vector2::~Vector2(void)
{
}

Vector2 Vector2::operator + (const Vector2 &otherVec) const
{
	return Vector2(this->x + otherVec.x, this->y + otherVec.y);
}
Vector2& Vector2::operator += (const Vector2 &otherVec)
{
	//c = a + b
	//a += b
	return Vector2(this->x += otherVec.x, this->x += otherVec.y);
}

Vector2 Vector2::operator- (const Vector2 &otherVec) const
{
	return Vector2(this->x - otherVec.x, this->y - otherVec.y);
}
Vector2& Vector2::operator -= (const Vector2 &otherVec)
{
	return Vector2(this->x -= otherVec.x, this->x -= otherVec.y);
}

float Vector2::dot(const Vector2 &otherVec) const
{
	return float((this->x * otherVec.x) + (this->y * otherVec.y));
}