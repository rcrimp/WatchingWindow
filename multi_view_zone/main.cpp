#include <opencv2/opencv.hpp>

#include <sstream>
#include <string.h>

int main (int arg, char *argv[]) {
   const float scale = 3.0f;
   
   // 3D display properties
   const int NUM_VIEWS = 9;
   const float DISPLAY_WIDTH = 930.0f / scale; // 310
   const float PROJECTION_WIDTH = 561.0f / scale; // 187
   const float OPTIMAL_DISTANCE = 3000.0f / scale; // 1000

   const int IMG_WIDTH = 1920;
   const int IMG_HEIGHT = OPTIMAL_DISTANCE;

   const cv::Point display_left (IMG_WIDTH/2.0f - DISPLAY_WIDTH/2.0f, IMG_HEIGHT-1.0f);
   const cv::Point display_right(IMG_WIDTH/2.0f + DISPLAY_WIDTH/2.0f, IMG_HEIGHT-1.0f);

   const int view_width = PROJECTION_WIDTH / NUM_VIEWS;

   const cv::Scalar colours[9] = {
      cv::Scalar(255, 0, 0),
      cv::Scalar(0, 255, 0),
      cv::Scalar(0, 0, 255),
      cv::Scalar(255, 255, 0),
      cv::Scalar(0, 255, 255),
      cv::Scalar(255, 0, 255),
      cv::Scalar(128, 128, 128),
      cv::Scalar(255, 0, 128),
      cv::Scalar(255, 128, 0)
   };

   cv::Mat img(cv::Size(IMG_WIDTH, IMG_HEIGHT), CV_8UC3);
   img.setTo(cv::Scalar(0, 0, 0));

   const int TOTAL_REGIONS = 41;

   float start_x = IMG_WIDTH/2.0f - PROJECTION_WIDTH/2.0f - PROJECTION_WIDTH * ((TOTAL_REGIONS-1.0f)/2.0f);
   for (int i = 0; i < TOTAL_REGIONS; i++){
      for (int v = 0; v < NUM_VIEWS; v++){
         cv::Point quad_points[4] = {
            cv::Point(start_x + (v * PROJECTION_WIDTH) / NUM_VIEWS, 0),
            cv::Point(start_x + ((v+1) * PROJECTION_WIDTH) / NUM_VIEWS, 0),
            display_right,
            display_left
         };
         cv::line(img, quad_points[0], display_left, colours[v]);
         cv::line(img, quad_points[1], display_right, colours[v]);
//         cv::fillConvexPoly(img, quad_points, 4, colours[v], CV_AA); 
      }
      start_x += PROJECTION_WIDTH;
   };

   cv::imwrite("view_zones.png", img);
   cv::namedWindow("Display", CV_WINDOW_NORMAL);
   cv::imshow("Display", img);
   cv::waitKey();
   return 0;
}
