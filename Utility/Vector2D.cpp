#include "stdafx.h"

Vector2D::Vector2D(float x_coord, float y_coord) : x(x_coord), y(y_coord)
{}

void Vector2D::Normalize()
{
	float length = Magnitude();
	if (length > 0)
	{
		x /= length;
		y /= length;
	}
}

Vector2D Vector2D::GetNormalized() const
{
	float length = Magnitude();
	length = (length > 0) ? length : 1.0f;
	return Vector2D(x / length, y / length);
}

void Vector2D::Rotate(float angle)
{
	float originalX = x;
	x = x * cos(angle) - y * sin(angle);
	y = originalX * sin(angle) + y * cos(angle);
}

void Vector2D::Limit(float max)
{
	if (MagnitudeSquared() > max*max)
	{
		Normalize();
		x *= max;
		y *= max;
	}
}

float Vector2D::DotProduct(const Vector2D& v) const
{
	return (x * v.x + y * v.y);
}

float Vector2D::Magnitude() const
{
	return sqrt(x * x + y * y);
}

float Vector2D::MagnitudeSquared() const
{
	return x * x + y * y;
}

float Vector2D::Distance(const Vector2D& v) const
{
	float dx = x - v.x;
	float dy = y - v.y;
	return sqrt(dx * dx + dy * dy);
}

float Vector2D::DistanceSquared(const Vector2D& v) const
{
	float dx = x - v.x;
	float dy = y - v.y;
	return dx * dx + dy * dy;
}

float Vector2D::Heading() const
{
	float angle = atan2(y, x);
	return angle;
}

Vector2D Vector2D::operator+(const Vector2D& v) const
{
	return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::operator-(const Vector2D& v) const
{
	return Vector2D(x - v.x, y - v.y);
}

Vector2D Vector2D::operator*(float value) const
{
	return Vector2D(x * value, y * value);
}

Vector2D Vector2D::operator/(float value) const
{
	return Vector2D(x / value, y / value);
}

Vector2D & Vector2D::operator+=(const Vector2D& right)
{
	this->x += right.x;
	this->y += right.y;
	return *this;
}

Vector2D & Vector2D::operator-=(const Vector2D& right)
{
	this->x -= right.x;
	this->y -= right.y;
	return *this;
}

Vector2D & Vector2D::operator*=(float value)
{
	this->x *= value;
	this->y *= value;
	return *this;
}

Vector2D & Vector2D::operator/=(float value)
{
	this->x /= value;
	this->y /= value;
	return *this;
}

float Vector2D::AngleBetween(const Vector2D& v1, const Vector2D& v2)
{
	float dot = v1.DotProduct(v2);
	float theta = static_cast<float>(acos(dot / (v1.Magnitude() * v2.Magnitude())));
	return theta;
}
