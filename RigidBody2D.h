#pragma once

#include "Component.h"

class RigidBody2D : public Component
{
public:
	RigidBody2D(const Vector2D& velocity = Vector2D(0.0f, 0.0f), const Vector2D & acceleration = Vector2D(0.0f, 0.0f), float angularVelocity = 0.0f, bool isKinematic = false);

	void ApplyForce(Vector2D force);
	const Vector2D& GetVelocity() const;
	const Vector2D& GetAcceleration() const;
	float GetAngularVelocity() const;
	bool IsKinematic() const;
	bool IsGrounded() const;

	void SetVelocity(const Vector2D& velocity);
	void SetAcceleration(const Vector2D& acceleration);
	void SetAngularVelocity(float angularVelocity);
	void SetKinematic(bool kinematic);
	void SetGrounded(bool grounded);
private:
	Vector2D m_velocity;
	Vector2D m_acceleration;
	float m_angularVelocity;
	bool m_kinematic;
	bool m_grounded;
};