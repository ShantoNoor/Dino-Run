#ifndef __GameObject__
#define __GameObject__

#include <SDL.h>
#include <string>

#include "IObject.h"
#include "Transform.h"
#include "Vector2d.h"

struct Properties
{
public:
    Properties(std::string id, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->flip = flip;
        this->id = id;
    }
    float x, y;
    int width, height;
    std::string id;
    SDL_RendererFlip flip;
};

class GameObject : public IObject
{
public:
    GameObject(Properties* p) 
    {
        m_id = p->id;
        m_width = p->width;
        m_height = p->height;
        m_flip = p->flip;
        m_transform = new Transform(p->x, p->y);
        m_origin = new Vector2d((p->x + p->width / 2), (p->y + p->height / 2));
    }

    Vector2d* m_origin;
    Transform* m_transform;
    int m_width, m_height;
    std::string m_id;
    SDL_RendererFlip m_flip;

    virtual void render() = 0;
    virtual void update(float dt) = 0;
    virtual void free() = 0;

    inline Vector2d* getOrigin() { return m_origin; }

};

#endif
