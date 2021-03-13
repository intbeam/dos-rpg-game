#ifndef TILEMANAGER_HPP
#define TILEMANAGER_HPP

#include <malloc.h>
#include <mem.h>
#include <stdlib.h>
#include <stdio.h>
#include "displaymeta.hpp"
#include "rasterizer.hpp"

class TileManager
{

public:
    char *tile_data;

    int tile_width;
    int tile_height;
    
    Rasterizer *rasterizer;

    TileManager(Rasterizer *rasterizer, int tile_width, int tile_height);
    ~TileManager();
    void draw_tile(int tileindex, rect source_rect, int destination_x, int destination_y);
    void generate_tiles(int numtiles);
};


#endif