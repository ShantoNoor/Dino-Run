#include "Tree.h"
#include "Graphics.h"
#include "Engine.h"

Tree::Tree(Properties* p) : Charecter(p)
{
    m_physics = new Physics();
}

void Tree::render()
{
    Graphics::get()->render(m_id, m_transform->x, m_transform->y, m_width, m_height, 0.15);
}

void Tree::update(float dt)
{
    m_physics->applyForce(Vector2d(-15, 0));
    m_physics->update(dt);
    m_transform->translateX(m_physics->getPosition());
    if(m_transform->x < -m_width*0.15) m_transform->x = Engine::get()->getScreenWidth();
}

void Tree::free()
{

}
