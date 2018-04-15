#include "stdafx.h"
#include <fstream>
#include "../table.h"

CTable Utilities::LoadBackground(const char * fileName)
{
	CTable table;
	std::fstream file;
	file.open(fileName, std::fstream::in);
	if (file.is_open())
	{
		int version = 0;
		file >> version;
		if (version <= 1)
		{
			while (!file.eof())
			{
				CLineSegment line;
				int type;
				file >> type;
				line.m_type = static_cast<LineType>(type);
				file >> line.m_start.m_x;
				file >> line.m_start.m_y;
				file >> line.m_end.m_x;
				file >> line.m_end.m_y;
				table.m_lines.push_back(line);
			}
		}
		file.close();
	}
	return table;
}

int Utilities::LoadRecordScore(const char * fileName)
{
	int score = 0;
	std::fstream file;
	file.open(fileName, std::fstream::in);
	if (file.is_open())
	{
		file >> score;
		file.close();
	}
	return score;
}

void Utilities::SaveRecordScore(const char* fileName, int score)
{
	std::fstream file;
	file.open(fileName, std::fstream::out);
	if (file.is_open())
	{
		file << score;
		file.close();
	}
}

float Utilities::NormalizeAngle(float angle)
{
	const float width = 0.0f - 360.0f;
	const float offsetValue = angle;
	return (offsetValue - (floor(offsetValue / width) * width));
}

Vector2D Utilities::FindClosestPointOnLine(const Vector2D & point, const Vector2D & startLinePoint, const Vector2D & endLinePoint)
{
	float a1 = endLinePoint.y - startLinePoint.y;
	float b1 = startLinePoint.x - endLinePoint.x;
	float c1 = a1 * startLinePoint.x + b1 * startLinePoint.y;
	float c2 = -b1 * point.x + a1 * point.y;
	float det = (a1 * a1) - (-b1 * b1);
	float px = 0;
	float py = 0;

	if (det != 0)
	{
		px = (a1 * c1 - b1 * c2) / det;
		py = (a1 * c2 - (-b1 * c1)) / det;
	}
	else
	{
		px = point.x;
		py = point.y;
	}
	return Vector2D(px, py);
}
