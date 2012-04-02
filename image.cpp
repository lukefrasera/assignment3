#include "image.h"
#include <math.h>
#include <cmath>

////////////////////////////// ASSIGNMENT 1 ////////////////////////////////////

/* CONSTRUCTOR
Purpose: create an image with default values
*/
ImageType::ImageType()
{
 N = 0;
 M = 0;
 Q = 0;

 pixelValue = NULL;
}

/* DEFAULT CONSTRUCTOR 
Purpose: Allow overloaded values to be run into the constructor
*/
ImageType::ImageType(int tmpN, int tmpM, int tmpQ)
{
 int i, j;

 N = tmpN;
 M = tmpM;
 Q = tmpQ;

 pixelValue = new int* [N];
 for(i=0; i<N; i++) {
   pixelValue[i] = new int[M];
   for(j=0; j<M; j++)
     pixelValue[i][j] = 0;
 }
}

/*COPY CONSTRUCTOR
Purpose: Create a copy of an image when the image is created
*/
ImageType::ImageType( const ImageType& rhs )
{
    N = rhs.N;
    M = rhs.M;
    Q = rhs.Q;
    
    // Allocate Memory
    pixelValue = new int* [ N ];
    for( int i = 0; i < N; i++ )
    {
        pixelValue[i] = new int[ M ];
    }
    
    if( rhs.pixelValue != NULL )
    {
        for( int i = 0; i < N; i++ )
        {
            for( int j = 0; j < M; j++ )
            {
                pixelValue[i][j] = rhs.pixelValue[i][j];
            }
        }
    }
    else
    {
        pixelValue = NULL;
    }
}

/* DESTRUCTOR
Purpose: Delete arrays and reset values
*/
ImageType::~ImageType()
{
    if( pixelValue != NULL )
    {
        for( int i = 0; i < N; i++ )
        {
            delete [] pixelValue[i];
        }
        delete [] pixelValue;
        
        N = -1;
        M = -1;
        Q = -1;
    }

}

/* = OPERATOR OVERLOAD
Purpose: allows a more intuitive statement like image = image to be made
*/
ImageType &ImageType::operator = ( const ImageType &rhs )
{
    if( this != &rhs )
    {
        (*this).N = rhs.N;
        (*this).M = rhs.M;
        (*this).Q = rhs.Q;
        
        if( rhs.pixelValue != NULL )
        {
            for( int i = 0; i < (*this).N; i++ )
            {
                for( int j = 0; j < (*this).M; j++ )
                {
                    (*this).pixelValue[i][j] = rhs.pixelValue[i][j];
                }
            }
            return *this;
        }
        else
        {
            (*this).pixelValue = NULL;
            return *this;
        }
    }
}

/* GET IMAGE INFO
Purpose: get the number of rows, columns and highest pixel value from the
        image.
*/
void ImageType::getImageInfo(int& rows, int& cols, int& levels)
{
 rows = N;
 cols = M;
 levels = Q;
}

/* SET IMAGE INFO
Purpose: set the image information
*/
void ImageType::setImageInfo(int rows, int cols, int levels)
{
 N= rows;
 M= cols;
 Q= levels;
}

/* GET PIXEL VALUE
Purpose: Return the value of the pixel at a designated point
Notes: If the point is out of bounds, an error message is displayed
*/
void ImageType::getPixelVal(int i, int j, int& val)
{
 if( (( i > N ) || ( j > M )) || ((i < 0 ) || (j<0)))
 {
    cout << "Error: point is out of bounds" << endl;
 }
 else
 val = pixelValue[i][j];
 
}

/* SET PIXEL VALUE
Purpose: set a value to a pixel designated by an (x,y) coordinate
Notes: If the point is out of bounds, an error message is displayed
*/
bool ImageType::setPixelVal(int i, int j, int val)
{
 if( (( i > N ) || ( j > M )) || ((i < 0 ) || (j<0)))
 {
    cout << "Error: point is out of bounds" << endl;
    return false;
 }
 else
 pixelValue[i][j] = val;
 return true;
}

/* GET SUB IMAGE
Purpose: crop an existing image down to a smaller size
*/
bool ImageType::getSubImage( const int &ULr, const int&ULc, const int&LRr, 
                        const int&LRc, const ImageType &oldImage )
{
    int hgt, wid, val;
    hgt = LRr - ULr;
    wid = LRc - ULc;
    
    if( oldImage.pixelValue == NULL )
    {
        return false;
    }
    else if( ULr < 0 || ULc < 0 || LRr > oldImage.N || LRc > oldImage.M )
    {
        
        return false;
        
    }
    
    
    if( pixelValue != NULL )
    {
        for( int i = 0; i < N; i++ )
        {
            delete [] pixelValue[i];
        }
        delete [] pixelValue;
    }
    
    N = hgt;
    M = wid;
    Q = oldImage.Q;
    
    pixelValue = new int*[ N ];
    for( int i = 0; i < N; i++ )
    {
        pixelValue[i] = new int[ M ];
    }
    
    for( int i = 0; i < N; i++ )
    {
        for( int j = 0; j < M; j++ )
        {
            pixelValue[i][j] = oldImage.pixelValue[ ULr + i ][ ULc + j ];
        }
    }
    
    return true;
}

/* MEAN GRAY
Purpose: calculate the mean value of the pixels in an image
*/
int ImageType::meanGray()const
{
    int num, counter;
    
    counter = 0;
    
    for( int i = 0; i < N; i++ )
    {
        for( int j = 0; j < M; j++ )
        {
            num += pixelValue[i][j];
            counter++;
        }
    }
    
    num /= counter;
    
    return num;
}

/* ENLARGE IMAGE 
Purpose: Enlarge an image
*/
bool ImageType::enlargeImage( const int &s, const ImageType &oldImage )
{
    if( oldImage.pixelValue == NULL )
    {
        return false;
    }   
    
    if( pixelValue != NULL )
    {
        for( int i = 0; i < N; i++ )
        {
            delete [] pixelValue[i];
        }
        delete [] pixelValue;
    }
    
    N = s * oldImage.N;
    M = s * oldImage.M;
    Q = oldImage.Q;
    
    
    pixelValue = new int*[N];
    for( int i = 0; i < N; i++ )
    {
        pixelValue[i] = new int[M];
    }
    
    for( int i = 0; i < oldImage.N; i++ )
    {
        for( int j = 0; j < oldImage.M; j++ )
        {
            for( int x = (i*s); x < (s+(i*s)); x++ )
            {
                for( int y = (j*s); y < (s+(j*s)); y++ )
                {
                    
                    pixelValue[x][y] = oldImage.pixelValue[i][j];
                    
                }
                
            }

        }
    }
    
    return true;
}

/* SHRINK IMAGE
Process: Make an image tiny by a factor
*/
bool ImageType::shrinkImage( const int& Scale, const ImageType& oldimg)
{
	// initialize variables
	int average;
	
	// check new image
	if( pixelValue != NULL )
	{
		for( int i = 0; i < N; i++ )
			delete [] pixelValue[i];
		
		delete [] pixelValue;
	}
	N = oldimg.N/Scale;
	M = oldimg.M/Scale;
	Q = oldimg.Q;
	
	pixelValue = new int*[N];
	for( int i = 0; i < N; i++ )
		pixelValue[i] = new int[M];
	
	//Render Shrunk image
	for( int i = 0; i < oldimg.N; i += Scale )
	{
		for( int j = 0; j < oldimg.M; j += Scale )
		{
			average = 0;
			for( int q = i; q < (i + Scale); q++ )
				for( int r = j; r < (j + Scale); r++ )
					average += oldimg.pixelValue[q][r];
			average = average / ( Scale * Scale );
			pixelValue[i/Scale][j/Scale] = average;
		}
	}
	return true;
}

/* REFLECT IMAGE
Purpose: Reflect image across the horizontal or vertical axis 
*/
bool ImageType::reflectImage( const bool &flag, const ImageType &oldImage )
{
    if( oldImage.pixelValue == NULL )
    {
        return false;
    }
    
    if( pixelValue != NULL )
    {
        for( int i = 0; i < N; i++ )
        {
            delete [] pixelValue[i];
        }
        delete [] pixelValue;
    }
    
    N = oldImage.N;
    M = oldImage.M;
    Q = oldImage.Q;
    
    pixelValue = new int*[N];
    for( int i = 0; i < N; i++ )
    {
        pixelValue[i] = new int[M];
    }
    
    if( flag == true ) // HORIZONTAL
    {
        for( int i = 0; i < N; i++ )
        {
            for( int j = 0; j < M; j++ )
            {
                pixelValue[i][j] = oldImage.pixelValue[(N - 1) - i][j];
            }
        }
        return true;
    }
    else
    {
        for( int i = 0; i < N; i++ )
        {
            for( int j = 0; j < M; j++ )
            {
                pixelValue[i][j] = oldImage.pixelValue[i][(M - 1) - j];
            }
        }
        return true;
    }
    
}

/* TRANSLATE IMAGE
Process: move an image around
*/
bool ImageType::translateImage( const int &t, const ImageType &oldImage )
{
    if( oldImage.pixelValue == NULL )
    {
        return false;
        
    }
    
    if( pixelValue != NULL )
    {
        for( int i = 0; i < N; i++ )
        {
            delete [] pixelValue[i];
        }
        delete [] pixelValue;
    }

    N = oldImage.N;
    M = oldImage.M;
    Q = oldImage.Q;
    
    pixelValue = new int*[N];
    for( int i = 0; i < N; i++ )
    {
        pixelValue[i] = new int[M];
    }

    // Black out the image
    for( int i = 0; i < N; i++ )
    {
        for( int j = 0; j < M; j++ )
        {
            pixelValue[i][j] = 0;
        }
    }
    
    // Translate
    for( int i = 0; i < N; i++ )
    {
        for( int j = 0; j < M; j++ )
        {
            if( ((i + t ) < N) && ((j + t ) < M ))
            {
                pixelValue[i+t][j+t] = oldImage.pixelValue[i][j];
            }
        }
    }
    
    
    return true;
}

/* ROTATE IMAGE
Purpose: Rotates a given image
Notes: Rotates about the central point
*/
bool ImageType::rotateImage( const int& theta, const ImageType& rhs)
{
    // BASE EQUATION: x' = xcos(theta) - ysin(theta);
	//                y' = xsin(theta) + ycos(theta);
	
    // Initialize Variables
	const double PI = 3.14159;
	const int x = 0;
	const int y = 1;
	int pivot[2];
	int translation[2];
	double radians;
	double x_1, y_1;
	int x_int, y_int;
	// hole fix array
	int** hole_map;
	int average;
	
	if( ( pixelValue == NULL ) )
	{
		M = rhs.M;
		N = rhs.N;
		Q = rhs.Q;
		
		pixelValue = new int*[N];
		
		for( int i = 0; i < N; i++ )
		{
			pixelValue[i] = new int[M];
		}
	}
	
	hole_map = new int*[N];
	for( int i = 0; i < N; i++ )
	{
		hole_map[i] = new int[M];
	}
	
	// Black out new image
	for( int i = 0; i < N; i++ )
	{
		for( int j = 0; j < M; j++ )
		{
			pixelValue[i][j] = 0;
			hole_map[i][j] = 0;
		}
	}
	
	// Locate Pivot
	pivot[x] = rhs.N / 2;
	pivot[y] = rhs.M / 2;
	
	// Claculate Basis Translation
	translation[x] = (N - rhs.N) / 2;
	translation[y] = (M - rhs.M) / 2;
	
	// convert to Radians
	radians = (double(theta) * (PI / 180.0));
	
	//Render Rotated image to new image
	for( int i = 0; i < rhs.N; i++ )
	{
		for( int j = 0; j < rhs.M; j++ )
		{
			x_1 = pivot[x] + ( i - pivot[x] ) * cos( radians ) - ( j - pivot[y] ) * sin(radians);
			y_1 = pivot[y] + ( i - pivot[x] ) * sin( radians ) + ( j - pivot[y] ) * cos(radians);
			
			x_1 = x_1 + translation[x];
			y_1 = y_1 + translation[y];
			
			// Round Coordinates
			if( (x_1 + 0.5) >= ( int(x_1) + 1) )
			{
				x_int = int(x_1) + 1;
			}
			else
			{
				x_int = int(x_1);
			}
			if( (y_1 + 0.5) >= ( int(y_1) + 1) )
			{
				y_int = int(y_1) + 1;
			}
			else
			{
				y_int = int(y_1);
			}
			
			// check if coordinate is inside image base
			if( (x_int >= 0 && y_int >= 0) && (x_int < rhs.N && y_int < rhs.M) )
			{
				// set rotated image pixel
				pixelValue[x_int][y_int] = rhs.pixelValue[i][j];
				hole_map[x_int][y_int] = 1;
			}
		}
	}

	// Extra Credit fix holes
	
	// loops through image
	for( int i = 0; i < N; i++ )
	{
		for( int j = 0; j < M; j++ )
		{
			if( hole_map[i][j] == 0 && ( i > 0 && j >0 ) && (i < (N -1) && j < (M -1)) )
			{
				average = 0;

				for( int k = (i-1); k <= (i+1); k++ )
				{
					for( int q = (j-1); q <= (j+1); q++ )
					{
						average += pixelValue[k][q];
						
					}
				}
            
				// average sum
				average = average / 8;
                		
                	
				pixelValue[i][j] = pixelValue[i+1][j];
			}
		}
	}
	
	return true;
}

/* OVERLOADED + OPERATOR
Purpose: permits the addition of two images
*/
ImageType &operator + (  ImageType &lhs, const ImageType &rhs )
{
    int height, width, b;
    double a = 5;
    
    
    while( (a >= 0) && ( a <= 1 ) );
    {
        cout << "Enter amount to weight the first image( 0 - 1 ): ";
        cin >> a;
    }
    
    if( lhs.N <= rhs.N )
    {
        height = lhs.N;
    }
    else
    {
        height = rhs.N;
    }
    if( lhs.M <= rhs.M )
    {
        width = lhs.M;
    }
    else
    {
        width = rhs.M;
    }
    
    for( int i = 0; i < height; i++ )
    {
        for( int j = 0; j < width; j++ )
        {
            lhs.pixelValue[i][j] = a * lhs.pixelValue[i][j] + 
                                        ( 1 - a ) * rhs.pixelValue[i][j];
        }
    }
    
    return lhs;
    
}

/* OVERLOADED - OPERATOR
Purpose: permits the addition of two images
*/
ImageType &operator - (  ImageType &lhs, const ImageType &rhs )
{
    int height, width, b;

    
    if( lhs.N <= rhs.N )
    {
        height = lhs.N;
    }
    else
    {
        height = rhs.N;
    }
    if( lhs.M <= rhs.M )
    {
        width = lhs.M;
    }
    else
    {
        width = rhs.M;
    }
    
    for( int i = 0; i < height; i++ )
    {
        for( int j = 0; j < width; j++ )
        {
            lhs.pixelValue[i][j] = abs( (lhs.pixelValue[i][j] - rhs.pixelValue[i][j] ) );
        }
    }
    
    return lhs;
    
}

/* NEGATE IMAGE
Purpose: negate the image
*/
bool ImageType::negateImage( const ImageType &image )
{
    if( image.pixelValue == NULL )
    {
        return false;
    }
    
    if( pixelValue != NULL )
    {
        for( int i = 0; i < N; i++ )
        {
            delete [] pixelValue[i];
        }
        delete [] pixelValue;
    }
    
    N = image.N;
    M = image.M;
    Q = image.Q;
    
    pixelValue = new int*[N];
    for( int i = 0; i < N; i++ )
    {
        pixelValue[i] = new int[M];
    }
    
    for( int i = 0; i < N; i++ )
    {
        for( int j = 0; j < M; j++ )
        {
            pixelValue[i][j] = -image.pixelValue[i][j] + 255;
        }   
    }
    
    return true;
    
}   

/////////////////////////////// ASSIGNMENT 2 ///////////////////////////////////
/* THRESHOLD
Purpose: create a binary image based on an input image
*/
bool ImageType::threshold( const int & T_in, ImageType & rhs )
{    
    // Re-size image
    if( rhs.pixelValue == NULL )
    {
        return false;
    }
    
    if( pixelValue != NULL )
    {
        for( int i = 0; i < N; i++ )
        {
            delete [] pixelValue[i];
        }
        delete [] pixelValue;
    }
    
    N = rhs.N;
    M = rhs.M;
    Q = rhs.Q;
    
    pixelValue = new int*[N];
    for( int i = 0; i < N; i++ )
    {
        pixelValue[i] = new int[M];
    }

    // Threshold image
   for( int i = 0; i < N; i++ )
   {
       for( int j = 0; j < M; j++ )
       {
           if( rhs.pixelValue[i][j] <= T_in )
               pixelValue[i][j] = 0;
           else
               pixelValue[i][j] = 255;
       }
   }
   return true;
   
}

/* DILATE
Purpose: dilates the images
*/
bool ImageType::dilate( ImageType & rhs )
{
    // Re-size image
    if( rhs.pixelValue == NULL )
    {
        return false;
    }
    
    if( pixelValue != NULL )
    {
        for( int i = 0; i < N; i++ )
        {
            delete [] pixelValue[i];
        }
        delete [] pixelValue;
    }
    
    N = rhs.N;
    M = rhs.M;
    Q = rhs.Q;
    
    pixelValue = new int*[N];
    for( int i = 0; i < N; i++ )
    {
        pixelValue[i] = new int[M];
    }
    
   // DILATE THE IMAGE
   bool set = 0;
   // Loop through image:
   for( int i = 0; i < N; i++ )
   {
       for( int j = 0; j < M; j++ )
       {
       
       
           // Check surrounding area for white
           for( int l = (i-1); l <= (i+1); l++ )
           {
               for( int k = (j-1); k <= (j+1); k++ )
               {
                   if( l < N && k < M && l > 0 && k > 0 )
                   {
                      if( rhs.pixelValue[l][k] == 255 )
                      {
                          set = true;
                          break;
                      }
                   }
               }
               if( set == true )
                   break;
           }
           
           
           
           
           if( set == true )
           {
               pixelValue[i][j] = 255;
               set = false;
           }
           else
           {
               pixelValue[i][j] = rhs.pixelValue[i][j];
               set = false;
           }
       }
   }
   return true;
}

/* ERODE
Purpose: erodes the images
*/
bool ImageType::erode( ImageType & rhs )
{
    // Re-size image
    if( rhs.pixelValue == NULL )
    {
        return false;
    }
    
    if( pixelValue != NULL )
    {
        for( int i = 0; i < N; i++ )
        {
            delete [] pixelValue[i];
        }
        delete [] pixelValue;
    }
    
    N = rhs.N;
    M = rhs.M;
    Q = rhs.Q;
    
    pixelValue = new int*[N];
    for( int i = 0; i < N; i++ )
    {
        pixelValue[i] = new int[M];
    }
    
   // DILATE THE IMAGE
   bool set = 0;
   // Loop through image:
   for( int i = 0; i < N; i++ )
   {
       for( int j = 0; j < M; j++ )
       {
       
       
           // Check surrounding area for white
           for( int l = (i-1); l <= (i+1); l++ )
           {
               for( int k = (j-1); k <= (j+1); k++ )
               {
                   if( l < N && k < M && l > 0 && k > 0 )
                   {
                      if( rhs.pixelValue[l][k] == 0 )
                      {
                          set = true;
                          break;
                      }
                   }
               }
               if( set == true )
                   break;
           }
           
           
           
           
           if( set == true )
           {
               pixelValue[i][j] = 0;
               set = false;
           }
           else
           {
               pixelValue[i][j] = rhs.pixelValue[i][j];
               set = false;
           }
       }
   }
   return true;
}






