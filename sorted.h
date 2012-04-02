#include <iostream>
#include "nodetype.h"
#ifndef SORT_H
#define SORT_H

using namespace std;

template <ItemType>
class SortedType{
   public:
   void MakeEmpty();
   bool isFull() const;
   int lengthIs() const;
   void RetrieveItem( ItemType &, bool &);
   void InsertItem( ItemType );
   void DeleteItem( ItemType);
   void ResetList();
   bool isLastItem();
   void getNextItem( ItemType& )
   
   private:
   int length;
   NodeType<ItemType> *listData;
   NodeType<ItemType>* currentPos;
};

#endif
