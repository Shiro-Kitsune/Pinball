#include "stdafx.h"
#include "RigidBody2D.h"

RigidBody2D::RigidBody2D(const Vector2D & velocity, const Vector2D & acceleration, float angularVelocity, bool isKinematic) : m_velocity(velocity), m_acceleration(acceleration)
{
	m_angularVelocity = angularVelocity;
	m_kinematic = isKinematic;
}

void RigidBody2D::ApplyForce(Vector2D force)
{
	m_acceleration += force;
}

const Vector2D & RigidBody2D::GetVelocity() const
{
	return m_velocity;
}

const Vector2D & RigidBody2D::GetAcceleration() const
{
	return m_acceleration;
}

float RigidBody2D::GetAngularVelocity() const
{
	return m_angularVelocity;
}

bool RigidBody2D::IsKinematic() const
{
	return m_kinematic;
}

bool RigidBody2D::IsGrounded() const
{
	return m_grounded;
}

void RigidBody2D::SetVelocity(const Vector2D & velocity)
{
	m_velocity = velocity;
}

void RigidBody2D::SetAcceleration(const Vector2D & acceleration)
{
	m_acceleration = acceleration;
}

void RigidBody2D::SetAngularVelocity(float angularVelocity)
{
	m_angularVelocity = angularVelocity;
}

void RigidBody2D::SetKinematic(bool kinematic)
{
	m_kinematic = kinematic;
}

void RigidBody2D::SetGrounded(bool grounded)
{
	m_grounded = grounded;
}