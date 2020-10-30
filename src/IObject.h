#ifndef __IObject__
#define __IObject__

class IObject
{
public:
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void free() = 0;
};

#endif