#include "tilemanager.hpp"

void TileManager::generate_tiles(int numtiles)
{
    int i;
    int size = tile_width * tile_height * numtiles;
    int sq = tile_width * tile_height;
    char *ptr;
    this->tile_data = new char[size];


    ptr = this->tile_data;

    for(i = 0; i < size; i++)
    {
        *ptr = (i / sq) + 59 + rand() % 3;
        ptr++;
    }

}

TileManager::TileManager(Rasterizer *rasterizer, int tile_width, int tile_height) : rasterizer(rasterizer), tile_width(tile_width), tile_height(tile_height), tile_data(0)
{
}

TileManager::~TileManager()
{
    delete this->tile_data;
}


void TileManager::draw_tile(int tileindex, rect source_rect, int destination_x, int destination_y)
{
    if(this->tile_data == 0)
    {
        throw "tile data is null";
    }
    if(source_rect.size.x <= 0 || source_rect.size.y <= 0)
        return;

    char *startptr = this->tile_data + (this->tile_width * this->tile_height * tileindex);

    rasterizer->copy_bits(startptr, tile_width, source_rect, destination_x, destination_y);
}