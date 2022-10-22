#include "keyboarddevicereader.hpp"

int KeyboardDeviceReader::get_device_type()
{
    return 1;
}


int KeyboardDeviceReader::read(input_data *buf, int maxlength)
{
    char scancode;

    __asm
    {
        in al, 60h
        mov scancode, al
        in al, 61h
        or al, 128
        out 61h, al
        xor al, 128
        out 61h, al
    }

    *(char*)(0x0040001A) = 0x20;
    *(char*)(0x0040001C) = 0x20;

    if(scancode == 0)
        return 0;

    if((scancode & 0x80) == 0x80)
    {
        buf[0].code = scancode ^ 0x80;    
    }
    else
    {
        buf[0].code = scancode;
    }
    
    buf[0].modifier = scancode & 0x80;
    
    return 1;
}