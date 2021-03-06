#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Stack.h"
#include <stdlib.h>
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template class Stack<uint>;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
Stack<T>::Stack(uint _size) : buffer(0), size(_size), numElements(0U)
{
    buffer = (T *)malloc(sizeof(T) * _size);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
Stack<T>::~Stack()
{
    free(buffer);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void Stack<T>::Push(T elem)
{
    if(numElements < size)
    {
        buffer[numElements] = elem;
        numElements++;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
T Stack<T>::Pop()
{
    if(numElements != 0)
    {
        numElements--;
        return buffer[numElements];
    }

    return (T)0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
uint Stack<T>::Size() const
{
    return numElements;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
bool Stack<T>::Empty() const
{
    return Size() == 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
int Stack<T>::NumFirstZeros() const
{
    int result = 0;

    for(uint i = 0; i < size; i++)
    {
        if(buffer[i] != 0)
        {
            break;
        }
        result++;
    }

    return result;
}
