#ifndef INPUTDEVICEREADER_HPP
#define INPUTDEVICEREADER_HPP

typedef struct input_data
{
    char code;
    char modifier;
} input_data, mapped_input_data;

class InputDeviceReader
{
public:
    virtual int get_device_type() = 0;
    virtual int read(input_data *buf, int maxlength) = 0;
};

#endif