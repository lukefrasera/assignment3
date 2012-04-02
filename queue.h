#include <iostream>

using namespace std;

class queue{
  public:
    queue(int);
    ~queue();
    void makeEmpty();
    bool isEmpty()const;
    bool isFull()const;
    void Enqueue( int );
    void Dequeue( int & );
    
  private:
    int front, rear, *items, maxQueue;
    
};
