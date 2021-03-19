#ifndef DISPLAYMETA_HPP
#define DISPLAYMETA_HPP
#include "vector2d.hpp"

struct surface_rect
{
    int width;
    int height;
};

struct rect
{
    int left;
    int top;
    int right;
    int bottom;

    rect displace(Vector2d vec);

};

#endif
