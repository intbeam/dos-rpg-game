#ifndef DISPLAYADAPTER_HPP
#define DISPLAYADAPTER_HPP

#include "displaymeta.hpp"

class DisplayAdapter
{
public:
    virtual surface_rect get_surface_dimensions();
};

#endif
