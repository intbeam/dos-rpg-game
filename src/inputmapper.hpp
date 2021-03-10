#ifndef INPUTMAPPER_HPP
#define INPUTMAPPER_HPP

#include "memory.h"
#include "inputdevicereader.hpp"

class InputMapper
{
protected:
    InputDeviceReader &device_reader;
    virtual input_data map(input_data input) = 0;
    virtual void map(input_data* input, int input_size, mapped_input_data* output, int output_size);
public:
    InputMapper(InputDeviceReader &reader);
    int read(mapped_input_data *buffer, int maxlen);
};

class PassthroughInputMapper : public InputMapper
{
protected:
    mapped_input_data map(input_data input);
public:
    PassthroughInputMapper(InputDeviceReader &reader);
};

#endif