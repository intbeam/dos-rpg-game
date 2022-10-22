#ifndef SCENE_HPP
#define SCENE_HPP

#include "tilemanager.hpp"
#include "spritemanager.hpp"
#include "map.hpp"

class Scene
{
private:
    TileManager *tile_manager;
    Map *map;
    SpriteManager *sprite_manager;
public:
    Scene(TileManager *tile_manager, Map *map, SpriteManager *sprite_manager);
    Viewport viewport;
    void draw_tiles(Quadrant *quadrant, int destination_x, int destination_y);
    void draw_tiles(Quadrant *quadrant, Viewport &viewport, int destination_x, int destination_y);
};

#endif