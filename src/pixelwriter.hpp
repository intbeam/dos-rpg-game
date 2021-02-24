#ifndef PIXELWRITER_HPP
#define PIXELWRITER_HPP

#include "displayadapter.hpp"


#define PACKET_SINGLE_COLOR     0
#define PACKET_SOURCE_COPY      1
#define PACKET_SKIP             2
#define PACKET_NEXT_LINE        3


typedef struct pixel_packet
{
    int count;
    int value;
    void *data;
    int type;

} pixel_packet;

class PixelWriter
{
protected:
    surface_rect dimensions;
public:
    PixelWriter(surface_rect dimensions);
    virtual void write_pixeldata(int x_origin, int y_origin, const pixel_packet *operations, int packet_count);    
};

#endif
