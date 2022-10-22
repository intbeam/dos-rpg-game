#ifndef RASTERIZER_HPP
#define RASTERIZER_HPP

#include "imagedata.hpp"
#include "rect.hpp"

class Rasterizer
{
public:    
    virtual void draw_sprite(Sprite *sprite, int x_origin, int y_origin) = 0;
    virtual void draw_rectangle(int x, int y, int width, int height, int color) = 0;
    virtual void fill_rectangle(int x, int y, int width, int height, int color) = 0;
    virtual void copy_bits(const char *source,int source_width, rect source_rect, int destination_x, int destination_y) = 0;
};

#endif
