#include "Tree.h"
#include "Graphics.h"
#include "Engine.h"

#define TREEVELOCITY 15.0f

Tree::Tree(Properties* p) : Charecter(p)
{
    m_physics = new Physics();
    m_collider = {(int)(m_transform->x + 5), (int)(m_transform->y + 5), 101, 142};
}

void Tree::render()
{
    Graphics::get()->render(m_id, m_transform->x, m_transform->y, m_width, m_height, 0.15);

    // for collider
    // SDL_Rect treeBox = {(int)(m_transform->x + 5), (int)(m_transform->y + 5), 101, 142};
	// SDL_SetRenderDrawColor(Engine::get()->getRenderer(), 255, 0, 0, 255);
	// SDL_RenderDrawRect(Engine::get()->getRenderer(), &m_collider);

}

void Tree::update(float dt)
{
    m_physics->applyForce(Vector2d(-TREEVELOCITY, 0));
    m_physics->update(dt);
    m_transform->translateX(m_physics->getPosition());
    if(m_transform->x < -m_width*0.15) m_transform->x = Engine::get()->getScreenWidth();
    m_collider = {(int)(m_transform->x + 5), (int)(m_transform->y + 5), 101, 142};
}

void Tree::free()
{

}
