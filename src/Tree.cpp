#include "Tree.h"
#include "Graphics.h"
#include "Engine.h"

#define COLLIDER_OFFSET_X 20
#define COLLIDER_OFFSET_Y 30
#define COLLIDER_WIDTH 164
#define COLLIDER_HEIGHT 198

Tree::Tree(Properties* p, float scale) : Charecter(p)
{
    m_treeVelocity = 4.0f;
    m_physics = new Physics();
    m_scale = scale;
    m_collider = {(int)(m_transform->x + COLLIDER_OFFSET_X), (int)(m_transform->y + COLLIDER_OFFSET_Y), COLLIDER_WIDTH, COLLIDER_HEIGHT};
}

void Tree::render()
{
    Graphics::get()->render(m_id, m_transform->x, m_transform->y, m_width, m_height, m_scale);

    // for collider
	SDL_SetRenderDrawColor(Engine::get()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Engine::get()->getRenderer(), &m_collider);

}

void Tree::partialRender(int xOffset, int yOffset, int widthOffset, int heightOffset) {
    Graphics::get()->render(m_id, m_transform->x + xOffset, m_transform->y + yOffset, m_width - widthOffset, m_height - heightOffset, m_scale);

    // for visualization
	SDL_SetRenderDrawColor(Engine::get()->getRenderer(), 0, 0, 255, 255);
	SDL_RenderDrawRect(Engine::get()->getRenderer(), new SDL_Rect({(int)(m_transform->x + xOffset), (int)(m_transform->y + yOffset), (int)((m_width - widthOffset) * m_scale), (int)((m_height - heightOffset) * m_scale)}));
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
