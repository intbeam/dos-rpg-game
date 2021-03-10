#ifndef CONTROLMAPPER_HPP
#define CONTROLMAPPER_HPP

enum ControlAction
{
    Player_Move_West = 1,
    Player_Move_East = 2,
    Player_Move_North = 3,
    Player_Move_South = 4
};

class ControlMapper
{
    int vkey_map[20];
public:
    ControlMapper();
    int map_virtual_key(ControlAction action);
};

#endif