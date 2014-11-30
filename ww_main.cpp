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
   cv::Mat in_image = cv::imread("9_view_test.png", CV_LOAD_IMAGE_COLOR);
   image.setTo(C_BLACK);
   
   cv::Mat in_images[9] = {
      cv::Mat(in_image, cv::Rect(   0,   0, 640, 360)),
      cv::Mat(in_image, cv::Rect( 640,   0, 640, 360)),
      cv::Mat(in_image, cv::Rect(1280,   0, 640, 360)),
      cv::Mat(in_image, cv::Rect(   0, 360, 640, 360)),
      cv::Mat(in_image, cv::Rect( 640, 360, 640, 360)),
      cv::Mat(in_image, cv::Rect(1280, 360, 640, 360)),
      cv::Mat(in_image, cv::Rect(   0, 720, 640, 360)),
      cv::Mat(in_image, cv::Rect( 640, 720, 640, 360)),
      cv::Mat(in_image, cv::Rect(1280, 720, 640, 360))

   };
   cv::Mat in_images_shuffled[9] = {
      in_images[0],
      in_images[1],
      in_images[2],
      in_images[3],
      in_images[4],
      in_images[5],
      in_images[6],
      in_images[7],
      in_images[8],
   };
   draw_views(in_images_shuffled, image);

//   cv::Mat in_images[9] = {
//      cv::imread("0.png", CV_LOAD_IMAGE_COLOR),
//      cv::imread("1.png", CV_LOAD_IMAGE_COLOR),
//      cv::imread("2.png", CV_LOAD_IMAGE_COLOR),
//      cv::imread("3.png", CV_LOAD_IMAGE_COLOR),
//      cv::imread("4.png", CV_LOAD_IMAGE_COLOR),
//      cv::imread("5.png", CV_LOAD_IMAGE_COLOR),
//      cv::imread("6.png", CV_LOAD_IMAGE_COLOR),
//      cv::imread("7.png", CV_LOAD_IMAGE_COLOR),
//      cv::imread("8.png", CV_LOAD_IMAGE_COLOR)
//   };
//   draw_views(in_images, image);
   cv::imwrite("test.png", image);

   cv::namedWindow("Display", CV_WINDOW_NORMAL);
   /* Fullscreen crashes on OSX */
   //   cv::setWindowProperty("Display", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
   cv::imshow("Display", image);
   cv::waitKey();
   return 0;
}
