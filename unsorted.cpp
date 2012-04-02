#include "unsorted.h"

// CONSTRUCTOR
template<class ItemType>
UnsortedType<ItemType>::UnsortedType()
{
 length = 0;
 listData = NULL;
}

// DESTRUCTOR
template<class ItemType>
UnsortedType<ItemType>::~UnsortedType()
{
 MakeEmpty();
}

// IS FULL 
template<class ItemType>
bool UnsortedType<ItemType>::IsFull() const
{
 NodeType<ItemType>* ptr;
 
 ptr = new NodeType<ItemType>;
 if(ptr == NULL)
   return true;
 else {
   delete ptr; 
   return false;
 }
} 

// LENGTH IS
template<class ItemType>
int UnsortedType<ItemType>::LengthIs() const
{
 return length;
}

// RESET LIST
template<class ItemType>
void UnsortedType<ItemType>::ResetList()
{
 currentPos = listData;
}

//GET NEXT ITEM
template<class ItemType>
void UnsortedType<ItemType>::GetNextItem(ItemType& item)
{
 item = currentPos->info;
 currentPos = currentPos->next;
}

//IS LAST ITEM
template<class ItemType>
bool UnsortedType<ItemType>::IsLastItem() const
{
 return(currentPos == NULL);
} 

// MAKE EMPTY
template<class ItemType>
void UnsortedType<ItemType>::MakeEmpty()
{
 NodeType<ItemType>* tempPtr;
 
 while(listData != NULL) {
   tempPtr = listData;
   listData = listData->next;
   delete tempPtr;
 }
 length=0;
} 

// RETRIEVE ITEM
template<class ItemType>
void UnsortedType<ItemType>::RetrieveItem(ItemType& item, bool& found)
{
 NodeType<ItemType>* location;
 
 location = listData;
 found = false;
 
 while( (location != NULL) && !found) {
 
   if(item == location->info) {
     found = true;
     item = location->info;
   }
   else
     location = location->next;
 }
} 

//INSERT ITEM
template <class ItemType>
void UnsortedType<ItemType>::InsertItem (ItemType newItem)
{ 
 NodeType<ItemType>* location;
 
 location = new NodeType<ItemType>;
 location->info = newItem;
 location->next = listData;
 listData = location;
 length++;
} 

//DELETE ITEM
template <class ItemType>
void UnsortedType<ItemType>::DeleteItem(ItemType item)
{
 NodeType<ItemType>* location = listData;
 NodeType<ItemType>* tempLocation;
 
 if(item == listData->info) {
   tempLocation = listData; // special case
   listData = listData->next;  
 }
 else {
   while(!(item == (location->next)->info))
     location = location->next;
     
   // delete node at location->next
   tempLocation=location->next;
   location->next = tempLocation->next;
 } 
 delete tempLocation;
 length--;
}

// 
 
 
 
 
 
 
 
 
 
 
 
