#pragma once

#include <random>
class CTable;

class Utilities
{
public:
	static bool CircleOverlap(const Vector2D & position1, float radius1, const Vector2D & position2, float radius2)
	{
		float distanceSquared = position1.DistanceSquared(position2);
		float radiusSum = radius1 + radius2;
		return (distanceSquared <= (radiusSum * radiusSum));
	}

	static bool PointCircleOverlap(const Vector2D& point, const Vector2D& circlePosition, float circleRadius)
	{
		float distanceSquared = point.DistanceSquared(circlePosition);
		return (distanceSquared <= (circleRadius * circleRadius));
	}

	static float ToRadians(float degrees)
	{
		return static_cast<float>(degrees * M_PI / 180.0f);
	}

	static float ToDegrees(float radians)
	{
		return static_cast<float>(radians * 180.0f / M_PI);
	}

	static float MapValue(float value, float start1, float end1, float start2, float end2)
	{
		float result = start2 + (end2 - start2) * ((value - start1) / (end1 - start1));
		return result;
	}

	static float Random(float min, float max)
	{
		thread_local static std::mt19937 gen{ std::random_device{}() };
		thread_local static std::uniform_real_distribution<float> pick{ min, max };
		return pick(gen);
	}

	static CTable LoadBackground(const char* fileName);
	static int LoadRecordScore(const char* fileName);
	static void SaveRecordScore(const char* fileName, int score);
	static float NormalizeAngle(float angle);

	static Vector2D FindClosestPointOnLine(const Vector2D& position, const Vector2D& startLinePoint, const Vector2D& endLinePoint);

private:
	Utilities() {}
};