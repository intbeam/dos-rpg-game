#include "vgadisplayadapter.hpp"

VgaDisplayAdapter::VgaDisplayAdapter() : enable_vsync(0)
{
    __asm
    {
        mov ax, 13h
        int 10h
    }
}

surface_rect VgaDisplayAdapter::get_surface_dimensions()
{
    surface_rect res;

    res.width = 320;
    res.height = 200;

    return res;
}

void VgaDisplayAdapter::set_palette(palette_24bpp &pal)
{    
    int i;

    for(i = 0; i < pal.count; i++)
    {
        outp(0x3c8, i);
        outp(0x3c9, pal.data[i * 3 + 2] / 4);
        outp(0x3c9, pal.data[i * 3 + 1] / 4);
        outp(0x3c9, pal.data[i * 3] / 4);

    }
}

void VgaDisplayAdapter::wait_vsync()
{
    if(enable_vsync)
    {
        while((inp(0x3da) & 8));
        while(!(inp(0x3da) & 8));
    }
}

void VgaDisplayAdapter::begin_frame()
{    
    wait_vsync();
}

void VgaDisplayAdapter::end_frame()
{

}