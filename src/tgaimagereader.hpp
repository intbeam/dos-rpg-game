#ifndef TGAIMAGEREADER_HPP
#define TGAIMAGEREADER_HPP

#include "spritemanager.hpp"

#define TGA_SIGNATURE "TRUEVISION-XFILE.\0"




#pragma pack(1)
typedef struct tga_header
{
    char image_id;
    char color_map_type;
    char image_type;

    unsigned short color_map_first_index;
    unsigned short color_map_length;

    char color_map_bpp;

    unsigned short origin_x;
    unsigned short origin_y;

    unsigned short image_width;
    unsigned short image_height;

    char image_bpp;
    char image_descriptor;


} tga_header;

typedef struct tga_footer
{
    unsigned long extension_offset;
    unsigned long developer_offset;
    char signature[18];
} tga_footer;
#pragma pack(0)

class TgaImageReader
{    
public:
    Sprite *load_sprite(SpriteManager &manager, char *filename, int &sprites_loaded);
    void load_palette(char *filename, palette_24bpp &palette);
};

#endif
