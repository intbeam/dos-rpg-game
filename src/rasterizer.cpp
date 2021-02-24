#include "rasterizer.hpp"

void Rasterizer::draw_sprite(PixelWriter &writer, Sprite &sprite, int x_origin, int y_origin)
{
    writer.write_pixeldata(x_origin, y_origin, sprite.pixelpackets, sprite.packet_count);
}