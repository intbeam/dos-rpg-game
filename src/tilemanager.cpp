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
        *ptr = (i / sq);
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

void TileManager::invalidate(rect invalidate_rect)
{
    this->invalidate_rects.push_back(invalidate_rect);
}

void TileManager::repaint(Quadrant *quadrant, Viewport view, int destination_x, int destination_y)
{
    rect *start;
    for(start = this->invalidate_rects.begin(); start < this->invalidate_rects.end(); start++)
    {
        rect redrawcoords = { 
            start->left, 
            start->top, 
            start->right, 
            start->bottom 
        };
        this->draw_tiles(quadrant, redrawcoords, start->left - view.view_coords.left, start->top - view.view_coords.top);
    }

    this->invalidate_rects.clear();
}

void TileManager::draw_tiles(Quadrant *quadrant, rect coords, int destination_x, int destination_y)
{
    int qx = coords.left / this->tile_width;
    int qxoffset = coords.left % this->tile_width;
    int qy = coords.top / this->tile_height;
    int qyoffset = coords.top % this->tile_height;

    int qw = (coords.right - coords.left) / this->tile_width;
    int qh = (coords.bottom - coords.top) / this->tile_height;
    
    if(qw == 0)
        qw = 1;

    if(qh == 0)
        qh = 1;
    

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
            tilecoords.bottom = qyoffset;
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
                tilecoords.right = qxoffset;
            }
            else
            {
                tilecoords.right = this->tile_width;
            }

            this->draw_tile(elementptr->get_tile_index(), tilecoords, destination_x + qxc - qxoffset + tilecoords.left, destination_y + qyc - qyoffset + tilecoords.top);

            elementptr++;

            qxc += this->tile_width;

        }

        qyc += this->tile_height;
    }

}