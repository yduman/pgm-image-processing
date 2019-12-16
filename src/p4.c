#include <stdio.h>
#include "pgm.h"

/**
 * Canny edge detection
 * Example call: $ ./p4 source.pgm dist.pgm
 */

int main(int argc, char *argv[])
{
   printf("P4\n");

   PGMData pgm_data, pgm_data2, magnitude_output;

   PGMData *data = &pgm_data;
   PGMData *data2 = &pgm_data2;
   PGMData *mag_out = &magnitude_output;

   PGMData *read = readFile(argv[1], data);
   PGMData *blurred = blur(read);
   puts("[+] Finished Blurring!");

   PGMData *gx = sobelX(blurred);
   puts("[+] Finished Sobel_X!");

   PGMData *read2 = readFile(argv[1], data2);
   PGMData *blurred2 = blur(read2);
   PGMData *gy = sobelY(blurred2);
   puts("[+] Finished Sobel_Y!");

   PGMData *mag = readFile(argv[1], mag_out);
   PGMData *magnitude = magFilter(gx, gy, mag);
   puts("[+] Finished calculating magnitude of Edges!");

   PGMData *thresh = threshFilter(magnitude);
   puts("[+] Finished Thresholding!");

   PGMData *nms = NMS(thresh, directions(gy, gx));
   puts("[+] Finished NMS!");

   PGMData *bin = binaryPGM(nms);
   puts("[+] Finished binary PGM!");

   writeFile(argv[2], bin);
   puts("[+] Finished Canny-Edge-Detection!");
   return 0;
}
