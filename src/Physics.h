#ifndef __Physics__
#define __Physics__

#include "Vector2d.h"

class Physics
{
    float m_gravity;
    float m_mass;
    Vector2d m_force;
    Vector2d m_friction;
    Vector2d m_position;
    Vector2d m_velocity;
    Vector2d m_accelaration;

public:
    Physics(float gravity = 9.8f, float mass = 1.0f);
    void update(float dt);

    //force
    inline void applyForce(Vector2d force) { m_force = force; }
    inline void unSetForce() { m_force = Vector2d(0, 0); }

    //friction
    inline void applyFriction(Vector2d friction) { m_friction = friction; }
    inline void unSetFriction() { m_friction = Vector2d(0, 0); }

    //getters and setters
    inline void setGravity(float gravity) { m_gravity = gravity; }
    inline void setFriction(float friction) { m_friction = friction; }
    inline Vector2d getPosition() { return m_position; }
    inline Vector2d getVelocity() { return m_velocity; }
    inline Vector2d getAccelaration() { return m_accelaration; }
    inline float getMass() { return m_mass; }
    inline float getGravity() { return m_gravity; }
    
};

#endif