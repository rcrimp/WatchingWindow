#include <opencv2/opencv.hpp>
#include "ww_lib.h"

#include <sstream>
#include <string.h>

#define WIDTH 1920 
#define HEIGHT 1080
#define SP_WIDTH WIDTH*3

using namespace watching_window;

int main (int arg, char *argv[]) {
   cv::Mat image(cv::Size(WIDTH, HEIGHT), CV_8UC3);
   image.setTo(C_BLACK);

   /* use argv and argc properly */

//  set_sub_pixel(image, 10, 10, 255);
//  set_sub_line(image, 0, 0, 100, 100, 255);
//  edge_artifacting2(image, HEIGHT, WIDTH);
//  draw_basic_lines(image, HEIGHT, WIDTH);
//  draw_slants(image, WIDTH, HEIGHT, 29);
 
//   cv::Mat image_white(cv::Size(640, 360), CV_8UC3);
//   cv::Mat image_black(cv::Size(640, 360), CV_8UC3);
//   image_white.setTo(C_WHITE);
//   image_black.setTo(C_BLACK);

   cv::Mat in_images[9] = {
      cv::imread(argv[1], /*"in_images0/0.png"*/ CV_LOAD_IMAGE_COLOR),
      cv::imread(argv[2], CV_LOAD_IMAGE_COLOR),
      cv::imread(argv[3], CV_LOAD_IMAGE_COLOR),
      cv::imread(argv[4], CV_LOAD_IMAGE_COLOR),
      cv::imread(argv[5], CV_LOAD_IMAGE_COLOR),
      cv::imread(argv[6], CV_LOAD_IMAGE_COLOR),
      cv::imread(argv[7], CV_LOAD_IMAGE_COLOR),
      cv::imread(argv[8], CV_LOAD_IMAGE_COLOR),
      cv::imread(argv[9], CV_LOAD_IMAGE_COLOR)
   };
   draw_views(in_images, image);

//   for (int i = 0; i < 9; i++){
//      std::stringstream strs;
//      strs << i << ".png";
//      std::string temp_str = strs.str();
//      const char* pchar = (char*) temp_str.c_str();
//
//      image.setTo(C_BLACK);
//      draw_view(image, i, HEIGHT, WIDTH);
//      
//      cv::imwrite( pchar , image);
//      cv::namedWindow("Display");
//      cv::imshow("Display", image);
//      cv::waitKey();
//   }

   cv::imwrite("test.png", image);
   
   cv::namedWindow("Display", CV_WINDOW_NORMAL);
   /* Fullscreen crashes on OSX */
//   cv::setWindowProperty("Display", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
   cv::imshow("Display", image);
   cv::waitKey();
   return 0;
}
