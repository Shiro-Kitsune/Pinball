#include "stdafx.h"
#include "BoundingCircle2D.h"

BoundingCircle2D::BoundingCircle2D(float radius) : m_radius(radius)
{}


float BoundingCircle2D::GetRadius() const
{
	return m_radius;
}

void BoundingCircle2D::SetRadius(float radius)
{
	m_radius = radius;
}
