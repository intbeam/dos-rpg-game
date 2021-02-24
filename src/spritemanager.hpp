#ifndef SPRITEMANAGER_HPP
#define SPRITEMANAGER_HPP

#include <malloc.h>
#include <mem.h>
#include "pixelwriter.hpp"
#include "imagedata.hpp"


class SpriteManager
{
private:
    char *pixel_data;
    char *pixel_data_current;
    int max_pixel_data;
    pixel_packet *packet_store;
    pixel_packet *packet_store_current;
    int max_packets;
    Sprite *sprite_store;
    Sprite *sprite_store_current;
    int max_sprites;

    void dispose();

public:
    SpriteManager();
    ~SpriteManager();
    pixel_packet *alloc_pixel_packet(int count, int value, const void *data, int type, int &pixel_packet_count);
    void *alloc_pixel_data(int count);
    Sprite *create_sprite();
};

#endif