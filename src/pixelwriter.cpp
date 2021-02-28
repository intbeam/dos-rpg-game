#include "pixelwriter.hpp"

PixelWriter::PixelWriter(surface_rect dimensions) : dimensions(dimensions)
{

}

void PixelWriter::set_line_length(int length)
{
    this->line_length = length;
}