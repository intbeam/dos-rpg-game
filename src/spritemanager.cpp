#include "spritemanager.hpp"

SpriteManager::SpriteManager() : max_sprites(10), max_packets(100), max_pixel_data(4096)
{
    this->sprite_store = (Sprite *)malloc(sizeof(Sprite) * max_sprites);
    this->packet_store = (pixel_packet *)malloc(sizeof(pixel_packet) * max_packets);
    this->pixel_data = (char *)malloc(sizeof(char) * max_pixel_data);

    this->sprite_store_current = this->sprite_store;
    this->packet_store_current = this->packet_store;
    this->pixel_data_current = this->pixel_data;

}

void *SpriteManager::alloc_pixel_data(int count)
{
    void *ret = this->pixel_data;
    this->pixel_data += count;
    return ret;
}

void SpriteManager::dispose()
{
    std::free(this->sprite_store);
    std::free(this->packet_store);
    std::free(this->pixel_data);
}

SpriteManager::~SpriteManager()
{
    this->dispose();
}

Sprite *SpriteManager::create_sprite()
{
    Sprite *spr = this->sprite_store_current++;

    spr->width = 0;
    spr->height = 0;
    spr->packet_count = 0;
    spr->pixelpackets = this->packet_store_current;

    return spr;

}

pixel_packet *SpriteManager::alloc_pixel_packet(int count, int value, const void *data, int type, int &pixel_packet_count)
{
    pixel_packet *cur = this->packet_store_current++;

    cur->count = count;
    cur->value = value;
    cur->data = (void *)data;
    cur->type = type;

    if(data != 0)
    {
        cur->data = alloc_pixel_data(count);
        memcpy(cur->data, data, count);
    }

    pixel_packet_count++;

    return cur;
}