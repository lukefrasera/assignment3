#include <iostream>
#include "nodetype.h"
#ifndef UNSORT_H
#define UNSORT_H

using namespace std;

template <ItemType>
class UnsortedType{
   public:
   void MakeEmpty();
   bool isFull() const;
   int lengthIs() const;
   void RetrieveItem( ItemType &, bool &);
   void InsertItem( ItemType );
   void DeleteItem( ItemType);
   void ResetList();
   bool isLastItem() const;
   void getNextItem( ItemType& )
   
   private:
   int length;
   NodeType<ItemType> *listData;
   NodeType<ItemType>* currentPos;
};

#endif
