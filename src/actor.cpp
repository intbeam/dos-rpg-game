#include "actor.hpp"

MapActor::MapActor(Vector2d location) : location(location)
{
    this->direction.x = 0;
    this->direction.y = 0;
}

void MapActor::update(Scene *scene, int diff)
{
    if(this->direction.x != 0 || this->direction.y != 0)
    {        
        Vector2d size = this->get_draw_size();
        rect irect = rect(this->location, size);
        //tilemanager->invalidate(irect);
        this->location.x += this->direction.x;
        this->location.y += this->direction.y;
    }
}

void MapActor::add_direction(Vector2d vec)
{
    this->direction.x += vec.x;
    this->direction.y += vec.y;
}


void Player::update(Scene *scene, int diff)
{
    MapActor::update(scene, diff);
}

Player::Player(Vector2d loc, Sprite *sprite) : MapActor(loc), sprite(sprite)
{

}

void Player::draw(Rasterizer *rasterizer, Viewport &viewport)
{
    rasterizer->draw_sprite(this->sprite, this->location.x - viewport.view_coords.location.x, this->location.y - viewport.view_coords.location.y);    
}

Vector2d Player::get_draw_size()
{
    return Vector2d(16, 16);
    
}