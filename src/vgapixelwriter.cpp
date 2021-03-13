#include "vgapixelwriter.hpp"

VgaPixelWriter::VgaPixelWriter(surface_rect dimensions) : PixelWriter(dimensions)
{

}

void VgaPixelWriter::copy_line(int x_origin, int y_origin, void *source, int numpixels)
{
    int vga_index = y_origin * this->dimensions.width + x_origin;
    
    __asm
    {
        mov ax, 0a000h
        mov es, ax              // Exta Segment set to VGA segment (0xA000)
        mov ax, vga_index
        mov di, ax              // Destination Index set to vga_index (initially sprite location)

        mov cx, numpixels
        mov ax, source
        mov si, ax

        rep movsb       // stores the memory at DS:SI+CX in ES:DI, CX number of times
    }


}


void VgaPixelWriter::write_pixeldata(int x_origin, int y_origin, const pixel_packet *operations, int packet_count)
{
    pixel_packet *packetsptr;
    int current_op;
    int pixels_written;
    int vga_index;    
    int line_pixels = 0;    

    packetsptr = (pixel_packet *)operations;    

    vga_index = y_origin * this->dimensions.width + x_origin;

    for(current_op = 0; current_op < packet_count; current_op++)
    {           
        switch(packetsptr->type)
        {
            case PACKET_SINGLE_COLOR:
                pixels_written = packetsptr->count;

                __asm {

                    mov ax, 0a000h
                    mov es, ax              // Exta Segment set to VGA segment (0xA000)
                    mov ax, vga_index
                    mov di, ax              // Destination Index set to vga_index (initially sprite location)

                    mov ax, packetsptr
                    mov si, ax

                    mov cx, [ds:si]
                    mov ax, [ds:si + 2]

                    rep stosb       // stores AX in ES:DI, CX number of times
                }
            break;
            case PACKET_SOURCE_COPY:
                pixels_written = packetsptr->count;
                __asm {

                    mov ax, 0a000h
                    mov es, ax              // Exta Segment set to VGA segment (0xA000)
                    mov ax, vga_index
                    mov di, ax              // Destination Index set to vga_index (initially sprite location)

                    mov ax, packetsptr
                    mov si, ax

                    mov cx, [ds:si]
                    mov ax, [ds:si + 4]                    
                    mov si, ax

                    rep movsb       // stores the memory at DS:SI+CX in ES:DI, CX number of times
                }
            break;
            case PACKET_SKIP: 
                pixels_written = packetsptr->count;
            break;
            case PACKET_NEXT_LINE:
                pixels_written = dimensions.width - line_length;                
            break;
        }        
        vga_index += pixels_written;
        packetsptr++;
    }

}

