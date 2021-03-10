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
    
    input_data input[5];
    mapped_input_data mapped[5];
    int chars_read = 0;
    PassthroughInputMapper inputmapper = PassthroughInputMapper(keyb);    
    InputManager input_manager;
    ControlMapper default_map;


    input_manager.add_mapper(inputmapper);


    int x = 50, y = 50;


    palette_24bpp pal;
    SpriteManager manager;
    TgaImageReader reader;
    Rasterizer rasterizer;
    Sprite *sprite;
    int sprites_loaded;

    reader.load_palette("char.tga", pal);

    display_adapter.set_palette(pal);

    sprite = reader.load_sprite(manager, "char.tga", sprites_loaded);

    while(true)
    {        
        //chars_read = inputmapper.read(mapped, 5);

        input_manager.update();


        display_adapter.begin_frame();

        rasterizer.draw_rectangle(pixel_writer, 250 + x, 50 + y, 16, 16, 0);

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
        

        rasterizer.draw_sprite(pixel_writer, *sprite, 250 + x, 50 + y);
        
        display_adapter.end_frame();


    }

    getchar();
    
    return 0;
}
