#ifndef PIXELRASTERIZER_HPP
#define PIXELRASTERIZER_HPP

#include "pixelwriter.hpp"
#include "spritemanager.hpp"
#include "rasterizer.hpp"
#include <stdio.h>

class PixelRasterizer : public Rasterizer
{
private:
    PixelWriter &pixel_writer;
public:
    PixelRasterizer(PixelWriter &pixel_writer);
    void draw_sprite(Sprite &sprite, int x_origin, int y_origin);
    void draw_rectangle(int x, int y, int width, int height, int color);
    void copy_bits(const char *source, int source_width, rect source_rect, int destination_x, int destination_y);
};

#endif