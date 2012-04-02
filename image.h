#include <iostream>
#ifndef IMAGE_H
#define IMAGE_H

using namespace std;


class ImageType {
 public:
    // ASSIGNMENT 1
    ImageType();
    ImageType(int, int, int);
    ImageType( const ImageType& );
    ~ImageType();
    ImageType &operator = (const ImageType& );
    void getImageInfo(int&, int&, int&);
    void setImageInfo(int, int, int);
    bool setPixelVal(int, int, int);
    void getPixelVal(int, int, int&);
    bool getSubImage( const int&, const int&, const int&, const int&, const ImageType& );
    int meanGray()const;
    bool enlargeImage( const int&, const ImageType& );
    bool shrinkImage( const int&, const ImageType& );
    bool reflectImage( const bool&, const ImageType& );
    bool translateImage( const int&, const ImageType& );
    bool rotateImage( const int&, const ImageType& );
    
    friend ImageType &operator + ( ImageType&, const ImageType& );
    friend ImageType &operator - ( ImageType&, const ImageType& );
    
    bool negateImage( const ImageType& );
    
    // ASSIGNMENT 2
    bool threshold( const int &, ImageType & );
    bool dilate( ImageType & rhs );
    bool erode( ImageType & rhs );
       
 private:
   int N, M, Q;
   int **pixelValue;

   
};


#endif
