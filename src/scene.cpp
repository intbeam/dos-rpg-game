#include "scene.hpp"

Scene::Scene(TileManager *tile_manager, Map *map, SpriteManager *sprite_manager) : tile_manager(tile_manager), map(map), sprite_manager(sprite_manager)
{

}

void Scene::draw_tiles(Quadrant *quadrant, int destination_x, int destination_y)
{
    Scene::draw_tiles(quadrant, this->viewport, destination_x, destination_y);
}

void Scene::draw_tiles(Quadrant *quadrant, Viewport &viewport, int destination_x, int destination_y)
{
    int tw = viewport.view_coords.size.x / tile_manager->tile_width;
    int th = viewport.view_coords.size.y / tile_manager->tile_height;

    int twm = viewport.view_coords.size.x % tile_manager->tile_width;
    int thm = viewport.view_coords.size.y % tile_manager->tile_height;

    if(twm > 0)
        tw++;
    
    if(thm > 0)
        th++;

    int xdata = viewport.view_coords.location.x / tile_manager->tile_width;
    int ydata = viewport.view_coords.location.y / tile_manager->tile_height;

    int xoffset = viewport.view_coords.location.x % tile_manager->tile_width;
    int yoffset = viewport.view_coords.location.y % tile_manager->tile_height;

    for(int y = 0; y <= th; y++)
    {
        
        absrect tilesource_rect = {0, 0, tile_manager->tile_width, tile_manager->tile_height};
        
        Vector2d pos = Vector2d(
            0,
            y * tile_manager->tile_height - yoffset
        );

        if(pos.y < 0)
        {
            tilesource_rect.top -= pos.y;
            pos.y = 0;
        }

        int h = tilesource_rect.bottom - tilesource_rect.top;

        if(pos.y + h > viewport.view_coords.size.y)
        {
            tilesource_rect.bottom -= (pos.y + h) - viewport.view_coords.size.y; 
        }

        for(int x = 0; x <= tw; x++)
        {
            MapElement *mapdata = quadrant->get_element_at(xdata + x, ydata + y);

            int tindex = mapdata->get_tile_index();
            
            pos.x = x * tile_manager->tile_width - xoffset;

            tilesource_rect.left = 0;
            tilesource_rect.right = tile_manager->tile_width;

            if(pos.x < 0)
            {
                tilesource_rect.left -= pos.x;
                pos.x = 0;
            }
            
            int w = tilesource_rect.right - tilesource_rect.left;

            if((pos.x + w > viewport.view_coords.size.x))
            {
                tilesource_rect.right -= (pos.x + w) - viewport.view_coords.size.x;             
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