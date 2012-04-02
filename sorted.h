#include <iostream>
#include "nodetype.h"
#ifndef SORT_H
#define SORT_H

using namespace std;

template <class ItemType>
class SortedType{
   public:
   SortedType();
   ~SortedType();
   void MakeEmpty();
   bool IsFull() const;
   int LengthIs() const;
   void RetrieveItem( ItemType &, bool &);
   void InsertItem( ItemType );
   void DeleteItem( ItemType);
   void ResetList();
   bool IsLastItem() const;
   void GetNextItem( ItemType& );
   
   private:
   int length;
   NodeType<ItemType> *listData;
   NodeType<ItemType>* currentPos;
};

#endif
