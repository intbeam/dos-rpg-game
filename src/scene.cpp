#include "scene.hpp"

Scene::Scene(TileManager *tile_manager, Map *map, SpriteManager *sprite_manager) : tile_manager(tile_manager), map(map), sprite_manager(sprite_manager)
{

}

void Scene::draw_tiles(Quadrant *quadrant, int destination_x, int destination_y)
{
    int tw = this->viewport.view_coords.size.x / tile_manager->tile_width;
    int th = this->viewport.view_coords.size.y / tile_manager->tile_height;

    int twm = this->viewport.view_coords.size.x % tile_manager->tile_width;
    int thm = this->viewport.view_coords.size.y % tile_manager->tile_height;

    int xdata = this->viewport.view_coords.location.x / tile_manager->tile_width;
    int ydata = this->viewport.view_coords.location.y / tile_manager->tile_height;

    int xoffset = this->viewport.view_coords.location.x % tile_manager->tile_width;
    int yoffset = this->viewport.view_coords.location.y % tile_manager->tile_height;

    Vector2d size = Vector2d(tile_manager->tile_width, tile_manager->tile_height);
    //Vector2d tilesourcepos = Vector2d(0,0);

    absrect tilesource_rect = {0, 0, tile_manager->tile_width, tile_manager->tile_height};
    int tindex = 3;

    for(int y = 0; y <= th; y++)
    {


        for(int x = 0; x <= tw; x++)
        {
            MapElement *mapdata = quadrant->get_element_at(xdata + x, ydata + y);

            
            Vector2d pos = Vector2d(
                x * tile_manager->tile_width - xoffset, 
                y * tile_manager->tile_height - yoffset
            );

            if(x == 0)
            {
                tilesource_rect.left = xoffset;
                pos.x += xoffset;
                tindex = 2;
            }
            else if(x == tw)
            {
                tilesource_rect.right = xoffset + twm;
                tilesource_rect.left = xoffset - twm;
                pos.x += xoffset;
                tindex = 1;
            }
            else
            {
                tilesource_rect.left = 0;
                tilesource_rect.right = tile_manager->tile_height;
                tindex = 0;
            }


            tile_manager->draw_tile(
                tindex, 
                    rect::from_absolute(tilesource_rect),
                    pos.x + destination_x,
                    pos.y + destination_y
                );

        }
    }
}