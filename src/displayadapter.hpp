#ifndef DISPLAYADAPTER_HPP
#define DISPLAYADAPTER_HPP

#include "displaymeta.hpp"
#include "rect.hpp"

class DisplayAdapter
{
public:
    virtual surface_rect get_surface_dimensions() = 0;
    virtual void scroll(rect area, Vector2d vec) = 0;
    virtual void begin_frame();
    virtual void end_frame();
};

#endif
