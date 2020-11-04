#ifndef __Background__
#define __Background__

#include <string>

class Background
{
    std::string m_id;
    int m_x, m_x2, m_y, m_width, m_height;
    int m_scrollSpeed;

public:
    Background(std::string id, int x, int y, int width, int height, int m_scrollSpeed);

    void update();
    void render(bool fullScreen = false);

};

#endif