#include <stdio.h>
#include "pgm.h"

/**
 * Blurring und Sharpening of PGM files
 * Example call: $ ./p2 src.pgm blur.pgm sharp.pgm
 */

int main(int argc, char *argv[])
{
   printf("P2\n");

   const char *data_path = argv[1];
   const char *blur_path = argv[2];
   const char *shar_path = argv[3];

   PGMData pgm_data, pgm_data2;

   PGMData *data = &pgm_data;
   PGMData *data2 = &pgm_data2;

   readFile(data_path, data);
   blur(data);
   writeFile(blur_path, data);
   puts("[+] Finished Blurring PGM!");

   readFile(data_path, data2);
   sharpen(data2);
   writeFile(shar_path, data2);
   puts("[+] Finished Sharpening PGM!");

   return 0;
}