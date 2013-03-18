#pragma once
class Vector2
{
public:
	Vector2()
	{
		x = y = 0.0f;
	}
	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	Vector2(const Vector2 &other)
	{
		x = other.x;
		y = other.y;
	}
		Vector2(float _vec[2])
	{
		vec[0] = _vec[0];
		vec[1] = _vec[1];
	}

	~Vector2(void);

	Vector2& operator += (const Vector2 &otherVec);
	Vector2 operator + (const Vector2 &otherVec) const;

	Vector2& operator -= (const Vector2 &otherVec);
	Vector2 operator- (const Vector2 &otherVec) const;

	float dot(const Vector2 &otherVec) const;

	void normalize();
	float getLength() const;

	//float x,y;

	union
	{
		struct
		{
			float x,y;
		};
		float vec[2];
	};
};

//////////////////////////////////////
//C++ built in square root is slow.
//new one with assembly
static float asm_sqrt(float n)
{
	_asm fld n
	_asm fsqrt
}