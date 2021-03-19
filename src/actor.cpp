#include "actor.hpp"

MapActor::MapActor(Vector2d location) : location(location)
{
    this->direction.x = 0;
    this->direction.y = 0;
}

void MapActor::update(TileManager *tilemanager, int diff)
{
    if(this->direction.x != 0 || this->direction.y != 0)
    {        
        Vector2d size = this->get_draw_size();
        rect irect = { this->location.x, this->location.y, this->location.x + size.x, this->location.y + size.y };
        tilemanager->invalidate(irect);
        this->location.x += this->direction.x;
        this->location.y += this->direction.y;
    }
}

void MapActor::add_direction(Vector2d vec)
{
    this->direction.x += vec.x;
    this->direction.y += vec.y;
}


void Player::update(TileManager *tilemanager, int diff)
{
    MapActor::update(tilemanager, diff);
}

Player::Player(Vector2d loc, Sprite *sprite) : MapActor(loc), sprite(sprite)
{

}

void Player::draw(Rasterizer *rasterizer, Viewport &viewport)
{
    rasterizer->draw_sprite(this->sprite, this->location.x - viewport.view_coords.left, this->location.y - viewport.view_coords.top);    
}

Vector2d Player::get_draw_size()
{
    return Vector2d(16, 16);
    
}