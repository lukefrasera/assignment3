#include <iostream>

using namespace std;

class PixelType;
class RegionType;

template<class ItemType>
class NodeType{
   ItemType info;
   NodeType<ItemType>* next;
};

class RegionType{
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


class PixelType{
   private:
   int x;
   int y;
   friend class RegionType;
};
