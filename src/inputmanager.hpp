#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include "inputmapper.hpp"
#include <stdio.h>
#include <vector>

struct key_state
{    
    char state;
public:
    int is_pressed();
    int is_held();
    int is_released();
};

#define VKEY_STATE_PRESSED      1
#define VKEY_STATE_HELD         2
#define VKEY_STATE_RELEASED     4


class InputManager
{
private:
    std::vector<InputMapper*> mappers;    
    key_state state_map[256];
    int state_map_size;
public:
    InputManager();
    void add_mapper(InputMapper &input_mapper);
    key_state get_state(int virtual_key);
    void update();
};

#endif