#include <iostream>

using namespace std;

class stack{
  public:
    stack( int );
    ~stack();
    void makeEmpty();
    bool isEmpty()const;
    bool isFull()const;
    void Push( int );
    void Pop( int & );
  private:
    int top, maxStack, *items;
};
