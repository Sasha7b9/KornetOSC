#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Log
{
public:
    static void Message(char *format, ...);
private:
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LOG_WRITE(...)       Log::Message(__VA_ARGS__)
#define LOG_ERROR_TRACE(...) Log::Message(__VA_ARGS__)
