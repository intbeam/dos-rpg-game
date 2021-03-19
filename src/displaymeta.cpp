#include "displaymeta.hpp"

rect rect::displace(Vector2d vec)
{
    rect ret = 
    { 
        this->left + vec.x,
        this->top += vec.y,
        this->right += vec.x,
        this->bottom += vec.y
    };
    return  ret;

}