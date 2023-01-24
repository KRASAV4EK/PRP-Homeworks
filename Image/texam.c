#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "exam_utils.h"
#include "xwin_sdl.h"
#include "save_jpeg.h"

bool file_proc(FILE *file, unsigned char *img, const char *fout, int image_w, int image_h, bool anim);
bool swap(unsigned char *img, int x1, int y1, int w, int h, int x2, int y2, int image_w, int image_h);
bool copy(unsigned char *img, int x1, int y1, int w, int h, int x2, int y2, int image_w, int image_h);

int main(int argc, char *argv[])
{
   bool ret = EXIT_SUCCESS;

   // args
   const char *fimage = argc > 1 ? argv[1] : NULL;
   const char *cmds = argc > 2 ? argv[2] : NULL;
   const char *fout = argc > 3 ? argv[3] : NULL;
   const bool anim = argc > 4 && strcmp(argv[4], "--anim") == 0;

   my_assert(fimage != NULL && cmds != NULL && fout != NULL, __func__, __LINE__, __FILE__);

   // init sizes
   int image_w, image_h;
   unsigned char *img = xwin_load_image(fimage, &image_w, &image_h);

   // create animation
   if (anim)
      xwin_init(image_w, image_h);

   // change image
   if (!ret && img)
   {
      FILE *file = fopen(cmds, "r");
      if (!file)
      {
         fprintf(stderr, "Error! Wrong file!\n");
         exit(101);
      }

      ret = file_proc(file, img, fout, image_w, image_h, anim);

      fclose(file);
   }
   else
   {
      fprintf(stderr, "Error! Wrong image!\n");
      exit(104);
   }
   

   // save  output image
   if (!ret)
   {
      if (strstr(fout, ".jpeg") == 0 || strstr(fout, ".jpg"))
         save_image_jpeg(image_w, image_h, img, fout);
      
      else
         save_image_rgb(image_w, image_h, img, fout);
   }

   if (anim)
      xwin_close();
   
   free(img);

   return ret;
}

bool file_proc(FILE *file, unsigned char *img, const char *fout, int image_w, int image_h, bool anim)
{
   bool ret = EXIT_SUCCESS;
   int x1, y1;
   char cmd[3];
   int x2, y2;
   int w, h;
   int counter = 0;
   int out;

   while (!feof(file) && !ret)
   {
      out = fscanf(file, "%2s %d %d %d %d %d %d\n", cmd, &x1, &y1, &w, &h, &x2, &y2);

      if (out == 7 && strcmp(cmd, "sw") == 0)
         ret = swap(img, x1, y1, w, h, x2, y2, image_w, image_h);

      else if (out == 7 && strcmp(cmd, "cp") == 0)
         ret = copy(img, x1, y1, w, h, x2, y2, image_w, image_h);

      else
      {
         fprintf(stderr, "Error! Wrong command!\n");
         exit(102);
      }

      if (anim && counter % 15 == 0)
      {
         xwin_redraw(image_w, image_h, img);
         delay(20);
      }
   }

   return ret;
}

bool swap(unsigned char *img, int x1, int y1, int w, int h, int x2, int y2, int image_w, int image_h)
{
   bool ret = EXIT_SUCCESS;

   for (unsigned xi = 0; xi < w; xi++)
   {
      for (unsigned yi = 0; yi < h; yi++)
      {
         const int sx = xi + x1;
         const int sy = yi + y1;
         const int dx = xi + x2;
         const int dy = yi + y2;

         if (dx >= 0 && dx < image_w && dy >= 0 && dy < image_h &&
             sx >= 0 && sx < image_w && sy >= 0 && sy < image_h)
         {
            for (unsigned i = 0; i < 3; i++)
            {
               unsigned char temp = img[(sy * image_w + sx) * 3 + i];
               img[(sy * image_w + sx) * 3 + i] = img[(dy * image_w + dx) * 3 + i];
               img[(dy * image_w + dx) * 3 + i] = temp;
            }
         }
         else
         {
            fprintf(stderr, "Error! Wrong swap coordinates!\n");
            ret = EXIT_FAILURE;
            break;
         }
      }
   }

   return ret;
}

bool copy(unsigned char *img, int x1, int y1, int w, int h, int x2, int y2, int image_w, int image_h)
{
   bool ret = EXIT_SUCCESS;

   for (unsigned xi = 0; xi < w; xi++)
   {
      for (unsigned yi = 0; yi < h; yi++)
      {
         const int sx = xi + x1;
         const int sy = yi + y1;
         const int dx = xi + x2;
         const int dy = yi + y2;

         if (dx >= 0 && dx < image_w && dy >= 0 && dy < image_h &&
             sx >= 0 && sx < image_w && sy >= 0 && sy < image_h)
         {
            for (unsigned i = 0; i < 3; i++)
               img[(dy * image_w + dx) * 3 + i] = img[(sy * image_w + sx) * 3 + i];
         }
         else
         {
            fprintf(stderr, "Error! Wrong copy coordinates!\n");
            ret = EXIT_FAILURE;
            break;
         }
      }
   }

   return ret;
}

/* end of texam.c */
