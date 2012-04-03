#ifndef SORT_H
#define SORT_H
#include <iostream>

using namespace std;



template<class NewType>
class NodeType{
   NewType info;
   NodeType<NewType>* next;
	template<class ItemType>
	friend class SortedType;
};

class PixelType{
   private:
   int x;
   int y;
   friend class RegionType;
};

class RegionType{
public:

	// Compute region operations //
	void calcCentroid();
	void calcSize();
	void calcOrientation();
	void calcEccentricity();
	void calcIntensity();
	// ************************ //
	
	RegionType &operator = (const RegionType& );
	bool operator < (const RegionType& );
	
	template<class ItemType>
	friend class NodeType;
   
   template<class ItemType>
   friend class SortedType;
   
   template<class ItemType>
   friend class UnsortedType;
   
   private:
   // GEOMETRIC PROPERTIES
   PixelType centroid;
   int size;
   float orientation;
   float eccentricity;
   
   // axes calculations
   float axes_max;
   float axes_min;
   
   // principal moments
   float lambda_max;
   float lambda_min;
   
   
   // INENSITY PROPERTIES
   int mean;
   int min;
   int max;
   

};

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

template <class ItemType>
class UnsortedType{
   public:
   UnsortedType();
   ~UnsortedType();
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




//////////////////////////  SORTED IMPLEMENTATION //////////////////////////////
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
void SortedType<ItemType>::ResetList()
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
   if (location->info < newItem) {
     predLoc = location;
     location = location->next;
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
//////////////////////// REGION IMPLEMENTATION///////////////////////////////////
RegionType &RegionType:: operator = (const RegionType &rhs )
{
	if( this != &rhs )
	{
		(*this).size = rhs.size;
		(*this).orientation = rhs.orientation;
		(*this).eccentricity = rhs.eccentricity;
		(*this).mean = rhs.mean;
		(*this).min = rhs.min;
		(*this).max = rhs.max;
		
		return *this;
	}
}
/*
	void calcCentroid();
	void calcSize();
	void calcOrientation();
	void calcEccentricity();
	void calcIntensity();
*/
void RegionType::calcCentroid()
{
	// calculate the centroid //
	pixelType temp;
	pixel_list.ResetList();
	
	centroid.x = 0;
	centroid.y = 0;
		//calcuate the X bar
	while( !pixel_list.IsLastItem() )
	{
		pixel_list.GetNextItem( temp );
		centroid.x += temp.x;
		centroid.y += temp.y;
	}
	
	centroid.x /= pixel_list.LengthIs();
	centroid.y /= pixel_list.LengthIs();
}

void RegionType::calcSize()
{
	// calculate the area of the region //
	// calculate the first moment //
	
	// set size equal to the length of the list  //
	size = pixel_list.LengthIs();
}

void RegionType::calcOrientation()
{
	int momen_2_x = 0;
	int moment_1_1 = 0;
	pixelType temp;
	
	if( eccentricity != 0 )
	{
		pixel_list.ResetList();
		while( !pixel_list.IsLastItem() )
		{
			pixel_list.GetLastNextItem( temp );
			
			moment_2_x += (( temp.x - centroid.x )*( temp.x - centroid.x ));
			moment_1_1 += (temp.x - centroid.x)*(temp.y - centroid.y);
		}
		
		orientation = atan((lambda_max - moment_2_x)/moment_1_1 );
	}
}

void RegionType::calcEccentricity()
{
	// Variables for Moment calclation
	pixelType moment_2;
	pixelType temp;
	float square_root;
	int moment_1_1 = 0;
	
	moment_2.x = 0;
	moment_2.y = 0;
	if( centroid.x != 0 )
	{
		pixel_list.ResetList();
		while( !pixel_list.IsLastItem() )
		{
			pixel_list.GetNextItem( temp );
			moment_2.x += (( temp.x - centroid.x )*( temp.x - centroid.x ));
			moment_2.y += (( temp.y - centroid.y )*( temp.y - centroid.y ));
			moment_1_1 += (temp.x - centroid.x)*(temp.y - centroid.y);
		}
		
		square_root = sqrt( (moment_2.x)*(moment_2.x) + (moment_2.y)*(moment_2.y) - 2*(moment_2.x)*(moment_2.y)
			+ 4 * (moment_1_1)(moment_1_1));
		
		lambda_max = 0.5 * (moment_2.x + moment_2.y) + 0.5 * square_root;
		lambda_min = 0.5 * (moment_2.x + moment_2.y) - 0.5 * square_root;
		
		axes_max = sqrt( lambda_max / pixel_list.LengthIs() );
		axes_min = sqrt( lambda_min / pixel_list.LengthIs() );
		
		eccentricity = (axes_max  / axes_min);
	}
}
/*
   int mean;
   int min;
   int max;
*/
void RegionType::calcIntensity( ImageType rhs)
{
	
}

bool RegionType::operator < (const RegionType &rhs )
{
	return ( size < rhs.size );
}

/////////////////////////// UNSORTED IMPLEMENTATION ////////////////////////////
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
#endif
