#include "rect.hpp"

rect::rect(Vector2d location, Vector2d size) : location(location), size(size)
{

}

rect rect::from_absolute(absrect arect)
{
    int width = arect.right - arect.left;
    int height = arect.bottom - arect.top;

    if(width < 0)
        width = 0;

    if(height < 0)
        height = 0;
    

    return rect(Vector2d(arect.left, arect.top), Vector2d(width, height));
}