#ifndef VGAPIXELWRITER_HPP
#define VGAPIXELWRITER_HPP

#include "pixelwriter.hpp"
#include <stdio.h>
#include <i86.h>

class VgaPixelWriter : public PixelWriter
{
public:
    VgaPixelWriter(surface_rect dimensions);    
    void write_pixeldata(int x_origin, int y_origin, const pixel_packet *operations, int packet_count);    
    void copy_line(int x_origin, int y_origin, void *source, int numpixels);
};

#endif