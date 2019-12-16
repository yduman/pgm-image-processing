#include <stdio.h>
#include "pgm.h"

/**
 * Read and Write PGM files
 * Example call: $ ./p1 source.pgm dist.pgm
 */

int main(int argc, char *argv[])
{
   const char *data_path = argv[1]; // source
   const char *dest_path = argv[2]; // destination

   PGMData pgm_data;
   PGMData *data = &pgm_data;

   readFile(data_path, data);
   puts("[+] Finished Reading PGM!");

   writeFile(dest_path, data);
   puts("[+] Finished Writing PGM!");
}
