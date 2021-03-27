#ifndef RECT_HPP
#define RECT_HPP

#include "vector2d.hpp"

struct absrect
{
    int left;
    int top;
    int right;
    int bottom;    
};

struct rect
{
    rect(Vector2d location, Vector2d size);
    Vector2d location;
    Vector2d size;

    static rect from_absolute(absrect rect);
};



#endif