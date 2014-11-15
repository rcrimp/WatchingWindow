#include <opencv2/opencv.hpp>

#include <sstream>
#include <string.h>
#include <iostream>

using namespace cv;
using namespace std;

//bgr
#define IND_BLUE 0
#define IND_GREEN 1
#define IND_RED 2

int main (int argc, char *argv[]) {
   if (argc != 2) {
      cout << "no image specified as an argument" << endl;
      return 1;
   }

   Mat in_image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
   if (!in_image.data){
      cout << "file error" << endl;
      return 1;
   }

   /* make these configurable via arguments */
   int border = 0;
   int sub_pixel_width = 1;
   int max_width = 1920;
   int max_height = 1080;
   Scalar border_col = Scalar(64, 64, 64);

   /* intermediary calculations */
   int pixel_size = 3 * sub_pixel_width; 
   int block_size = border + pixel_size; 
   int in_width = MIN(max_width / block_size, in_image.cols);
   int in_height = MIN(max_height / block_size, in_image.rows);
   
   Mat out_image(Size((in_width * block_size) + border, (in_height * block_size) + border), CV_8UC3);
   out_image.setTo(border_col);

   for (int x = 0; x < in_width; x++){
      for (int y = 0; y < in_height; y++){
         Vec3b colour = in_image.at<cv::Vec3b>(y, x);
        
         /* draw the red subpixel */
         rectangle(out_image, 
               Point((block_size * x) + border + (0 * sub_pixel_width), (block_size * y) + border), 
               Point((block_size * x) + border + (1 * sub_pixel_width) -1, (block_size * y) -1 + border + pixel_size),
               Scalar(0, 0, colour[IND_RED]), CV_FILLED);
         /* draw the green subpixel */
         rectangle(out_image,
               Point((block_size * x) + border + (1 * sub_pixel_width), (block_size * y) + border),
               Point((block_size * x) + border + (2 * sub_pixel_width) -1, (block_size * y) -1 + border + pixel_size),
               Scalar(0, colour[IND_GREEN], 0), CV_FILLED);
         /* draw the blue subpixel */
         rectangle(out_image, 
               Point((block_size * x) + border + (2 * sub_pixel_width), (block_size * y) + border),
               Point((block_size * x) + border + (3 * sub_pixel_width) -1, (block_size * y) -1 + border + pixel_size),
               Scalar(colour[IND_BLUE], 0, 0), CV_FILLED);   
      }
   }

   imwrite("out.png", out_image);
   namedWindow("Sub Pixel View");
   imshow("Sub Pixel View", out_image);

   namedWindow("Original");
   imshow("Original", in_image(Rect(0, 0, in_width, in_height)));
   
   waitKey();
   return 0;
}
