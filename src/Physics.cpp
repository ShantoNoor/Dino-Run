#include "Physics.h"

Physics::Physics(float gravity, float mass)
{
    m_gravity = gravity;
    m_mass = mass;
}

void Physics::update(float dt)
{
    m_accelaration.x = (m_force.x + m_friction.x) / m_mass;
    m_accelaration.y = m_gravity + m_force.y / m_mass;
    m_velocity = m_accelaration * dt;
    m_position = m_velocity * dt;
}
