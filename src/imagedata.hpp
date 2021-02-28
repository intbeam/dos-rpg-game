#ifndef IMAGEDATA_HPP
#define IMAGEDATA_HPP

#include "pixelwriter.hpp"

struct palette_24bpp
{
    int count;
    char data[768];
};

class Sprite
{
public:
    int width;
    int height;
    int packet_count;
    pixel_packet *pixelpackets;
};

#endif