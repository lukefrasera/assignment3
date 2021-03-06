#ifndef DRIVE_H
#define DRIVE_H

#include <iostream>
#include "image.h"
#include "ReadImageHeader.cpp"
#include "ReadImage.cpp"
#include "WriteImage.cpp"
#include "stack.h"
#include "queue.h"
#include "list.h"


using namespace std;



// Function prototypes
int computeComponents_BFS_(  ImageType & input, ImageType & output );

int computeComponents_DFS_(  ImageType & input, ImageType & output, 
											SortedType<RegionType> listOfRegions, ImageType & );


void findcomponentBFS( ImageType & input, ImageType & output, int x, int y,
                         int label );
                         
void findcomponentDFS(  ImageType & input, ImageType & output, int x, int y,
                            int label, RegionType& region, ImageType& Origonal );


// SUB MENU FUNCTIONS
void displaySizes( ImageType &, SortedType<RegionType> rhs, int, int );

void displayOrientations( ImageType &input, SortedType<RegionType> rhs, 
										int small, int big );

void displayEcc( ImageType &input, SortedType<RegionType> rhs, 
										int small, int big );

void displayInt( ImageType &input, SortedType<RegionType> rhs, 
										int small, int big );

void deleteSmallComponents( SortedType<RegionType>, int );

//////////////////////// Calculate Found Regions /////////////////////////
//////////////////////////////////////////////////////////////////////////
void RenderRegions( RegionType& region, const ImageType& input );

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


int main()
{
    int row, col, max, selection, pixel, thresh, label, sub_select = 0;
    int x_in, x_col, y_in, y_col;
    bool test = false;
    char file_name[20], out_name[20], image_1[20], image_2[20], sel;
    int** maker;
    char cont;
    ImageType tester;

    
    cout << "------- Program Tester -------" << endl;
    cout << "Input File Name: ";
    cin >> file_name;
    
    //Read Information from file to dummy ints
    cout << endl << "Retrieving Header Information" << endl;
    readImageHeader( file_name, row, col, max, test );
    cout << "Completed." << endl;
    
    // Define image
    ImageType picture( row, col, max);
    
    // Read image from file to array
    cout << endl << "Retrieving File Informtation..." << endl;
    readImage( file_name, picture );
    cout << "Completed." << endl;

    // Display Menu
    do{
        cout << " ===== MAIN MENU =====" << endl;
        cout << "1. getImageInfo" << endl;
        cout << "2. getPixelVal" << endl;
        cout << "3. setPixelVal" << endl;
        cout << "4. getSubImage" << endl;
        cout << "5. meanGray" << endl;
        cout << "6. enlargeImage" << endl;
        cout << "7. shrinkImage" << endl;
        cout << "8. reflectImage" << endl;
        cout << "9. translateImage" << endl;
        cout << "10. rotateImage" << endl;
        cout << "11. Add Images" << endl;
        cout << "12. Subtract Images" << endl;
        cout << "13. Negate Image" << endl;
        cout << "14. Threshold Image" << endl;
        cout << "15. Dilate Image" << endl;
        cout << "16. Erode Image" << endl;
        cout << "17. computeComponents (BFS)" << endl;
        cout << "18. computeComponents (DFS)" << endl;
        cout << "19. Display Region Information" << endl;
        cout << "20. Quit" << endl;
        cin >> selection;
        cout << endl << endl;
        
        switch( selection )
        {
            case 1:
            cout << "-- getImageInfo -- " << endl;
            picture.getImageInfo( row, col, max );
            cout << "Rows: " << row << endl;
            cout << "Columns: " << col << endl;
            cout << "Maximum Grayscale Value: " << max << endl;
            cout << endl << endl;
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            
            case 2:
            cout << "-- getPixelVal --" << endl;
            cout << "Enter X Position: ";
            cin >> x_in;
            cout << "Enter Y Position: ";
            cin >> y_in;
            picture.getPixelVal( x_in, y_in, pixel );
            if( pixel >= 0 )
            {
                cout << "Value: " << pixel << endl << endl;
            }
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            
            case 3:
            cout << "-- setPixelVal --" << endl;
            cout << "Enter New Pixel Value: ";
            cin >> pixel;
            cout << "Enter X Position: ";
            cin >> x_in;
            cout << "Enter Y Position: ";
            cin >> y_in;
            test = picture.setPixelVal( x_in, y_in, pixel );
            if( test == true )
            {
            cout << endl << "New value set." << endl;
            picture.getPixelVal( x_in, y_in, pixel );            
            cout << "Value: " << pixel << endl << endl;
            }
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            
            case 4:
            cout << "-- getSubImage --" << endl;
            
            cout << "Enter the Upper Left Row: " << endl;
            cin >> x_in;
            cout << "Enter the Upper Left Column: " << endl;
            cin >> x_col;
            cout << "Enter the Lower Right Row: " << endl;
            cin >> y_in;
            cout << "Enter the Lower Right Column: " << endl;
            cin >> y_col;
            
            cout << endl << endl;
            
            test = tester.getSubImage( x_in, x_col, y_in, y_col, picture );
            
            cout << "Enter desired file name: ";
            cin >> out_name;
            
            if( test == true )
            {
                writeImage( out_name, tester );
            }
            else
            cout << "Error: There was a problem writing the image to file" << endl;
            cout << endl;
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            
            case 5:
            cout << "-- meanGray --" << endl;
            pixel = picture.meanGray();
            cout << "The mean value of the image is: " << pixel << endl << endl;
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            
            case 6:
            cout << "-- enlargeImage --" << endl;
            cout << "Enter the scale to enlarge: " << endl;
            cin >> pixel;
            
            test = tester.enlargeImage( pixel, picture );
            
            cout << "Enter desired file name: ";
            cin >> out_name;
            
            if( test == true )
            {
                writeImage( out_name, tester );
            }
            else
            cout << "Error: There was a problem writing the image to file" << endl;
            cout << endl;
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            
            case 7:
            cout << "-- shrinkImage --" << endl;
            cout << "Enter the factor by which it should be shrunk: ";
            cin >> pixel;
            
            test = tester.shrinkImage( pixel, picture );
            
            cout << "Enter desired file name: ";
            cin >> out_name;
            
            if( test == true )
            {
                writeImage( out_name, tester );
            }
            else
            cout << "Error: There was a problem writing the image to file" << endl;
            cout << endl;
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            
            case 8:
            cout << "-- reflectImage -- " << endl;
            while( (sel != 'h') && (sel != 'v' ) )
            {
                cout << "Flip horizontal or vertical? <h/v>: ";
                cin >> sel;
            }
            if( sel == 'h' )
            {
                test = true;
            }
            else
            {
                test = false;
            }
            
            test = tester.reflectImage( test, picture );
            
            cout << "Enter desired file name: ";
            cin >> out_name;
            
            if( test == true )
            {
                writeImage( out_name, tester );
            }
            else
            cout << "Error: There was a problem writing the image to file" << endl;
            cout << endl;
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            sel = 'a';
            break;
            
            
            case 9:
            cout << "-- translateImage --" << endl;
            cout << "Enter amount to translate: ";
            cin >> pixel;
            
            test = tester.translateImage( pixel, picture );
            
            cout << "Enter desired file name: ";
            cin >> out_name;
            
            if( test == true )
            {
                writeImage( out_name, tester );
            }
            else
            cout << "Error: There was a problem writing the image to file" << endl;
            cout << endl;
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            
            case 10:
            cout << "-- rotateImage --" << endl;
            cout << "Enter angle of rotation: ";
            cin >> pixel;
            
            test = tester.rotateImage( pixel, picture );
            
            cout << "Enter desired file name: ";
            cin >> out_name;
            
            if( test == true )
            {
                writeImage( out_name, tester );
            }
            else
            cout << "Error: There was a problem writing the image to file" << endl;
            cout << endl;
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            
            case 11:
            {
            cout << "-- overloaded + operator --" << endl;
            cout << "Enter file 1: ";
            cin >> image_1;
            //Read Information from file to dummy ints
            cout << endl << "Retrieving Header Information" << endl;
            readImageHeader( image_1, row, col, max, test );
            cout << "Completed." << endl;
            
            // Define image
            ImageType img_1( row, col, max);
            
            // Read image from file to array
            cout << endl << "Retrieving File Informtation..." << endl;
            readImage( image_1, img_1 );
            cout << "Completed." << endl << endl << endl;
            
            cout << "Enter file 2: ";
            cin >> image_2;
            //Read Information from file to dummy ints
            cout << endl << "Retrieving Header Information" << endl;
            readImageHeader( image_2, row, col, max, test );
            cout << "Completed." << endl;
            
            // Define image
            ImageType img_2( row, col, max);
            
            // Read image from file to array
            cout << endl << "Retrieving File Informtation..." << endl;
            readImage( image_2, img_2 );
            cout << "Completed." << endl << endl << endl;
            
            img_1 + img_2;

            cout << "Enter desired file name: ";
            cin >> out_name;

            writeImage( out_name, img_1 );
                
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            }
            
            case 12:
            {
            cout << "-- overloaded - operator --" << endl;
            cout << "Enter file 1: ";
            cin >> image_1;
            //Read Information from file to dummy ints
            cout << endl << "Retrieving Header Information" << endl;
            readImageHeader( image_1, row, col, max, test );
            cout << "Completed." << endl;
            
            // Define image
            ImageType sub_1( row, col, max);
            
            // Read image from file to array
            cout << endl << "Retrieving File Informtation..." << endl;
            readImage( image_1, sub_1 );
            cout << "Completed." << endl << endl << endl;
            
            cout << "Enter file 2: ";
            cin >> image_2;
            //Read Information from file to dummy ints
            cout << endl << "Retrieving Header Information" << endl;
            readImageHeader( image_2, row, col, max, test );
            cout << "Completed." << endl;
            
            // Define image
            ImageType sub_2( row, col, max);
            
            // Read image from file to array
            cout << endl << "Retrieving File Informtation..." << endl;
            readImage( image_2, sub_2 );
            cout << "Completed." << endl << endl << endl;
            
            sub_1 - sub_2;

            cout << "Enter desired file name: ";
            cin >> out_name;

            writeImage( out_name, sub_1 );
                
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            
            break;
            }
            
            case 13:
            cout << "-- negateImage --" << endl;
                        
            test = tester.negateImage( picture );
            
            cout << "Enter desired file name: ";
            cin >> out_name;
            
            if( test == true )
            {
                writeImage( out_name, tester );
            }
            else
            cout << "Error: There was a problem writing the image to file" << endl;
            cout << endl;
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            
            case 14: 
            cout << "-- threshold --" << endl;
            cout << "Enter threshold between 0 and 255: ";
            cin >> thresh;
            
            test = tester.threshold( thresh, picture );
            
            cout << "Enter desired file name: ";
            cin >> out_name;
            
            if( test == true )
            {
                writeImage( out_name, tester );
            }
            else
            cout << "Error: There was a problem writing the image to file" << endl;
            cout << endl;
            
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            
            case 15:
            {
            cout << "-- dilate --" << endl;
            cout << "Enter thresholded image: ";
            cin >> image_2;
            //Read Information from file to dummy ints
            cout << endl << "Retrieving Header Information" << endl;
            readImageHeader( image_2, row, col, max, test );
            cout << "Completed." << endl;
            
            // Define image
            ImageType dilate( row, col, max);
            
            // Read image from file to array
            cout << endl << "Retrieving File Informtation..." << endl;
            readImage( image_2, dilate );
            cout << "Completed." << endl << endl << endl;
            
            test = tester.dilate( dilate );
            
            cout << "Enter desired file name: ";
            cin >> out_name;
            
            if( test == true )
            {
                writeImage( out_name, tester );
            }
            else
            cout << "Error: There was a problem writing the image to file" << endl;
            cout << endl;
            
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            }
            
            case 16:
            {
            cout << "-- erode --" << endl;
            cout << "Enter thresholded image: ";
            cin >> image_2;
            //Read Information from file to dummy ints
            cout << endl << "Retrieving Header Information" << endl;
            readImageHeader( image_2, row, col, max, test );
            cout << "Completed." << endl;
            
            // Define image
            ImageType erode( row, col, max);
            
            // Read image from file to array
            cout << endl << "Retrieving File Informtation..." << endl;
            readImage( image_2, erode );
            cout << "Completed." << endl << endl << endl;
            
            test = tester.erode( erode );
            
            cout << "Enter desired file name: ";
            cin >> out_name;
            
            if( test == true )
            {
                writeImage( out_name, tester );
            }
            else
            cout << "Error: There was a problem writing the image to file" << endl;
            cout << endl;
            
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            }
            
            case 17: 
            {
            cout << "-- computeComponents_BFS --" << endl;
            
            // get picture sizes
            picture.getImageInfo( row, col, max );
            
            // Create new output image of the right size
            ImageType BFS( row, col, max );
            
            label = computeComponents_BFS_( picture, BFS );
            
            cout << "Objects in image: " << label << endl;
            
            cout << "Enter desired file name: ";
            cin >> out_name;
            writeImage( out_name, BFS );
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            }
            
            case 18: 
            {
            cout << "-- computeComponents_DFS --" << endl;
            // get picture sizes
            picture.getImageInfo( row, col, max );
            
            // Create new output image of the right size
            ImageType DFS( row, col, max );
			
            ///////////////////////////////////////////////////
            //label = computeComponents_DFS_( picture, DFS );
            
            cout << "Objects in image: " << label << endl;
            
            cout << "Enter desired file name: ";
            cin >> out_name;
            writeImage( out_name, DFS );
            
            while( cont != 'y' )
            {
                cout << "Continue? <y/n>" << endl;
                cin >> cont;
            }
            cont = 'n';
            break;
            }
            
            case 19:
            {
            	int A, B, min_size;
            	
            	
            	cout << "Input File Name of Original File: ";
    				cin >> file_name;
    
            	//Read Information from file to dummy ints
					cout << endl << "Retrieving Header Information" << endl;
					readImageHeader( file_name, row, col, max, test );
					cout << "Completed." << endl;
					
					// Define image
					ImageType sub_pic( row, col, max);
					ImageType result_pic( row, col, max );
					SortedType<RegionType> regions;
					 
					// Read image from file to array
					cout << endl << "Retrieving File Informtation..." << endl;
					readImage( file_name, sub_pic );
					cout << "Completed." << endl;
					
					
					
					cout << "Input File Name of Diluted File: ";
    				cin >> file_name;
    
            	//Read Information from file to dummy ints
					cout << endl << "Retrieving Header Information" << endl;
					readImageHeader( file_name, row, col, max, test );
					cout << "Completed." << endl;
					
					// Define image
					ImageType dilute_pic( row, col, max);
					 
					// Read image from file to array
					cout << endl << "Retrieving File Informtation..." << endl;
					readImage( file_name, dilute_pic );
					cout << "Completed." << endl;
					
					// CALL MANIPULATION ON IMAGE
					computeComponents_DFS_( dilute_pic, result_pic, regions, sub_pic );
					
					
					cout << "Enter the minimum size for objects: ";
					cin >> min_size;
					
					deleteSmallComponents( regions, min_size );
					
					
					
					////// GET REGIONS
		         do{
		         	cout << "========== Regions and their Properties ==========" << endl;
		         	//regions.print(); // PRINT REGION INFORMATION
		         	cout << "Operations: " << endl;
		         	cout << "1. Display Regions - Size" << endl;
		         	cout << "2. Display Regions - Orientation" << endl;
		         	cout << "3. Display Regions - Eccentricity" << endl;
		         	cout << "4. Display Regions - Mean Intensity" << endl;
		         	cout << "5. Return to Main" << endl;
		         	cin >> sub_select;
		         	
		         	switch( sub_select )
		         	{
		         		case 1: 
		         		//Display size regions
		         		cout << "Display Regions Between Two Sizes:" << endl;
		      		
				   		cout << "Enter Smaller Size: ";
				   		cin >> A;
				   		cout << "Enter Larger Size: ";
				   		cin >> B;
				   		
				   		if( B < A )
				   		{
				   			cout << "ERROR: The sizes were entered incorrectly" << endl;
				   			break;
				   		}
				   		
				   		displaySizes( sub_pic, regions, A, B );
				      		
		         		break;
		         		
		         		case 2:
		         		// display orientation regions
		         		cout << "Display Regions Between Two Orientations:" << endl;
		      		
				   		cout << "Enter Smaller Orientation: ";
				   		cin >> A;
				   		cout << "Enter Larger Orientation: ";
				   		cin >> B;
				   		
				   		if( B < A )
				   		{
				   			cout << "ERROR: The sizes were entered incorrectly" << endl;
				   			break;
				   		}
				   		
				   		displayOrientations( sub_pic, regions, A, B );
		         		break;
		         		
		         		case 3:
		         		// display eccentricity regions
		         		cout << "Display Regions Between Two Eccentricities:" << endl;
		      		
				   		cout << "Enter Smaller Eccentricity: ";
				   		cin >> A;
				   		cout << "Enter Larger Eccentricity: ";
				   		cin >> B;
				   		
				   		if( B < A )
				   		{
				   			cout << "ERROR: The sizes were entered incorrectly" << endl;
				   			break;
				   		}
				   		
				   		displayEcc( sub_pic, regions, A, B );
				   		
		         		break;
		         		
		         		case 4:
		         		// display mean intensity regions
		         		cout << "Display Regions Between Two Eccentricities:" << endl;
		      		
				   		cout << "Enter Smaller Eccentricity: ";
				   		cin >> A;
				   		cout << "Enter Larger Eccentricity: ";
				   		cin >> B;
				   		
				   		if( B < A )
				   		{
				   			cout << "ERROR: The sizes were entered incorrectly" << endl;
				   			break;
				   		}
				   		
				   		displayInt( sub_pic, regions, A, B );
				   		
		         		break;
		         		
		         	}
		         	
		         }while( sub_select != 5 );
            }
        }
        
    }while( selection != 20 );
    
    return 0;
}



/////////////////////////////// Supporting Functions ///////////////////////////

/* computeComponents
Purpose: Compute how many objects are in an image
Notes: The two images passed into the function must already be sized
       the same
*/
int computeComponents_BFS_( ImageType & input, ImageType & output )
{
   int row, col, LEVEL;
   int value, value_2;
   int conncomp, label;
   
   // retrieve image info
   input.getImageInfo( row, col, LEVEL );
   
   for( int i = 0; i < row; i++ )
   {
       for( int j = 0; j < col; j++ )
       {
           output.setPixelVal( i, j, LEVEL );
       }
   }
   conncomp = 0;

   for( int i = 0; i < row; i++ )
   {
       for( int j = 0; j < col; j++ )
       {
           input.getPixelVal( i, j, value );
           output.getPixelVal( i, j, value_2 );
           
           if( value == LEVEL && value_2 == LEVEL )
           {
               conncomp++;
               label = conncomp;
               
               findcomponentBFS( input, output, i, j, label );
           }
       }
   }
   
   return conncomp;
}

/* computeComponents
Purpose: Compute how many objects are in an image
Notes: The two images passed into the function must already be sized
       the same
*/
int computeComponents_DFS_(  ImageType & input, ImageType & output, 
										SortedType<RegionType> listOfRegions, ImageType & Origonal)
{
   int row, col, LEVEL;
   int value, value_2;
   int conncomp, label;
   RegionType region;
   
   
   
   // retrieve image info
   input.getImageInfo( row, col, LEVEL );
   
   for( int i = 0; i < row; i++ )
   {
       for( int j = 0; j < col; j++ )
       {
           output.setPixelVal( i, j, LEVEL );
       }
   }
   conncomp = 0;
   
   // STORE VALUES TO CORRECT STUFF
   for( int i = 0; i < row; i++ )
   {
       for( int j = 0; j < col; j++ )
       {
           input.getPixelVal( i, j, value );
           output.getPixelVal( i, j, value_2 );
           
           if( value == LEVEL && value_2 == LEVEL )
           {
               conncomp++;
               label = conncomp;
              
               findcomponentDFS( input, output, i, j, label, region, Origonal );
               listOfRegions.InsertItem( region );
               region.print();
           }
       }
   }
   
   return conncomp;
}


void findcomponentBFS( ImageType & input, ImageType & output, int x, int y,
                         int label )
{
   int position_x, position_y;
   int row, col, LEVEL;
   int value, value_2;
   input.getImageInfo( row, col, LEVEL );
   
   // There's no real need for this assignment to go any larger than 6000
   queue Queue_x(6000);
   queue Queue_y(6000);
   
   Queue_x.makeEmpty();
   Queue_y.makeEmpty();
   
   Queue_x.Enqueue(x);
   Queue_y.Enqueue(y);
   
   while( !Queue_x.isEmpty())
   {
       Queue_x.Dequeue( position_x );
       Queue_y.Dequeue( position_y );
       
       output.setPixelVal( position_x, position_y, (label * 10) );
       
       // Enqueue every neighboring Pixel location
       for( int i = (position_x - 1); i <= (position_x + 1); i++ )
       {
           for( int j = (position_y - 1); j <= (position_y + 1); j++ )
           {
               if( i < row && i >= 0 && j < col && j >= 0 )
               {
                   input.getPixelVal(i, j, value);
                   output.getPixelVal(i, j, value_2);
                   if( value == LEVEL && value_2 == LEVEL )
                   {
                       output.setPixelVal( i, j, -1 );
                       
                       Queue_x.Enqueue(i);
                       Queue_y.Enqueue(j);
                   }
               }
           }
       }
   }
   
}


void findcomponentDFS(  ImageType & input, ImageType & output, int x, int y,
                            int label, RegionType& region, ImageType& Origonal )
{
	cout << "ARRIVE" << endl;
   int position_x, position_y;
   int row, col, LEVEL;
   int value, value_2;
   cout << "BEFORE PIXEL" << endl;
   PixelType temp;
   cout << "AFTER PIXEL" << endl;
   
   input.getImageInfo( row, col, LEVEL );
   cout << "AFTER GET INFO" << endl;
   // There's no real need for this assignment to go any larger than 6000
   stack Stack_x(60000);
   stack Stack_y(60000);
   cout << "AFTER STACK DECL." << endl;
   // Empty both stacks
   Stack_x.makeEmpty();
   Stack_y.makeEmpty();
   
   Stack_x.Push(x);
   Stack_y.Push(y);
   

   cout << "BEFORE LOOP" << endl;
   while( !Stack_x.isEmpty() )
   {
      // set pos_x and pos_y to coordinates
       Stack_x.Pop( position_x );
       Stack_y.Pop( position_y );
       
       output.setPixelVal( position_x, position_y, (label * 10) );
		
	   temp.x = position_x;
	   temp.y = position_y;
		cout << "BEFORE TEMP" << endl;
	   region.pixel_list.InsertItem( temp );
      cout << "INSERTTEMP" << endl;
       // Enqueue every neighboring Pixel location
       for( int i = (position_x - 1); i <= (position_x + 1) && i < row && i >=0;
                   i++ )
       {
           for( int j = (position_y - 1); j <= (position_y + 1) && j < col &&
                           j >= 0; j++ )
           {

                   input.getPixelVal(i, j, value);
                   output.getPixelVal(i, j, value_2);
                   if( value == LEVEL && value_2 == LEVEL )
                   {
                       output.setPixelVal( i, j, -1 );
                       
                       Stack_x.Push(i);
                       Stack_y.Push(j);
                   }
               
           }
       }
   }
   cout << "RENDER" << endl;
   RenderRegions( region, Origonal );
   cout << "END" << endl;
}

//////////////////////////// SUB MENU FUNCTIONS ////////////////////////////////
void displaySizes( ImageType &input, SortedType<RegionType> rhs, int small, int big )
{
	ImageType tempImage( input );
	RegionType cursor, min, max;
	PixelType temp;
	int N, M, Q;
	char out_name[20];
	
	min.setSize( small );
	max.setSize( big );
	
	// Set new image to all black
	input.getImageInfo( N, M, Q );
	
	for( int i = 0; i < N; i++ )
	{
		for( int j = 0; j < M; j++ )
		{
			tempImage.setPixelVal( i, j, 0 );
		}
	}
	
	rhs.ResetList();
	rhs.GetNextItem( cursor );
	
	// Get to node >= small
	while( cursor < min )
	{
		rhs.GetNextItem( cursor );
	}
	while( cursor <= max )
	{
		// WRITE REGION TO IMAGE
		cursor.writeToImage( input, tempImage );
		
		rhs.GetNextItem( cursor );
	}
	
	cout << "Enter desired file name: ";
   cin >> out_name;
   writeImage( out_name, tempImage );
	
}



void displayOrientations( ImageType &input, SortedType<RegionType> rhs, 
										int small, int big )
{
	ImageType tempImage( input );
	RegionType cursor, min, max;
	PixelType temp;
	int N, M, Q;
	char out_name[20];
	bool test;
	
	min.setOrientation( small );
	max.setOrientation( big );
	
	// Set new image to all black
	input.getImageInfo( N, M, Q );
	
	for( int i = 0; i < N; i++ )
	{
		for( int j = 0; j < M; j++ )
		{
			tempImage.setPixelVal( i, j, 0 );
		}
	}
	
	rhs.ResetList();
	rhs.GetNextItem( cursor );
	test = cursor.orCompare( cursor, min );
	
	// Get to node >= small
	while( test == true )
	{
		rhs.GetNextItem( cursor );
		test = cursor.orCompare( cursor, min );
	}
	
	test = cursor.orCompare( cursor, max );
	
	while( test == true )
	{
		// WRITE REGION TO IMAGE
		cursor.writeToImage( input, tempImage );
		
		rhs.GetNextItem( cursor );
		test = cursor.orCompare( cursor,max );
	}
	
	cursor.writeToImage( input, tempImage );
	
	cout << "Enter desired file name: ";
   cin >> out_name;
   writeImage( out_name, tempImage );
	
}



void displayEcc( ImageType &input, SortedType<RegionType> rhs, 
										int small, int big )
{
	ImageType tempImage( input );
	RegionType cursor, min, max;
	PixelType temp;
	int N, M, Q;
	char out_name[20];
	bool test;
	
	min.setEcc( small );
	max.setEcc( big );
	
	// Set new image to all black
	input.getImageInfo( N, M, Q );
	
	for( int i = 0; i < N; i++ )
	{
		for( int j = 0; j < M; j++ )
		{
			tempImage.setPixelVal( i, j, 0 );
		}
	}
	
	rhs.ResetList();
	rhs.GetNextItem( cursor );
	test = cursor.eccCompare( cursor, min );
	
	// Get to node >= small
	while( test == true )
	{
		rhs.GetNextItem( cursor );
		test = cursor.eccCompare( cursor, min );
	}
	
	test = cursor.eccCompare( cursor, max );
	
	while( test == true )
	{
		// WRITE REGION TO IMAGE
		cursor.writeToImage( input, tempImage );
		
		rhs.GetNextItem( cursor );
		test = cursor.eccCompare( cursor,max );
	}
	
	cursor.writeToImage( input, tempImage );
	
	cout << "Enter desired file name: ";
   cin >> out_name;
   writeImage( out_name, tempImage );
	
}



void displayInt( ImageType &input, SortedType<RegionType> rhs, 
										int small, int big )
{
	ImageType tempImage( input );
	RegionType cursor, min, max;
	PixelType temp;
	int N, M, Q;
	char out_name[20];
	bool test;
	
	min.setInt( small );
	max.setInt( big );
	
	// Set new image to all black
	input.getImageInfo( N, M, Q );
	
	for( int i = 0; i < N; i++ )
	{
		for( int j = 0; j < M; j++ )
		{
			tempImage.setPixelVal( i, j, 0 );
		}
	}
	
	rhs.ResetList();
	rhs.GetNextItem( cursor );
	test = cursor.intCompare( cursor, min );
	
	// Get to node >= small
	while( test == true )
	{
		rhs.GetNextItem( cursor );
		test = cursor.intCompare( cursor, min );
	}
	
	test = cursor.intCompare( cursor, max );
	
	while( test == true )
	{
		// WRITE REGION TO IMAGE
		cursor.writeToImage( input, tempImage );
		
		rhs.GetNextItem( cursor );
		test = cursor.intCompare( cursor,max );
	}
	
	cursor.writeToImage( input, tempImage );
	
	cout << "Enter desired file name: ";
   cin >> out_name;
   writeImage( out_name, tempImage );
	
}

void deleteSmallComponents( SortedType<RegionType> listOfRegions, int threshold)
{
	RegionType temp;
	RegionType test;
	
	test.setSize( threshold );
	cout << "get next" << endl;
	//listOfRegions.GetNextItem( temp );
	cout << "before loop" << endl;
	
	while( temp < test )
	{
		cout << "hit" << endl;
		listOfRegions.DeleteItem( temp );
		listOfRegions.GetNextItem( temp );
	}
	
}


////////////////////// Region Computations /////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void RenderRegions( RegionType& region, const ImageType& input )
{
	cout << "GETTING HERE" << endl;
	region.calcCentroid();
	cout << "centroid" << endl;
	region.calcEccentricity();
	cout << "ecc" << endl;
	region.calcOrientation();
	cout << "orient" << endl;
	//region.calcIntensity( input );
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
#endif









