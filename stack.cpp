#include "stack.h"

stack::stack( int size )
{
    top = -1;
    maxStack = size;
    items = new int[maxStack];
}

stack::~stack()
{
    delete [] items;
}

void stack::makeEmpty()
{
    top = -1;
}

bool stack::isEmpty()const
{
    return (top == -1 );
}

bool stack::isFull()const
{
    return (top == maxStack - 1);
}

void stack::Push( int newItem )
{
    top++;
    items[top] = newItem;
}

void stack::Pop( int &item )
{
    item = items[top];
    top--;
}


