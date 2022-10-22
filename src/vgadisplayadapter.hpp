#ifndef VGADISPLAYADAPTER_HPP
#define VGADISPLAYADAPTER_HPP

#include <dos.h>
#include <i86.h>
#include <conio.h>
#include <stdio.h>
#include "displayadapter.hpp"
#include "imagedata.hpp"

/* VGA ports */
#define PALETTE_INDEX 0x3C8
#define PALETTE_DATA 0x3C9
#define INPUT_STATUS 0x03DA
#define MISC_OUTPUT 0x3C2
#define AC_WRITE 0x3C0
#define AC_READ 0x3C1
#define SC_INDEX 0x3C4
#define SC_DATA 0x3C5
#define GC_INDEX 0x03CE
#define GC_DATA 0x03CF
#define CRTC_INDEX 0x03D4
#define CRTC_DATA 0x03D5

/* VGA status bits */
#define DISPLAY_ENABLE 0x01
#define VRETRACE 0x08

/* Attribute controller registers */
#define PEL_PANNING 0x13

/* Sequence controller registers */
#define MAP_MASK 0x02
#define ALL_PLANES 0xFF02
#define MEMORY_MODE 0x04

/* CRT controller registers */
#define HIGH_ADDRESS 0x0C
#define LOW_ADDRESS 0x0D
#define LINE_OFFSET 0x13
#define UNDERLINE_LOCATION 0x14
#define MODE_CONTROL 0x17

class VgaDisplayAdapter : public DisplayAdapter
{
private:
    void wait_vsync();
public:
    int enable_vsync;
    VgaDisplayAdapter();
    surface_rect get_surface_dimensions();
    void set_palette(palette_24bpp &pal);
    void scroll(rect area, Vector2d vec);
    void begin_frame();
    void end_frame();
};

#endif
