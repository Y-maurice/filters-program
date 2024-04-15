/* 
SECTION : 20
TEAM MEMBERS:

=> NAME: Monica rafaat adeb selem
   ID : 20230430
   The parts she did: filters ( black & white , flipping , crop , resize , Bonus(infrared , purple))
   EMAIL : monica.rafaat.1310@gmail.com
==========================================
=> NAME: Mary isaac hanna
   ID : 20230301
   The parts she did: filters ( grey, lighten & darken, edge detect , merge )
   EMAIL : romaishak@gmail.com
==========================================
=>NAME: youssef moris kamal
  ID : 20230514
  The parts he did: filters ( invert , rotate , frame , blur , Bonus(sunlight)) & the whole menu 
  EMAIL : youssefmoris10@gmail.com
===========================================
=>the figuer of the functions :

https://drive.google.com/file/d/1mqbOwNmN8shzFuHdiCqRMg4OHg60fEiK/view?usp=drive_link

=>>> V 2.0 of this project have some modifications :
=>  used switch cases in some parts instead of if conditions.
=> changed the functions to return Image instead of void.
=> fixed the problem unloading the saved image in rotation 270 filter. 
=> made a validation in the inner options of some filters like (flipping , rotate , lighten & darken , merge ).
=>added the functions of new filters(crop,resize,infrared,purple,frame,blur,sunlight,edge detect,merge)
*/

#include"Image_Class.h"
#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
#include<regex>
using namespace std;



//==============function to save the photo and the choice of the exetention==============>
   void saveph(Image x){
    string input;
    regex validInputSaving("[12]"); 
    regex validInputExe("[1234]");
    // regex method to validate both input of exetension and saving choice
    int exe_choice;
    int saving_choice;
    string new_name;

    do {
        cout << "=> for saving it , enter 1" << endl
             << "=> to continue , enter 2" << endl;
        cin >> input;

        if (cin.fail() || !regex_match(input, validInputSaving)) {
            cin.clear(); // clear the error 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            // ignore the bad input
            cout << "Invalid choice. Please enter 1 or 2."<<endl;
        } else {
            saving_choice = stoi(input); // convert string to int
            break; // exit the loop once a valid input is entered
        }
            
    } while(true);


    if(saving_choice == 1){
        


         cout << "enter the new name" << endl;
         cin>>new_name;
         cout << "enter the exetention you want" << endl
              << "=> jpg => 1" << endl
              << "=> jpeg => 2" << endl
              << "=> png => 3" << endl
              << "=> bmp => 4" << endl;

         do {
             cin >> input;

             if (cin.fail() || !regex_match(input, validInputExe)) {
                 cin.clear(); // clear the error 
                 cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                 // ignore the bad input
                 cout << "Invalid choice , Please enter 1, 2, 3, or 4"<<endl;
             } else {
                 exe_choice = stoi(input); // convert string to int
                 break; // exit the loop once a valid input is entered
             }
         } while(true);
         do{
         switch (exe_choice){
            case 1 :
            new_name.append(".jpg");
            break;
            case 2 :
            new_name.append(".jpeg");
            break;
            case 3 :
            new_name.append(".png");
            break;
            case 4 : 
            new_name.append(".bmp");
            break;
         }
         
         cout<<"===== image saved successfully ====="<<endl;
         x.saveImage(new_name);
         break;

         

   }while(true);
    }
   }
   
//=================================== Invert ====================================>

/*it works by subtracting the original value of R G B from 255.*/

Image invert(Image x){
    

for(int i = 0 ; i < x.width ; i++){

    for(int j = 0 ; j < x.height ; j++){

     x(i,j,0) = 255 - x(i,j,0);
     x(i,j,1) = 255 - x(i,j,1);
     x(i,j,2) = 255 - x(i,j,2);
    }
}
return x;
} 

//=================================== B & W ====================================>

/*.  this filter turns color image into black and white image by converting 
every pixel with a value greater than 127 into a pixel with a value of 255,
 and converting every pixel with a value less than 127 into a pixel with a value of 0. */

Image B_and_W(Image x){

    for(int i=0;i<x.width;i++){

        for(int j = 0; j< x.height; j++ ){

            if(x(i,j,0)+x(i,j,1)+x(i,j,2) > 127){
                x(i,j,0)=225;
                x(i,j,1)=225;
                x(i,j,2)=225;
            }
            else{
                x(i,j,0)=0;
                x(i,j,1)=0;
                x(i,j,2)=0;

            }
        }
    }cout<<endl;
  return x; 
}

//=================================== Flipping ====================================>

/* this filter flipping the image over the y-axis or x-axis this is based
 user's choice by subtracting 1 from the actual width (height) of the image
  and subtracting the pixel value from them (width(height)-1-i(j) */

Image flipping(Image x){
int fliping_choice;
string input;
regex validflip("[12]");
do {
    cout<<"for flipping vertically , enter 1"<<endl
    <<"for flipping horizontally , enter 2"<<endl;
    cin>>input;
  if(cin.fail() || !regex_match(input,validflip)){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Invalid choice. Please enter 1 or 2."<<endl;
  }else{
    fliping_choice = stoi(input);
    break;
  }
}while (true);
  
  if(fliping_choice==1){

    Image flipped(x.width, x.height);

    for(int i=0;i<x.width;i++){

        for(int j = 0; j< x.height; j++ ){
            
            for(int k=0; k<3 ; k++){

                flipped(i, j, k) = x(i, x.height - 1 - j, k);
               
                
            }

        }
    }
return flipped ;
}else if (fliping_choice==2){

     
       
    Image y(x.width, x.height);
    for(int i=0;i<x.width;i++){
        for(int j = 0; j< x.height; j++ ){
            for(int k=0; k<3 ; k++){
                y(i, j, k) = x(x.width - 1 - i, j, k);
            }
        }
    }
return y;
}
}

//=================================== Grey ====================================>

/*this filter turn the color image into grey one by converting every pixel 
to pixel contains the average of RGB in Red , Green ,and Blue.*/

Image Grey(Image x){

    for (int i=0 ; i<x.width ; i++ ) {

        for (int j=0 ; j<x.height ; j++) {

            int avr = ((x(i, j, 0) + x(i, j, 1) + x(i, j, 2)) / 3);
                x(i, j, 0) = avr;
                x(i, j, 1) = avr;
                x(i, j, 2) = avr;
        }
    }

   return x;
}

//==================================== //Darken & Lighten ====================================>

/*this filter turn the image into lighten or darken one by converting every pixel to more lighten
 one (By rounding the RGB value to 255 ) or to more darken one (By rounding the RGB value to 0).*/

Image darken_and_lighten(Image x){
string input ;
int choice;
regex validinput("[12]");
do{ 
    cout << "for Lighten filter , enter 1" << endl;
    cout << "for Darken filter ,  enter 2" << endl;
    cin >> input;

    if(cin.fail() || !regex_match(input , validinput)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid choice. Please enter 1 or 2."<<endl;
    }else{
        choice = stoi(input);
        break;
    }
}while(true) ;   


    if (choice == 1) {

        for (int i = 0; i < x.width; i++) {

            for (int j = 0; j < x.height; j++) {

                for (int k = 0; k < 3; k++) {
                    int value;
                    value = 1.5 * x(i, j, k);


                    if (value > 255)
                    {
                        x(i, j, k) = 255;
                    }
                    else {
                        x(i, j, k) = value;
                    }
                }

            }
        }
        return x;
    }
    else {
        for (int i = 0; i < x.width; i++) {

            for (int j = 0; j < x.height; j++) {

                x(i, j, 0) = 0.5 * x(i, j, 0);
                x(i, j, 1) = 0.5 * x(i, j, 1);
                x(i, j, 2) = 0.5 * x(i, j, 2);


            }
        }

        return x;
}

}

 //==================================== Rotate ====================================>

/*to rotate the photo by 90 , 180 or 270 degree*/

Image rotate(Image x){
Image xr;
Image x270;
int rotation_choice;
string input;
regex validrotate("[123]") ;
do{
  cout<<"to rotate 90° , enter 1"<<endl
  <<"to rotate 180° ,enter 2"<<endl
  <<"to rotate 270° ,enter 3"<<endl;
  cin>>input;
 if(cin.fail() || !regex_match(input, validrotate)){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Invalid choice. Please enter 1, 2 or 3"<<endl;
 }else{
    rotation_choice = stoi(input);
    break;
 }
}while(true) ;



// 90
if(rotation_choice==1){
  Image xr(x.height,x.width);
  for(int i =0 ; i < x.height ;i++){

    for(int j  = 0 ; j < x.width ; j++){

      for(int k =0 ; k<3 ; k++){

        xr(x.height -1-i,j,k) = x(j,i,k);
      }
    }
    
  }
return xr;
}
//180
 else if(rotation_choice==2){
    Image xr(x.width,x.height);
    for(int i =0 ;i<x.width ; i++){

        for(int j =0 ; j<x.height;j++){

            for(int k =0; k<3 ;k++){

                xr(x.width-1-i,x.height-1-j,k) = x(i,j,k);
            }
        }
    }
return xr;
}
//270
else if(rotation_choice==3){
    Image xr(x.height,x.width);
  for(int i = 0 ; i < x.width ;i++){

    for(int j  = 0 ; j < x.height ; j++){

      for(int k = 0 ; k < 3 ; k++){

        xr(j,i,k) = x(i,j,k);
      }
    }
    
  }
return xr;
}

}

//==================================== frame ====================================>

/*This applies a frame effect to an image, The frame consists of two parts: a blue
 outer frame and a white inner frame,The function first calculates the width of the 
 frames based on a ratio of the image's dimensions.*/

Image frame(Image x){
// Define the ratio for the frame as a smaller percentage of the image's dimensions
//so the images with small width and height won't be all covered by the frame
     double ratio = 0.03; 

    int blue_frame = x.height * ratio;
    int White_frame = x.width * ratio;

    // Check if the frame dimensions are too large for smaller images
    if (blue_frame > x.height / 2) {
        blue_frame = x.height / 2;
    }
    if (White_frame > x.width / 2) {
        White_frame = x.width / 2;
    }

    for (int i = 0; i < x.width; i++){
        for(int j = 0; j < x.height; j++){
            if(i < blue_frame || i >= x.width - blue_frame || j < blue_frame || j >= x.height - blue_frame){
                x(i,j,0) = 0;
                x(i,j,1) = 0;
                x(i,j,2) = 255;
            } else if (i < White_frame || i >= x.width - White_frame || j < White_frame || j >= x.height - White_frame){
                x(i,j,0) = 255;
                x(i,j,1) = 255;
                x(i,j,2) = 255;
            }
        }
    }
    return x;
}

//==================================== crop ====================================>

/* This filter crops the image using the starting point (starting from 
the top left corner) and then takes the dimensions from the user */

Image crop(Image x){
    int X, Y, W, H;
    char bracket,astr,comma;
    string point ,dimensions;
    cout<<"enter point as (x,y) upper left corner of the part to keep: \n";
    getline(cin,point);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    cout<<"enter the dimensions as W*H: \n";
    getline(cin,dimensions);

 
    while (true){

    char bracket,astr,comma;
    stringstream ssCorner(point);
    stringstream ssDimensions(dimensions);
    ssCorner >> bracket >> X >> comma >> Y >> bracket;
    ssDimensions >> W >> astr>> H;

    if(W > x.width || H > x.height){
        cout<<endl<<"this dimendion is out of the bounders of the image,"<<endl
        <<"please re enter it and make the W < "<<x.width<<endl
        <<"and the H < "<<x.height<<endl; 
         cout<<"enter the dimensions as W*H: \n";
         getline(cin,dimensions);
     
         

    }else{

        break;
    }

    }
    Image l (W,H);

    // Copy the image
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            for (int k = 0; k < 3; k++) {
                l.setPixel(j, i, k, x.getPixel(X+ j, Y + i, k));
            }
        }
    }


return l;
}

//==================================== infrared ====================================>

/*This filter makes the image look like it is under infrared radiation 
by making the red color in each pixel full (equal to 225). */

Image infrared(Image x) {
   
    for(int i=0;i<x.width;i++){
        for(int j = 0; j< x.height; j++ ){
            x(i,j,0)=255;
            x(i,j,1)=255-x(i,j,1);
            x(i,j,2)=255-x(i,j,2);

        }
    }
return x;
}

//==================================== resize ====================================>

/* This filter changes the size of the image and can enlarge or reduce 
it according to the dimensions that the user wants */

Image resize (Image x){
    string dimensions;
    cout<<"enter new dimensions as W*H: \n";
    getline(cin,dimensions);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int X, Y, W, H;
    char astr;
    stringstream ssDimensions(dimensions);
    ssDimensions >> W >> astr>> H;

    float Sw = static_cast<float>(x.width)/static_cast<float>(W) ;
    float Sh = static_cast<float>(x.height)/static_cast<float>(H) ;

    Image l (W,H);
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            for (int k = 0; k < 3; ++k) {
                int origX = static_cast<int>(j * Sw);
                int origY = static_cast<int>(i * Sh);
                l.setPixel(j, i, k, x.getPixel(origX, origY, k));
            }
        }
    }
   return l;
    
}

//==================================== purple ====================================>

/* This filter depends on showing the image in a violet color, and this is done by 
changing the percentage of green color and leaving red and blue as they are, because 
violet is a mixture between red and blue. */

Image purple(Image x) {
    for(int i=0;i<x.width;i++){
        for(int j = 0; j< x.height; j++ ){
            x(i,j,1)*=0.4;
        }
    }
return x;
}

//==================================== plur ====================================>

Image blur(Image x){
    
Image result = x;

    // Define the degree of blurring
int degree = 12; /*responsible for the degree of the blur as it represents the number
 of the pixles that the average of them will be taken and put it in each filter( so it
  determines the size of the area around each  pixel that is used for the blur calculation)
  (here it = 12 this means a matrix from -12 to 12 means a 13*13 matrix), a large degrre value
   will result in stronger blur effect */
for (int i = 0; i < x.width; i++){
    for(int j = 0; j < x.height; j++){
         for(int k = 0; k < x.channels; k++){
            int sum = 0;
            int count = 0;
            for(int ki = -degree; ki <= degree; ki++){
                for(int kj = -degree; kj <= degree; kj++){
                    int new_i = i + ki;
                    int new_j = j + kj;
                    if (new_i >= 0 && new_i < x.width && new_j >= 0 && new_j < x.height) {
                         //condition to check if it still in the image
                        sum += x(new_i, new_j, k);
                         count++;
                    }
                }
            }
            result(i, j, k) = sum / count; //putting the avg value in each pixel
        }
    }
}
    
 return result;
}

//==================================== sunlight ====================================>

/* It works by manipulating the intensity of the red, green, and blue color channels 
in each pixel of the image but with different ratio for each channel (red and greeen
increased by 30% blue decreased by 10%) .*/

Image sunlight(Image x) {
    

    for (int i = 0; i < x.width; i++) {
        for (int j = 0; j < x.height; j++) {

            int nRed = x(i, j, 0);
            nRed *= 1.3; 
            if (nRed > 255) {
                nRed = 255;
            }

            int nGreen = x(i, j, 1);
            nGreen *= 1.3; 
            if (nGreen > 255) {
                nGreen = 255;
            }

            int nBlue = x(i, j, 2);
            nBlue *= 0.9; 
            if (nBlue > 255) {
                nBlue = 255;
            }
            else if (nBlue < 0) {
                nBlue = 0;
            }

            x(i, j, 0) = nRed;
            x(i, j, 1) = nGreen;
            x(i, j, 2) = nBlue;
        }
    }
return x;
}


//==================================== edge detect ====================================>

/* This code applies an edge detection filter to an image. It first converts the image
to black and white based on a threshold. Then, it calculates the horizontal and vertical
gradients. If both gradients are above a certain threshold, the pixel is considered an 
edge and is colored black, otherwise it's colored white.*/


Image edge_detect(Image x){

        for (int i = 0; i < x.width; i++) {
            for (int j = 0; j < x.height; j++) {

                if (x(i, j, 0) + x(i, j, 1) + x(i, j, 2) > 127) {
                    x(i, j, 0) = 225;
                    x(i, j, 1) = 225;
                    x(i, j, 2) = 225;
                }
                else {
                    x(i, j, 0) = 0;
                    x(i, j, 1) = 0;
                    x(i, j, 2) = 0;

                }
            }
        }
        
        for (int i = 0; i < x.width-1; i++) {
            for (int j = 0; j < x.height-1; j++) {

                int h = abs(x(i, j, 0) - x(i, j + 1, 0));
                int v = abs(x(i, j, 0) - x(i + 1, j, 0));
                
                if (h > 127 && v > 127) {

                    for (int k = 0; k < 3; k++) {
                        x(i, j, k) = 0;

                    }
                }
                else {

                    for (int k = 0; k < 3; k++) {
                        x(i, j, k) = 255;

                    }

                }
   
            }
        }

   return x;     
}

//==================================== merge ====================================>

Image merge (Image x ){
string imageyname;
cout<<"enter the name of the other image ==> [name.exe]"<<endl;
cin>>imageyname;
cin.ignore();   
Image y(imageyname);
int choice;
string input;
cin>>input;
regex validchoice("[12]") ;
do{
     cout << "please choose if you want to crop images or resize them" << endl;
    cout << "to crop choose >>1" << endl;
    cout << "to resize choose >>2" << endl;

     cin>>input;
 if(cin.fail() || !regex_match(input, validchoice)){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Invalid choice. Please enter 1 or 2"<<endl;
 }else{
    choice = stoi(input);
    break;
 }
}while(true) ;

    float max_h = max(x.height, y.height);
    float max_w = max(x.width, y.width);
    float min_h = min(x.height, y.height);
    float min_w = min(x.width, y.width);


    if (choice == 1) {
        Image a(min_w, min_h);
        Image b(min_w, min_h);
        Image c(min_w, min_h);

        for (int i = 0; i < a.width; i++) {
            for (int j = 0; j < a.height; j++) {
                for (int k = 0; k < 3; k++) {

                    a(i, j, k) = x(i, j, k);
                    b(i, j, k) = y(i, j, k);
                }
            }
        }

        for (int i = 0; i < c.width; i++) {
            for (int j = 0; j < c.height; j++) {
                for (int k = 0; k < 3; k++) {

                    c(i, j, k) = (a(i, j, k) + b(i, j, k)) / 2;

                }
            }
        }
        return c;

    }



    if (choice == 2) {

        Image a(max_w, max_h);
        Image b(max_w, max_h);
        Image c(max_w, max_h);

        float ratio_w_a = (x.width) / (max_w);
        float ratio_h_a = (x.height) / (max_h);
        float ratio_w_b = (y.width) / (max_w);
        float ratio_h_b = (y.height) / (max_h);

        for (int i = 0; i < a.width; i++) {
            for (int j = 0; j < a.height; j++) {
                for (int k = 0; k < 3; k++) {

                    double origX = j * ratio_h_a;
                    double origY = i * ratio_w_a;
                    a.setPixel(i, j, k, x.getPixel(origY, origX, k));
                    double origZ = j * ratio_h_b;
                    double origQ = i * ratio_w_b;
                    b.setPixel(i, j, k, y.getPixel(origQ, origZ, k));

                }
            }
        }

        for (int i = 0; i < c.width; i++) {
            for (int j = 0; j < c.height; j++) {
                for (int k = 0; k < 3; k++) {

                    c(i, j, k) = (a(i, j, k) + b(i, j, k)) / 2;

                }
            }
        }
        return c;

}

}


int main(){

string input;
regex validInputImage("[01]"); 
regex validInputFilter("([0-9]|10|11|12|13|14|15)");//the valid inputs (from 0 to 12)
// regex method to validate both the input of the filter and image
int image_choice;
Image x;
int filter_choice;
string image_name;

    do
    {
   
        do {
              cout << endl << "===== welcome in our filters program =====" << endl
                   << "=> for processing on an image , enter 1" <<endl
                   << "=> To Exit , enter 0" << endl;
            cin >> input;

            if (cin.fail() || !regex_match(input, validInputImage)) {
                cin.clear(); // clear the error 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the bad input
                cout << "Invalid choice , Please enter 1 or 0"<<endl;
            } else {
                image_choice = stoi(input); // convert string to int
                break; // exit the loop once a valid input is entered
            }
        } while(true);

        if(image_choice == 1){
            while(true) {
                cout << "Enter your image name ==> [name.exe] " << endl;
                cin >> image_name;

                // ifstream is a function for checking the ability to open a file (checking if the image is in the file)
                ifstream file(image_name.c_str());

                // If the file was successfully opened (that means that the image already exists in the files), break the loop as good() will return true
                if(file.good()) {
                    file.close();
                    break;
                } else  {
                    // If the file could not be opened, print an error message and ask for input again
                    cout << "This photo isn't in this file. Please enter a valid file name."<<endl;
                }
            }

            x.loadNewImage(image_name);
        } else if(image_choice == 0){
            cout << "===== thank you for using our program =====" << endl;
            break;
        }
    

        do {
            cout << endl << "===== choose the filter you want =====" << endl
                 <<"Invert => 1" << endl
                 <<"B & W  => 2" << endl
                 <<"Flip   => 3" << endl
                 <<"Grey   => 4" << endl
                 <<"Darken & lighten => 5"<<endl
                 <<"Rotation => 6"<<endl
                 <<"Frame => 7"<<endl
                 <<"Crop => 8"<<endl
                 <<"Infrared => 9"<<endl
                 <<"Purple => 10"<<endl
                 <<"Resize => 11"<<endl
                 <<"Blur => 12"<<endl
                 <<"Sunlight => 13"<<endl
                 <<"Edge detect => 14"<<endl
                 <<"Merge => 15"<<endl
                 <<"Exit   => 0" << endl;
            cin >> input;

            if (cin.fail() || !regex_match(input, validInputFilter)) {
                cin.clear(); // clear the error 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the bad input
                cout << "Invalid choice. Please enter a valid choice."<<endl;
            } else {
                filter_choice = stoi(input); // convert string to int
                break; // exit the loop once a valid input is entered
            }
        } while(true);

         if(filter_choice==0){
            cout << "===== thank you for using our program =====" << endl;
            break;
          }

        switch (filter_choice){
            
            case 1 :
            saveph(invert(x));
            break;

            case 2 :
            saveph(B_and_W(x));
            break;
            
            case 3 :
           saveph(flipping(x));
            break;

            case 4 :
           saveph(Grey(x));
            break;

            case 5 :
            saveph(darken_and_lighten(x));
            break;

            case 6 :
           saveph(rotate(x));
            break;

            case 7 :
            saveph(frame(x));
            break;

            case 8 :
            saveph(crop(x));
            break;

            case 9 :
            saveph(infrared(x));
            break;

            case 10 :
            saveph(purple(x));
            break;

            case 11 :
            saveph(resize(x));
            break;

            case 12 :
            cout<<"==== this might take a few seconds , please wait ===="<<endl;
            saveph(blur(x));
            break;

            case 13 :
           saveph(sunlight(x));
            break;

            case 14 :
            saveph(edge_detect(x));
            break;

            case 15 :
            saveph(merge(x));
            break;
        }
     
          
    }while(true);
    return 0;
}