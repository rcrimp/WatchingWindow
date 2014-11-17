#include <opencv2/opencv.hpp>
#include "ww_lib.h"

#include <iostream>

namespace watching_window
{
   /* * sets the specified subpixel to the intensity specified */
   void set_sub_pixel(cv::Mat image, int sub_pixel_x, int pixel_y, int intensity)
   {
      if (pixel_y >= 1080)
return;//         std::cout << "y oob" << std::endl;
      if (sub_pixel_x >= 1920*3)
return;//         std::cout << "x oob" << std::endl;
      cv::Vec3b colour = image.at<cv::Vec3b>(pixel_y, sub_pixel_x / 3);

      if (sub_pixel_x % 3 == 0)
         colour[RED] = intensity;
      else if ((sub_pixel_x - 1) % 3 == 0)
         colour[GREEN] = intensity;
      else 
         colour[BLUE] = intensity;

      image.at<cv::Vec3b>(pixel_y, sub_pixel_x / 3) = colour;
   }

   /* * bresnhams line drawing algorithm drawing sub pixel line */
   void set_sub_line(cv::Mat i, float x1, float y1, float x2, float y2, int intensity)
   {
      bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
      if(steep){
         std::swap(x1, y1);
         std::swap(x2, y2);
      }

      if(x1 > x2){
         std::swap(x1, x2);
         std::swap(y1, y2);
      }

      float dx = x2 - x1;
      float dy = fabs(y2 - y1);

      float error = dx / 2.0f;
      int ystep = (y1 < y2) ? 1 : -1;
      int y = (int)y1;

      int maxX = (int)x2;

      for(int x=(int)x1; x<maxX; x++){
         if(steep)
            set_sub_pixel(i, y, x, intensity);
         else
            set_sub_pixel(i, x, y, intensity);

         error -= dy;
         if(error < 0){
            y += ystep;
            error += dx;
         }
      }
   }

   /* CYCLE THROUGH THE VIEWS */
   /* start_x corresponds to the view index */
   static const int mask[9][9] = {
      {1, 3, 5, 7, 0, 2, 4, 6, 8}, 
      {0, 2, 4, 6, 8, 1, 3, 5, 7},
      {8, 1, 3, 5, 7, 0, 2, 4, 6},
      {7, 0, 2, 4, 6, 8, 1, 3, 5},
      {6, 8, 1, 3, 5, 7, 0, 2, 4},
      {5, 7, 0, 2, 4, 6, 8, 1, 3},
      {4, 6, 8, 1, 3, 5, 7, 0, 2},
      {3, 5, 7, 0, 2, 4, 6, 8, 1},
      {2, 4, 6, 8, 1, 3, 5, 7, 0},
   };

   /* 
    * expects in_images to be 640 x 360
    * expcects out_image to be 1920 x 1080
    */
   void draw_views(cv::Mat in_images[], cv::Mat out_image) {
      for (int x = 0; x < 640; x++){ // in_image width (mask is 1 wide) 
         for (int y = 0; y < 360; y+=3){ // in_image height (mask is 3 high)
            /* draw 27 pixels, the 81 sub pixels */
            /* draw the sub pixel max */
            /* using the colours in_images[?].colAt(x, y + i) for i in (0, 1, 2) */

            for (int xx = 0; xx < 9; xx++){
               for (int yy = 0; yy < 9; yy++){
                  if (mask[yy][xx] == 0)
                  set_sub_pixel(out_image, x * 9 + xx, y * 3 + yy, 255);      
               }
            }
         }
      }   
   }
   void draw_view(cv::Mat image, int view, const int HEIGHT, const int WIDTH){
      for (int x = 0; x < WIDTH / 3; x++){ // in_image width (mask is 1 wide) 
         for (int y = 0; y < HEIGHT / 3; y+=3){ // in_image height (mask is 3 high)
            for (int xx = 0; xx < 9; xx++){
               for (int yy = 0; yy < 9; yy++){
                  if (mask[yy][xx] == view)
                  set_sub_pixel(image, x * 9 + xx, y * 3 + yy, 255);      
               }
            }
         }
      }   
//      const int SP_WIDTH = WIDTH * 3; 
//      int offset = 0;
//
//      int w_count, h_count;
//      w_count = h_count = 0;
//
//      for (int x = start_x % 9; x + offset  < SP_WIDTH; x += 9){
//         offset = 0;
//         w_count++;
//         h_count = 0;
//         for (int y = 0; y < HEIGHT; y+=2){
//            h_count++;
//            set_sub_pixel(image, x + offset, y, 255);
//            offset = (offset + 1) % 9;
//         } 
//      }
//      //std::cout << w_count << " " << h_count << std::endl;
//
//      w_count = 0;
//      for (int x = (start_x + 5) % 9; x + offset < SP_WIDTH; x += 9){
//         offset = 0;
//         w_count++;
//         h_count = 0;
//         for (int y = 1; y < HEIGHT; y+=2){
//            h_count++;
//            set_sub_pixel(image, x + offset, y, 255);
//            offset = (offset + 1) % 9;
//         } 
//      }   
//   //std::cout << w_count << " " << h_count << std::endl;
   }

   /* edge artifacting */
   void edge_artifacting(cv::Mat image, const int HEIGHT, const int WIDTH)
   {
      cv::line(image, cv::Point(0,0), cv::Point(0, HEIGHT/4), C_WHITE);
      cv::line(image, cv::Point(1, HEIGHT/4 +1), cv::Point(11, HEIGHT/2), C_WHITE);

      cv::line(image, cv::Point(WIDTH-12, HEIGHT/2), cv::Point(WIDTH-2, HEIGHT/4 * 3), C_WHITE);
      cv::line(image, cv::Point(WIDTH-1, HEIGHT/4 * 3), cv::Point(WIDTH-1, HEIGHT-1), C_WHITE);

      cv::line(image, cv::Point(30, HEIGHT/4), cv::Point(WIDTH-31, HEIGHT/4), C_BLUE);
      cv::line(image, cv::Point(30, HEIGHT/4 * 3), cv::Point(WIDTH-31, HEIGHT/4 * 3), C_BLUE);
   }  

   void edge_artifacting2(cv::Mat image, const int HEIGHT, const int WIDTH)
   {
      cv::line(image, cv::Point(WIDTH-1, 0), cv::Point(WIDTH-1, 39), C_RED);
      cv::line(image, cv::Point(WIDTH-1, 40), cv::Point(WIDTH-1, 79), C_BLUE);
      cv::line(image, cv::Point(WIDTH-1, 80), cv::Point(WIDTH-1, 119), C_GREEN);

      int repeats = 3;
      int gap = 20;
      int start = 119 + gap;

      for (int len = 0; start < HEIGHT-1; len++){
         for(int j = 0; j < repeats; j++){
            cv::line(image, cv::Point(WIDTH-1, start), cv::Point(WIDTH-1, start + len), C_WHITE);
            start += len + gap;
         }
      }
   }


   /* LINES */
   void draw_basic_lines(cv::Mat image, const int HEIGHT, const int WIDTH)
   {
      cv::Scalar colours[] = {C_RED, C_GREEN, C_BLUE, C_CYAN, C_MAGENTA, C_YELLOW, C_WHITE, C_BLACK};

      for (int i = 0; i < 8; i++){
         int order = (i + 1) * 100;
         cv::line(image, cv::Point(0, order), cv::Point(WIDTH-1, order), colours[i]);
         cv::line(image, cv::Point(order, 0), cv::Point(order, HEIGHT-1), colours[i]);
         cv::line(image, cv::Point((i+1)*10, 750), cv::Point((i+1)*10, 750), colours[i]);
      }
   }

   /* * SLANT */
   void draw_slant(cv::Mat i, const int HEIGHT, cv::Scalar colours[], int x = 0, int colour_offset = 0)
   {
      /* the line is draw in segments of 6 pixels at a time */
      for (int y = 0; y <  HEIGHT; y+=6){ // y of line
         for (int yy = 0; yy < 6; yy+=2){  // y of line segment
            // change this to yy < 3 by making the line below draw two pixels
            cv::line(i, cv::Point(x, yy + y), cv::Point(x,yy + y + 1), colours[((yy/2) + colour_offset) % 3]);
         }
         x++;
      }
   }

   /* * SLANTS */
   void draw_slants(cv::Mat i, const int WIDTH, const int HEIGHT, const int spacing)
   {
      cv::Scalar cols1[] = {C_RED, C_GREEN, C_BLUE};
      cv::Scalar cols2[] = {C_BLUE, C_GREEN, C_RED};

      for (int lines = 0; lines * spacing < WIDTH; lines+=4){

         for (int x = lines; x < lines + 3; x++){
            draw_slant(i, HEIGHT, cols1, (x + lines) * spacing, x - lines); 
         } 

         for (int x = lines + 3; x < lines + 6; x++){
            draw_slant(i, HEIGHT, cols2, (lines + x) * spacing, x - lines);
         }
      }
   }

}
