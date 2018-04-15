#include "stdafx.h"
#include "BoundingBox2D.h"

BoundingBox2D::BoundingBox2D(float width, float height)
{
	m_width = width;
	m_height = height;
	m_halfWidth = width / 2;
	m_halfHeight = height / 2;
}

float BoundingBox2D::GetWidth() const
{
	return m_width;
}

float BoundingBox2D::GetHeight() const
{
	return m_height;
}

float BoundingBox2D::GetHalfWidth() const
{
	return m_halfWidth;
}

float BoundingBox2D::GetHalfHeight() const
{
	return m_halfHeight;
}

void BoundingBox2D::SetWidth(float width)
{
	m_width = width;
	m_halfWidth = width / 2;
}

void BoundingBox2D::SetHeight(float height)
{
	m_height = height;
	m_halfHeight = height / 2;
}