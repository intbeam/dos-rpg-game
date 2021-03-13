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
    rect source_rect;

    Sprite *sprite;
    int sprites_loaded;

    reader.load_palette("char.tga", pal);

    display_adapter.set_palette(pal);

    tilemanager->generate_tiles(5);

    sprite = reader.load_sprite(manager, "char.tga", sprites_loaded);

    source_rect.left = 0;
    source_rect.top = 0;
    source_rect.right = 20;
    source_rect.bottom = 20;

    int *map = new int[16 * 10];


    for(i = 0; i < 16; i++)
    {
        for(j = 0; j < 10; j++)
        {
            map[c] = rand() % 5;

            tilemanager->draw_tile(map[c], source_rect, i * 20, j * 20);
            c++;
        }
    }


    while(true)
    {        
        //chars_read = inputmapper.read(mapped, 5);
        

        input_manager.update();        


        display_adapter.begin_frame();

        if(input_manager.get_state(default_map.map_virtual_key(Player_Move_West)).is_held())
        {
            x--;            
        }

        if(input_manager.get_state(default_map.map_virtual_key(Player_Move_East)).is_held())
        {
            x++;
        }

        if(input_manager.get_state(default_map.map_virtual_key(Player_Move_North)).is_held())
        {
            y--;
        }

        if(input_manager.get_state(default_map.map_virtual_key(Player_Move_South)).is_held())
        {
            y++;
        }
        
        

        rasterizer->draw_sprite(*sprite, 250 + x, 50 + y);
        
        display_adapter.end_frame();


    }

    delete rasterizer;

    getchar();
    
    return 0;
}
