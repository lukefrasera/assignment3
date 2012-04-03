#ifndef NODE_H
#define NODE_H

using namespace std;

class PixelType;
class RegionType;

template<class NewType>
class NodeType{
   NewType info;
   NodeType<NewType>* next;
	template<NewType>
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
	RegionType &operator = (const RegionType& );
	
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
   int orientation;
   int eccentricity;
   // INENSITY PROPERTIES
   int mean;
   int min;
   int max;

};



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

#endif
