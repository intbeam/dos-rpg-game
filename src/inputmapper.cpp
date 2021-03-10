#include "inputmapper.hpp"

InputMapper::InputMapper(InputDeviceReader &reader) : device_reader(reader)
{

}

void InputMapper::map(input_data* input, int input_size, mapped_input_data* output, int output_size)
{
    int i;

    for(i = 0; i < input_size; i++)
    {
        output[i] = map(input[i]);
    }
}

int InputMapper::read(mapped_input_data *buffer, int maxlen)
{
    int numread;
    mapped_input_data inbuf[10];
    numread = this->device_reader.read(inbuf, 10);

    map(inbuf, numread, buffer, maxlen);

    return numread;
}

mapped_input_data PassthroughInputMapper::map(input_data input)
{
    return input;
}

PassthroughInputMapper::PassthroughInputMapper(InputDeviceReader &reader) : InputMapper(reader)
{

}