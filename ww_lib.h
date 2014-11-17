#include <opencv2/opencv.hpp>

namespace watching_window
{
   /* sub pixel indexes B G R */
   static const int BLUE = 0;
   static const int GREEN = 1;
   static const int RED = 2;

   /* common colours */
   static const cv::Scalar C_RED = cv::Scalar(0,0,255);
   static const cv::Scalar C_BLUE = cv::Scalar(255,0,0);
   static const cv::Scalar C_GREEN = cv::Scalar(0,255,0);
   static const cv::Scalar C_CYAN = cv::Scalar(255,255,0);
   static const cv::Scalar C_MAGENTA = cv::Scalar(255,0,255);
   static const cv::Scalar C_YELLOW = cv::Scalar(0,255,255);
   static const cv::Scalar C_WHITE = cv::Scalar(255,255,255);
   static const cv::Scalar C_BLACK = cv::Scalar(0,0,0);

   /* 
    * sets the specified subpixel to the intensity specified
    */
   void set_sub_pixel(cv::Mat image, int sub_pixel_x, int pixel_y, int intensity);

   /*
    * bresnhams line drawing algorithm drawing sub pixel line
    *
    * set_sub_line(image, 0.0f, 0.0f, 100.0f, 100.0f, 255)
    */
   void set_sub_line(cv::Mat i, float x1, float y1, float x2, float y2, int intensity);

   /* draws a view needs alot of work lol */
   void draw_view(cv::Mat image, int view, const int HEIGHT, const int WIDTH);
   void draw_views(cv::Mat[], cv::Mat);

   /* demonstrates the edge artifacting */
   void edge_artifacting(cv::Mat image, const int HEIGHT, const int WIDTH);
   void edge_artifacting2(cv::Mat image, const int HEIGHT, const int WIDTH);

   /* LINES */
   void draw_basic_lines(cv::Mat image, const int HEIGHT, const int WIDTH);

   /* 
    * SLANT
    * Draws a line with a slope of -6
    */
   void draw_slants(cv::Mat i, const int HEIGHT, int x, cv::Scalar colours[]);

   /* 
    * SLANTS
    * Indicates the slope of the lenticules and the order of the LED subpixels
    */
   void draw_slants(cv::Mat i, const int WIDTH, const int HEIGHT, const int spacing);
}
