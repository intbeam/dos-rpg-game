#ifndef KEYBOARDDEVICEREADER_HPP
#define KEYBOARDDEVICEREADER_HPP

#include <conio.h>
#include <stdio.h>
#include "inputdevicereader.hpp"

class KeyboardDeviceReader : public InputDeviceReader
{
public:
    int get_device_type();
    int read(input_data *buf, int maxlength);
};

#endif