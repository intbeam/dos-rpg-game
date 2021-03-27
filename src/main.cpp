/* Copyright 2021 Intbeam

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "main.hpp"

// Game entrypoint
int main(int argc, char** argv)
{
    VgaDisplayAdapter display_adapter;    
    VgaPixelWriter pixel_writer = VgaPixelWriter(display_adapter.get_surface_dimensions());    
    
    KeyboardDeviceReader keyb;

    PassthroughInputMapper inputmapper = PassthroughInputMapper(keyb);    
    InputManager input_manager;
    ControlMapper default_map;

    input_manager.add_mapper(inputmapper);

    int x = 50, y = 50;
    int i, j, c;


    palette_24bpp pal;
    SpriteManager manager;
    TgaImageReader reader;

    Rasterizer *rasterizer = new PixelRasterizer(pixel_writer);
    TileManager *tilemanager = new TileManager(rasterizer, 20, 20);
    
    MapLoader *mloader = new RandomMapLoader();
    Map *themap;    
    Quadrant *cq;

    int update = 0;
    
    Vector2d playerpos = Vector2d(20, 20);
    


    Sprite *sprite;
    

    int sprites_loaded;

    reader.load_palette("char.tga", pal);

    display_adapter.set_palette(pal);

    tilemanager->generate_tiles(10);

    Scene scene = Scene(tilemanager, themap, &manager);

    scene.viewport.view_coords.size = Vector2d(44, 26);

    themap = new Map(1, 1, 32, 32, mloader);

    cq = themap->load_quadrant(0, 0);


    sprite = reader.load_sprite(manager, "char.tga", sprites_loaded); 

    Player player(playerpos, sprite);        

    int tileindex = 0;

    while(true)
    {        
        input_manager.update();
        
        player.update(tilemanager, 0);

        display_adapter.begin_frame();

if(input_manager.get_state(default_map.map_virtual_key(Player_Move_East)).is_held())
        {
            scene.viewport.view_coords.location.x++;
            update = 1;
        }

        if(input_manager.get_state(default_map.map_virtual_key(Player_Move_West)).is_held())
        {
            if(scene.viewport.view_coords.location.x > 0)
            {
                scene.viewport.view_coords.location.x--;
                update = 1;
            }
        }


        if(input_manager.get_state(default_map.map_virtual_key(Player_Move_South)).is_held())
        {
            scene.viewport.view_coords.location.y++;
            update = 1;
        }

        if(input_manager.get_state(default_map.map_virtual_key(Player_Move_North)).is_held())
        {
            if(scene.viewport.view_coords.location.y > 0)
            {
                scene.viewport.view_coords.location.y--;
                update = 1;
            }
        }

        if(update)
        {
            rasterizer->draw_rectangle(
                50,
                50, 
                scene.viewport.view_coords.size.x, 
                scene.viewport.view_coords.size.y, 30);

            scene.draw_tiles(cq, 50, 50);

            update = 0;
        }

        //rect tilerect = rect(Vector2d(0,0), Vector2d(tilemanager->tile_width, tilemanager->tile_height));

        //tilemanager->draw_tile(tileindex % 10, tilerect, 50, 50 );

        
        
        
        display_adapter.end_frame();

    }

    delete rasterizer;

    getchar();
    
    return 0;
}
