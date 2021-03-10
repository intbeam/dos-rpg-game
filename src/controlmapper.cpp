#include "controlmapper.hpp"

ControlMapper::ControlMapper()
{
    this->vkey_map[Player_Move_West] = 0x1e;
    this->vkey_map[Player_Move_East] = 0x20;
    this->vkey_map[Player_Move_North] = 0x11;
    this->vkey_map[Player_Move_South] = 0x1f;
}

int ControlMapper::map_virtual_key(ControlAction action)
{
    return this->vkey_map[(int)action];
}