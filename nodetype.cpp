#include "nodetype.h"

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
