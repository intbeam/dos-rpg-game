#include "map.hpp"

int MapElement::get_tile_index()
{
    return this->data & ~(0x80);
}

int MapElement::is_passable()
{
    return this->data & 0x80;
}

void MapElement::set_data(char data)
{
    this->data = data;
}

Map::Map(int width, int height, int qwidth, int qheight, MapLoader *map_loader) : map_width(width), map_height(height), quadrant_width(qwidth), quadrant_height(qheight), map_loader(map_loader)
{
    this->quadrants = new Quadrant[width * height];
}

Quadrant *Map::get_quadrant(int x, int y)
{
    return &this->quadrants[y * this->map_width + x];
}

Quadrant::Quadrant() : map_data(0)
{
    
}

Quadrant::Quadrant(int width, int height) : width(width), height(height)
{

}

Quadrant *Map::load_quadrant(int x, int y)
{
    Quadrant *res =  this->get_quadrant(x, y);
    this->map_loader->load(x, y, res);
    return res;
}


void Quadrant::set_data(MapElement *map_data)
{
    if(this->map_data != 0)
    {
        printf("map data is not null");
        return;
    }

    this->map_data = map_data;
}

MapElement *Quadrant::get_element_at(int x, int y)
{
    return &this->map_data[y * width + x];
}

void RandomMapLoader::load(int x, int y, Quadrant *quadrant)
{
    quadrant->width = 32;
    quadrant->height = 32;

    int xx, c = quadrant->width * quadrant->height;

    MapElement *data = new MapElement[c];
    MapElement *dptr = data;

    for(xx = 0; xx < c; xx++)
    {
        dptr[xx].set_data(rand() % 5);
    }

    quadrant->set_data(data);
}