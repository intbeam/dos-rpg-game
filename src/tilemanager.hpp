#ifndef TILEMANAGER_HPP
#define TILEMANAGER_HPP

#include <malloc.h>
#include <mem.h>
#include <vector>
#include "displaymeta.hpp"
#include "rasterizer.hpp"
#include "map.hpp"
#include "viewport.hpp"

class TileManager
{
private:
    std::vector<rect> invalidate_rects;
public:
    char *tile_data;

    int tile_width;
    int tile_height;

    
    Rasterizer *rasterizer;

    TileManager(Rasterizer *rasterizer, int tile_width, int tile_height);
    ~TileManager();
    void draw_tile(int tileindex, rect source_rect, int destination_x, int destination_y);
    void generate_tiles(int numtiles);
    void draw_tiles(Quadrant *quadrant, rect coords, int destination_x, int destination_y);
    void invalidate(rect rect);
    void repaint(Quadrant *quadrant, Viewport view, int destination_x, int destination_y);
};


#endif