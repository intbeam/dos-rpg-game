#include "vgadisplayadapter.hpp"

VgaDisplayAdapter::VgaDisplayAdapter() : enable_vsync(1)
{
    __asm
    {
        mov ax, 13h
        int 10h
    }

    /* disable chain 4 */
   // outp( SC_INDEX, MEMORY_MODE );
    //outp( SC_DATA, 0x06 );
    /* disable doubleword mode */
    //outp( CRTC_INDEX, UNDERLINE_LOCATION );
    //outp( CRTC_DATA, 0x00 );
    /* disable word mode */
    //outp( CRTC_INDEX, MODE_CONTROL );
    //outp( CRTC_DATA, 0xE3 );

    //outp( CRTC_INDEX, LINE_OFFSET );
    //outp( CRTC_DATA, 80 );
  
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

void VgaDisplayAdapter::scroll(rect area, Vector2d vec)
{
    char ac;
    int high_address, low_address, o;

    int vga_y_pan = vec.y;
    int vga_x_pan = vec.x / 4;
    int vga_x_pel_pan = vec.x % 4;

    o = vga_y_pan * 320 + vga_x_pan;
    high_address = HIGH_ADDRESS | (o & 0xFF00);
    low_address = LOW_ADDRESS | (o << 8);
    outp( CRTC_INDEX, high_address );
    outp( CRTC_INDEX, low_address );
    _disable();
    inp( INPUT_STATUS );
    ac = inp( AC_WRITE );
    outp( AC_WRITE, PEL_PANNING );
    outp( AC_WRITE, vga_x_pel_pan);
    outp( AC_WRITE, ac );
    wait_vsync();
    _enable();
}