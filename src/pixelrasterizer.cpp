#include "pixelrasterizer.hpp"

PixelRasterizer::PixelRasterizer(PixelWriter &pixel_writer) : pixel_writer(pixel_writer)
{

}

void PixelRasterizer::draw_sprite(Sprite *sprite, int x_origin, int y_origin)
{
    this->pixel_writer.set_line_length(sprite->width);
    this->pixel_writer.write_pixeldata(x_origin, y_origin, sprite->pixelpackets, sprite->packet_count);
}

void PixelRasterizer::draw_rectangle(int x, int y, int width, int height, int color)
{
    this->pixel_writer.set_line_length(width);

    pixel_packet line[2] = { { width, color, 0, PACKET_SINGLE_COLOR }, { 0, 0, 0, PACKET_NEXT_LINE } };

    for(int i = 0; i < height; i++)
    {
        this->pixel_writer.write_pixeldata(x, y + i, line, 2);
    }

}

void PixelRasterizer::copy_bits(const char *source, int source_width, rect source_rect, int destination_x, int destination_y)
{    
    char *lineptr = ((char *)source) + (source_rect.location.y * source_width + source_rect.location.x);
    int i;    

    for(i = 0; i < source_rect.size.y; i++)
    {
        this->pixel_writer.copy_line(destination_x, destination_y + i, lineptr, source_rect.size.x);
        lineptr += source_width;
    }

}