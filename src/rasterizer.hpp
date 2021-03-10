#ifndef RASTERIZER_HPP
#define RASTERIZER_HPP

#include "imagedata.hpp"

class Rasterizer
{
public:
    void draw_sprite(PixelWriter &pixelwriter, Sprite &sprite, int x_origin, int y_origin);
    void draw_rectangle(PixelWriter &pixelwriter, int x, int y, int width, int height, int color);
};

#endif
