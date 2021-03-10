#include "rasterizer.hpp"

void Rasterizer::draw_sprite(PixelWriter &writer, Sprite &sprite, int x_origin, int y_origin)
{
    writer.set_line_length(sprite.width);
    writer.write_pixeldata(x_origin, y_origin, sprite.pixelpackets, sprite.packet_count);
}

void Rasterizer::draw_rectangle(PixelWriter &writer, int x, int y, int width, int height, int color)
{
    writer.set_line_length(width);

    pixel_packet line[2] = { { width, color, 0, PACKET_SINGLE_COLOR }, { 0, 0, 0, PACKET_NEXT_LINE } };

    for(int i = 0; i < height; i++)
    {
        writer.write_pixeldata(x, y + i, line, 2);
    }

}