#include "rect.hpp"

rect::rect(Vector2d location, Vector2d size) : location(location), size(size)
{

}

Vector2d absrect::get_size()
{
    return Vector2d(this->right - this->left, this->bottom - this->top);
}

rect rect::from_absolute(absrect arect)
{
    int width = arect.right - arect.left;
    int height = arect.bottom - arect.top;    

    return rect(Vector2d(arect.left, arect.top), Vector2d(width, height));
}