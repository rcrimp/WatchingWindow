#include <opencv2/opencv.hpp>

#include <sstream>
#include <string.h>

#define ASPECT_RATIO (640.0f/360.0f)
#define WIDTH 640
#define HEIGHT 360

//argv[1] is the source image
//argv[2] is the target image
int main (int arg, char *argv[]) {
   //cv::Mat image(cv::Size(WIDTH, HEIGHT), CV_8UC3);
   //image.setTo(C_BLACK);

   cv::Mat in_image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
   cv::Mat scaled_image;
      
   double in_aspect_ratio = in_image.cols / in_image.rows;
   double scale_factor;

   cv::Rect out_rect(0, 0, WIDTH, HEIGHT); 

   if (in_aspect_ratio >= ASPECT_RATIO){
      scale_factor = (double) HEIGHT / in_image.rows; 
   } else {
      scale_factor = (double) WIDTH / in_image.cols; 
   }
  
   cv::resize(in_image, scaled_image, cv::Size(), scale_factor, scale_factor, cv::INTER_CUBIC);

   cv::Mat cropped = scaled_image(out_rect);

   td::stringstream strs; 
      strs << argv[1] << ".png"; 
         std::string temp_str = strs.str(); 
            const char* pchar = (char*) temp_str.c_str(); 
   
   cv::imwrite(pchar, cropped);
   return 0;
}
