#include <opencv2/opencv.hpp>

#define WIDTH 1920 
#define HEIGHT 1080
//bgr
#define RED cv::Scalar(0,0,255)
#define BLUE cv::Scalar(255,0,0)
#define GREEN cv::Scalar(0,255,0)
#define WHITE cv::Scalar(255,255,255)
#define BLACK cv::Scalar(0,0,0)

int main (int arg, char *argv[]) {
   cv::Mat image(cv::Size(WIDTH, HEIGHT), CV_8UC3);

   image.setTo(WHITE);
   //cv::circle(image, cv::Point(320,240), 200, cv::Scalar(255,0,0), -1);
   //cv::circle(image, cv::Point(320,240), 100, RED, -1);

   int view_index = 2;
   int even_offset = view_index;
   int odd_offset = 5 + view_index;
   cv::Scalar col;

   /*for(int y = 0; y < HEIGHT; y++){
      even_offset %= 9;
      odd_offset %= 9;
      int px = (y % 2 ==0) ? even_offset++ : odd_offset++;
      

      for(px; px < WIDTH * 3; px+=9){
         
         if (y%3 == 0)
            col = RED;
         else if ((y+1)%3 ==0)
            continue;//col = GREEN;
         else 
            continue;//col = BLUE;
         
         cv::line(image, cv::Point(px/3,y), cv::Point(px/3,y), col);
      }
   }*/
   /*
      int x = 100;
      int y = 300;
      cv::Vec3b colour = image.at<cv::Vec3b>(y,x)
      colour[0] = 100;
      colour[1] = 200;
      image.at<cv::Vec3b>(y,x) = colour;
    */



   cv::imwrite("test.png", image);

   cv::namedWindow("Display");
   cv::imshow("Display", image);


   cv::waitKey();



   return 0;
}
