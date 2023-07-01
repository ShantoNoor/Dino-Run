#include "Tree.h"
#include "Graphics.h"
#include "Engine.h"

#define COLLIDER_OFFSET_X 10
#define COLLIDER_OFFSET_Y 10
#define COLLIDER_WIDTH 91
#define COLLIDER_HEIGHT 112

Tree::Tree(Properties* p) : Charecter(p)
{
    m_treeVelocity = 4.0f;
    m_physics = new Physics();
    m_collider = {(int)(m_transform->x + COLLIDER_OFFSET_X), (int)(m_transform->y + COLLIDER_OFFSET_Y), COLLIDER_WIDTH, COLLIDER_HEIGHT};
}

void Tree::render()
{
    Graphics::get()->render(m_id, m_transform->x, m_transform->y, m_width, m_height, 0.15);

    // for collider
	SDL_SetRenderDrawColor(Engine::get()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Engine::get()->getRenderer(), &m_collider);

}

void Tree::update(float dt)
{
    m_physics->applyForce(Vector2d(m_treeVelocity * -1.0f, 0));
    m_physics->update(dt);
    m_transform->translateX(m_physics->getPosition());
    if(m_transform->x < -m_width*0.15) m_transform->x = Engine::get()->getScreenWidth();
    m_collider = {(int)(m_transform->x + COLLIDER_OFFSET_X), (int)(m_transform->y + COLLIDER_OFFSET_Y), COLLIDER_WIDTH, COLLIDER_HEIGHT};
}

void Tree::setTreeVelocity(float newTreeVelocity) {
    m_treeVelocity = newTreeVelocity;
}

void Tree::reset(float x) {
    m_transform->x = x;
    m_collider = {(int)(m_transform->x + COLLIDER_OFFSET_X), (int)(m_transform->y + COLLIDER_OFFSET_Y), COLLIDER_WIDTH, COLLIDER_HEIGHT};
}

void Tree::free()
{
    
}
