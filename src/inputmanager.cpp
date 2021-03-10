#include "inputmanager.hpp"

int key_state::is_held()
{
    return (this->state & VKEY_STATE_HELD) == VKEY_STATE_HELD;
}

int key_state::is_pressed()
{
    return (this->state & VKEY_STATE_PRESSED) == VKEY_STATE_PRESSED;
}

int key_state::is_released()
{
    return (this->state & (VKEY_STATE_RELEASED | VKEY_STATE_HELD)) == (VKEY_STATE_RELEASED | VKEY_STATE_HELD);
}

InputManager::InputManager() : state_map_size(256)
{
    memset(state_map, 0, sizeof(key_state) * this->state_map_size);
}

void InputManager::add_mapper(InputMapper &mapper)
{
    this->mappers.push_back(&mapper);
}

key_state InputManager::get_state(int virtual_key)
{
    return this->state_map[virtual_key];
}

void InputManager::update()
{
    mapped_input_data buffer[10];
    key_state *ks;
    int numkeys = 0;
    int i;
    int vkey;
    InputMapper *mapper;
    int mods;
    
    for(i = 0; i < this->state_map_size; i++)
    {
        ks = &this->state_map[i];

        if(ks->state == 0)
            continue;


        if(ks->is_pressed())
        {            
            ks->state ^= VKEY_STATE_PRESSED;
            ks->state |= VKEY_STATE_HELD;
        }

        if(ks->is_released())
        {
            ks->state ^= (VKEY_STATE_RELEASED | VKEY_STATE_HELD);
        }

    }

    for(i = 0; i < this->mappers.size(); i++)
    {
        mapper = this->mappers[i];

        numkeys = mapper->read(buffer, 10);

        for(i = 0; i < numkeys; i++)
        {
            vkey = buffer[i].code;

            if((buffer[i].modifier & 0x80) != 0x80)
            {
                if(!this->state_map[vkey].is_held())
                {                    
                    this->state_map[vkey].state |= VKEY_STATE_PRESSED;
                }
            }
            else
            {
                if(this->state_map[vkey].is_held())
                {                    
                    this->state_map[vkey].state |= VKEY_STATE_RELEASED;
                }
            }
        }        
    }
}
