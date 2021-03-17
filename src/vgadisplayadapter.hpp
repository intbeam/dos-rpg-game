#ifndef VGADISPLAYADAPTER_HPP
#define VGADISPLAYADAPTER_HPP

#include <conio.h>
#include <stdio.h>
#include "displayadapter.hpp"
#include "imagedata.hpp"



class VgaDisplayAdapter : public DisplayAdapter
{
private:
    void wait_vsync();
public:
    int enable_vsync;
    VgaDisplayAdapter();
    surface_rect get_surface_dimensions();
    void set_palette(palette_24bpp &pal);
    void begin_frame();
    void end_frame();
};

#endif
