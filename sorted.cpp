#include "sorted.h"

// CONSTRUCTOR
template<class ItemType>
SortedType<ItemType>::SortedType()
{
 length = 0;
 listData = NULL;
 
}

// DESTRUCTOR
template<class ItemType>
SortedType<ItemType>::~SortedType()
{
 MakeEmpty();
}

// IS FULL 
template<class ItemType>
bool SortedType<ItemType>::IsFull() const
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
int SortedType<ItemType>::LengthIs() const
{
 return length;
}
 
// RESET LIST
template<class ItemType>
int SortedType<ItemType>::ResetList()
{
 currentPos = listData;
}

//GET NEXT ITEM
template<class ItemType>
void SortedType<ItemType>::GetNextItem(ItemType& item)
{
 item = currentPos->info;
 currentPos = currentPos->next;
}
 
//IS LAST ITEM
template<class ItemType>
bool SortedType<ItemType>::IsLastItem() const
{
 return(currentPos == NULL);
} 

// MAKE EMPTY
template<class ItemType>
void SortedType<ItemType>::MakeEmpty()
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
void SortedType<ItemType>::RetrieveItem(ItemType& item, bool& found)
{
 NodeType<ItemType>* location;
 
 location = listData;
 found = false;
 
 while( (location != NULL) && !found) {
 
   if (location->info < item) 
     location = location->next;
   else if (location->info == item) {
     found = true;
     item = location->info;
   }
   else
     location = NULL;  
 }
} 

//INSERT ITEM
template <class ItemType>
void SortedType<ItemType>::InsertItem(ItemType newItem)
{
 NodeType<ItemType>* newNode;
 NodeType<ItemType>* predLoc; 
 NodeType<ItemType>* location;
 bool found;
 
 found = false;
 location = listData;
 predLoc = NULL;
 
 while( location != NULL && !found) {
 
   if (locationinfo < newItem) {
     predLoc = location;
     location = locationnext;
   }
   else
     found = true;
 } 
 newNode = new NodeType<ItemType>;
 newNode->info = newItem;
 
 if (predLoc == NULL) {
   newNode->next = listData;  
   listData = newNode;
 }
 else {
  newNode->next = location;
  predLoc->next = newNode;   
 }
 length++;
} 

//DELETE ITEM
template <class ItemType>
void SortedType<ItemType>::DeleteItem(ItemType item)
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
 
 
 
 
 
 
 
 
 
 
 