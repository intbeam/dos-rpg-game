#include "tgaimagereader.hpp"

#include <stdio.h>
#include <string.h>

Sprite *TgaImageReader::load_sprite(SpriteManager &manager, char *filename, int &sprites_loaded)
{
    FILE *fp;
    tga_footer footer;
    tga_header header;
    pixel_packet *current_packet;
    Sprite *sprite;
    char pixelbuffer[128];
    long maxpixels;
    long totalpixels;
    char numpixels;
    char pixelcolor;
    int nlength = 0;

    char rle_packetheader;


    fp = fopen(filename, "rb");

    if(fp == 0)
    {
        printf("Unable to open file %s", filename);
        return 0;
    }

    fseek(fp, -((long)sizeof(tga_footer)), SEEK_END);

    fread(&footer, sizeof(tga_footer), 1, fp);

    if(strcmp(footer.signature, TGA_SIGNATURE) != 0)
    {
        fclose(fp);
        printf("Signature mismatch");
        return 0;
    }
    
    fseek(fp, 0L, SEEK_SET);

    fread(&header, sizeof(tga_header), 1, fp);    

    fseek(fp, header.color_map_length * (header.color_map_bpp / 8), SEEK_CUR);

    sprite = manager.create_sprite();

    sprite->width = header.image_width;
    sprite->height = header.image_height;    

    maxpixels = sprite->width * sprite->height;
    totalpixels = 0L;

    while(totalpixels < maxpixels)
    {
        fread(&rle_packetheader, sizeof(char), 1, fp);

        if(0x80 & rle_packetheader)
        {
            numpixels = (0x80 ^ rle_packetheader);
        }
        else
        {
            numpixels = rle_packetheader;
        }

        numpixels++;

        if(0x80 & rle_packetheader)
        {
            fread(&pixelcolor, sizeof(char), 1, fp);            
            current_packet = manager.alloc_pixel_packet(numpixels, pixelcolor, 0, pixelcolor > 0 ? PACKET_SINGLE_COLOR : PACKET_SKIP, sprite->packet_count);
        }
        else
        {
            fread(pixelbuffer, sizeof(char), numpixels, fp);
            current_packet = manager.alloc_pixel_packet(numpixels, 0, pixelbuffer, PACKET_SOURCE_COPY, sprite->packet_count);
        }        

        if(nlength >= sprite->width)
        {
            nlength = 0;
            current_packet = manager.alloc_pixel_packet(0, 0, 0, PACKET_NEXT_LINE, sprite->packet_count);
        }

        

        nlength += numpixels;

        totalpixels += numpixels;

    }

    fclose(fp);

    sprites_loaded = 1;

    return sprite;
    

}

void TgaImageReader::load_palette(char *filename, palette_24bpp &pal)
{
    FILE *fp;
    tga_footer footer;
    tga_header header;

        fp = fopen(filename, "rb");

    if(fp == 0)
    {
        printf("Unable to open file %s", filename);
        return;
    }

    fseek(fp, -((long)sizeof(tga_footer)), SEEK_END);

    fread(&footer, sizeof(tga_footer), 1, fp);

    if(strcmp(footer.signature, TGA_SIGNATURE) != 0)
    {
        fclose(fp);
        printf("Signature mismatch");
        return;
    }
    
    fseek(fp, 0L, SEEK_SET);

    fread(&header, sizeof(tga_header), 1, fp);

    pal.count = header.color_map_length;
    fread(pal.data, header.color_map_bpp / 8, header.color_map_length, fp);


    fclose(fp);
}