#include "queue.h"

queue::queue( int max )
{
    maxQueue = max + 1;
    front = maxQueue - 1;
    rear = maxQueue - 1;
    items = new  int [maxQueue];
}

queue::~queue()
{
    delete [] items;
}

void queue::makeEmpty()
{
    front = maxQueue - 1;
    rear = maxQueue - 1;
}

bool queue::isEmpty()const
{
    return (rear == front );
}

bool queue::isFull()const
{
    return( (rear + 1 ) % maxQueue == front );
}

void queue::Enqueue( int newItem )
{
    rear = (rear + 1) % maxQueue;
    items[rear] = newItem;
}

void queue::Dequeue( int &item )
{
    front = (front+1) % maxQueue;
    item = items[front];
}
