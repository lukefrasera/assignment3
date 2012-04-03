#ifndef SORT_H
#define SORT_H
#include <iostream>
#include "image.h"
#include <cmath>

using namespace std;

template<class ItemType>
class NodeType;

template<class ItemType>
class SortedType;

template<class ItemType>
class UnsortedType;

class RegionType;

class PixelType;

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
   
   friend class RegionType;
   
   private:
   int length;
   NodeType<ItemType> *listData;
   NodeType<ItemType>* currentPos;
};

template<class NewType>
class NodeType{
   NewType info;
   NodeType<NewType>* next;
	template<class ItemType>
	friend class SortedType;
	template<class ItemType>
	friend class UnsortedType;
	friend class RegionType;
};

class PixelType{
   public:
   void print();
   int x;
   int y;
   friend class RegionType;
   
};

class RegionType{
	public:
	RegionType();
	void print();
	RegionType &operator = ( RegionType& );
	bool operator < (const RegionType& );
	bool operator <= (const RegionType& );
	bool operator == (const RegionType& );
	void setSize( int );
	void setOrientation( int );
	void setEcc( int );
	void setInt( int );
	void writeToImage( ImageType &, ImageType & );
	void calcOrientation();
	void calcEccentricity();
	void calcIntensity(ImageType );
	void calcCentroid();
	bool orCompare( RegionType, RegionType );
	bool eccCompare( RegionType, RegionType);
	bool intCompare( RegionType, RegionType );
	
	
	
	template<class ItemType>
	friend class NodeType;
   
   template<class ItemType>
   friend class SortedType;
   
   template<class ItemType>
   friend class UnsortedType;
   
   UnsortedType<PixelType> pixel_list;
   
   private:
   // GEOMETRIC PROPERTIES
   PixelType centroid;
   int size;
   float orientation;
   float eccentricity;
   // INENSITY PROPERTIES
   int mean;
   int min;
   int max;
   
   float lambda_min, lambda_max, axes_max, axes_min;
   
	// List of pixels
	
	
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

////////////////////////// PIXELTYPE IMPELEMNATION ////////////////////////////
void PixelType::print()
{
	cout << "( " << x << ", " << y << " )";
}
//////////////////////// REGION IMPLEMENTATION///////////////////////////////////
RegionType::RegionType()
{
	centroid.x = 0;
	centroid.y = 0;
	
	size = 0;
	orientation = 0;
	eccentricity = 0; 
	mean = 0;
	min = 0;
	max = 0;
}

void RegionType::print()
{
	cout << "Geometric Properties:" << endl;
	cout << "  Centroid: ";
		centroid.print();
	cout << endl;
	cout << "  Size: " << size << endl;
	cout << "  Orientation: " << orientation << endl;
	cout << "  Eccentricity: " << eccentricity << endl;
	cout << "Photometric Properties:" << endl;
	cout << "  Mean Intensity: " << mean << endl;
	cout << "  Minimum Intensity: " << min << endl;
	cout << "  Maximum Intensity: " << max << endl;
}

RegionType &RegionType:: operator = ( RegionType &rhs )
{
	PixelType dummy;
	
	if( this != &rhs )
	{
		(*this).size = rhs.size;
		(*this).orientation = rhs.orientation;
		(*this).eccentricity = rhs.eccentricity;
		(*this).mean = rhs.mean;
		(*this).min = rhs.min;
		(*this).max = rhs.max;
		
		// Copy Pixels
		rhs.pixel_list.ResetList();
		pixel_list.MakeEmpty();
		
		while( !rhs.pixel_list.IsLastItem() )
		{
			rhs.pixel_list.GetNextItem( dummy );
			pixel_list.InsertItem( dummy );

		}
		return *this;
	}
}

void RegionType::calcCentroid()
{
	PixelType temp;
	centroid.x = 0;
	centroid.y = 0;
	pixel_list.ResetList();
	
	while( !pixel_list.IsLastItem() )
	{
		pixel_list.GetNextItem( temp );
		
		centroid.x += temp.x;
		centroid.y += temp.y;
	}
	centroid.x /= pixel_list.LengthIs();
	size = pixel_list.LengthIs();
}

void RegionType::calcOrientation()
{
	int moment_2_x = 0;
	int moment_1_1 = 0;
	PixelType temp;
	
	if( eccentricity != 0 )
	{
		pixel_list.ResetList();
		while( !pixel_list.IsLastItem() )
		{
			pixel_list.GetNextItem( temp );
			
			moment_2_x += (( temp.x - centroid.x )*( temp.x - centroid.x ));
			moment_1_1 += (temp.x - centroid.x)*(temp.y - centroid.y);
		}
		
		orientation = atan((lambda_max - moment_2_x)/moment_1_1 );
	}
}

void RegionType::calcEccentricity()
{
	// Variables for Moment calclation
	PixelType moment_2;
	PixelType temp;
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
		
		square_root = sqrt( (moment_2.x)*(moment_2.x) + (moment_2.y)*(moment_2.y) - 
										2*(moment_2.x)*(moment_2.y) + 4 * (moment_1_1)*(moment_1_1));
		
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
	mean = 0;
	min = 0;
	max = 0;
	int imagevalue;
	PixelType temp;
	pixel_list.ResetList();
	while( !pixel_list.IsLastItem() )
	{
		pixel_list.GetNextItem( temp );
		rhs.getPixelVal( temp.x, temp.y, imagevalue );
		mean += imagevalue;
		if( mean < imagevalue )
		{
			max = imagevalue;
		}
		if( min > imagevalue )
		{
			min = imagevalue;
		}
	}
	
	mean /= pixel_list.LengthIs();
}

bool RegionType::operator < (const RegionType &rhs )
{
	return ( size < rhs.size );
}

bool RegionType::operator <= (const RegionType &rhs )
{
	return ( size <= rhs.size );
}

bool RegionType::operator == (const RegionType& rhs)
{
	return( size == rhs.size );
}

void RegionType::setSize( int a )
{
	size = a;
}

void RegionType::setOrientation( int a )
{
	orientation = a;
}

void RegionType::setEcc( int a )
{
	eccentricity = a;
}

void RegionType::setInt( int a )
{
	mean = a;
}

bool RegionType::orCompare( RegionType a, RegionType b)
{
	if( a.orientation < b.orientation )
	{
		return true;
	}
	else
	return false;
}

bool RegionType::eccCompare( RegionType a, RegionType b)
{
	if( a.eccentricity < b.eccentricity )
	{
		return true;
	}
	else
	return false;
}

bool RegionType::intCompare( RegionType a, RegionType b )
{
	if( a.mean < b.mean )
	{
		return true;
	}
	else
	return false;
}

void RegionType::writeToImage( ImageType &source, ImageType &dest )
{
	PixelType temp;
	int tempColor;
	
	pixel_list.ResetList();
	
	while( !pixel_list.IsLastItem() )
	{
		pixel_list.GetNextItem( temp );
		source.getPixelVal( (*pixel_list.listData).info.x, 
										(*pixel_list.listData).info.y, tempColor );
		dest.setPixelVal( (*pixel_list.listData).info.x, 
										(*pixel_list.listData).info.y, tempColor );
	}
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
