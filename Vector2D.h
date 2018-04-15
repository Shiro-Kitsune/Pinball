#pragma once

class Vector2D
{
public:
	Vector2D(float x_coord = 0.0f, float y_coord = 0.0f);

	static float AngleBetween(const Vector2D& v1, const Vector2D& v2);

	void Normalize();
	Vector2D GetNormalized() const;
	void Rotate(float angle);
	void Limit(float maxAmount);
	float DotProduct(const Vector2D& v) const;
	float Magnitude() const;
	float MagnitudeSquared() const;
	float Distance(const Vector2D& v) const;
	float DistanceSquared(const Vector2D& v) const;
	float Heading() const;
	Vector2D operator+(const Vector2D& v) const;
	Vector2D operator-(const Vector2D& v) const;
	Vector2D operator*(float value) const;
	Vector2D operator/(float value) const;
	Vector2D& operator+=(const Vector2D& right);
	Vector2D& operator-=(const Vector2D& right);
	Vector2D& operator*=(float value);
	Vector2D& operator/=(float value);
public:
	float x;
	float y;
};


Vector2D operator*(float value, const Vector2D& vector) {
	return Vector2D(vector.x * value, vector.y * value);
}

Vector2D operator/(float value, const Vector2D& vector) {
	return Vector2D(vector.x / value, vector.y / value);
}