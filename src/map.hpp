#ifndef MAP_HPP
#define MAP_HPP

#include <stdlib.h>
#include <stdio.h>

class MapElement
{
private:
    char data;
public:
    int get_tile_index();
    int is_passable();
    void set_data(char data);
};

class Quadrant
{
private:
    MapElement *map_data;
public:
    Quadrant();
    Quadrant(int width, int height);
    MapElement *get_element_at(int x, int y);
    void set_data(MapElement *map_data);
    int width;
    int height;
};

class MapLoader
{
public:
    virtual void load(int x, int y, Quadrant *quadrant) = 0;
};

class Map
{
private:
    int map_width;
    int map_height;
    int quadrant_width;
    int quadrant_height;
    Quadrant *quadrants;
    MapLoader *map_loader;
public:
    Map(int width, int height, int qwidth, int qheight, MapLoader *map_loader);
    Quadrant *get_quadrant(int x, int y);
    Quadrant *load_quadrant(int x, int y);
    void free_quadrant(int x, int y);
};

class RandomMapLoader : public MapLoader
{
    void load(int x, int y, Quadrant *quadrant);
};

#endif