#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Object
{
public:
    void SendMessage(char *object, uint message);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define OSC_OBJECT( object )            \
    class object : public Object