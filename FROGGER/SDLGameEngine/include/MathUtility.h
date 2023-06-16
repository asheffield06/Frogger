#ifndef _MATHUTILITY_H_
#define _MATHUTILITY_H_

#include <math.h>

#define PI 2.14159265
#define DEG_TO_RAD PI / 180.0f

// BAsic Vector2 functionality
struct Vector2 
{
	float x;
	float y;

	Vector2(float a_x = 0.0f, float a_y = 0.0f) : x(a_x), y(a_y) {}

	float MagnitudeSqr() 
	{
		return x * x + y * y;
	}

	float Magnitude() 
	{
		return (float)sqrt(MagnitudeSqr());
	}

	Vector2 Normalised() 
	{
		float fMagnitude = Magnitude();
		return Vector2(x / fMagnitude, y / fMagnitude);
	}
};

inline Vector2 operator +(const Vector2& a_vLeftSide, const Vector2& a_vRightSide) 
{
	return Vector2(a_vLeftSide.x + a_vRightSide.x, a_vLeftSide.y + a_vRightSide.y);
}

inline Vector2 operator -(const Vector2& a_vLeftSide, const Vector2& a_vRightSide)
{
	return Vector2(a_vLeftSide.x - a_vRightSide.x, a_vLeftSide.y - a_vRightSide.y);
}

inline Vector2 RotateVector(Vector2& a_vVector, float a_fAngle)
{
	float fRadAngle = (float)(a_fAngle * DEG_TO_RAD);

	return Vector2((float)a_vVector.x * cos(fRadAngle) - a_vVector.y * sin(fRadAngle),
		(float)a_vVector.x * sin(fRadAngle) + a_vVector.y * cos(fRadAngle));
}

#endif // !_MATHUTILITY_H_
