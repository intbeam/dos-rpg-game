#include "tilemanager.hpp"

void TileManager::generate_tiles(int numtiles)
{
    int i;
    int size = tile_width * tile_height * numtiles;
    char *ptr;
    this->tile_data = new char[size];


    ptr = this->tile_data;

    for(i = 0; i < size; i++)
    {
        *ptr = 26 + (i % 12);
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

    char *startptr = this->tile_data + (this->tile_width * this->tile_height * tileindex);

    rasterizer->copy_bits(startptr, tile_width, source_rect, destination_x, destination_y);

}

void TileManager::draw_tiles(Quadrant *quadrant, rect coords, int destination_x, int destination_y)
{
    int qx = coords.left / this->tile_width;
    int qxoffset = coords.left % this->tile_width;
    int qy = coords.top / this->tile_height;
    int qyoffset = coords.top % this->tile_height;

    int qw = (coords.right - coords.left) / this->tile_width;
    int qww = (coords.right - coords.left) % this->tile_width;
    int qh = (coords.bottom - coords.top) / this->tile_height;
    int qhh = (coords.bottom - coords.top) % this->tile_height;

    
        qh+=1;
    
    
        qw+=1;
    
    int qxc = 0;
    int qyc = 0;
    MapElement *elementptr;
    
    rect tilecoords = { 0, 0, 0, 0};

    for(int y = 0; y <= qh; y++)
    {        
        if(y == 0)
        {
            tilecoords.top = qyoffset;
        }
        else
        {
            tilecoords.top = 0;
        }

        if(y == qh)
        {
            tilecoords.bottom = this->tile_height - qhh;
        }
        else
        {
            tilecoords.bottom = this->tile_height;
        }

        elementptr = quadrant->get_element_at(qx, qy + y);
        
        qxc = 0;

        for(int x = 0; x <= qw; x++)
        {            
            if(x == 0)
            {
                tilecoords.left = qxoffset;
            }
            else
            {
                tilecoords.left = 0;
            }

            if(x == qw)
            {
                tilecoords.right = this->tile_width - qww;
            }
            else
            {
                tilecoords.right = this->tile_width;
            }            

            this->draw_tile(elementptr->get_tile_index(), tilecoords, destination_x + qxc - qxoffset + tilecoords.left, destination_y + qyc - qyoffset + tilecoords.top + this->tile_height - tilecoords.bottom);

            elementptr++;

            qxc += this->tile_width;

        }

        qyc += this->tile_height;
    }

}