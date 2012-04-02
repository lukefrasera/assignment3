#include <iostream>

using namespace std;

template<class ItemType>
class NodeType{
   ItemType info;
   NodeType<ItemType>* next;
};


