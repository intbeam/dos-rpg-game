#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "vector2d.hpp"
#include "spritemanager.hpp"
#include "rasterizer.hpp"
#include "tilemanager.hpp"
#include "rect.hpp"

class Actor
{
public:
};

class MapActor : public Actor
{
private:
public:    
    MapActor(Vector2d loc);
    Vector2d location;
    Vector2d direction;
    void add_direction(Vector2d vec);    
    virtual void draw(Rasterizer *rasterizer, Viewport &viewport) = 0;
    virtual Vector2d get_draw_size() = 0;
    virtual void update(TileManager *tilemanager, int diff);
};

class Player : public MapActor
{
private:
    Sprite *sprite;
public:
    Player(Vector2d loc, Sprite *sprite);
    void draw(Rasterizer *rasterizer, Viewport &viewport);
    void update(TileManager *tilemanager, int diff);
    Vector2d get_draw_size();
};

#endif