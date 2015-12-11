#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

/**
 * Autoren: Yildiz Kasimay, Artjom Poljakow, Yadullah Duman
 * --------------------------------------------------------
 *
 * --> Einsatz von Nichtlinearen Filtern.
 *      --> Minimum-Filter
 *      --> Median-Filter
 *      --> Maximum-Filter
 * --> Beispiel fuer einen Aufruf: $ ./p3 src.pgm N min.pgm med.pgm max.pgm
 * --> N ist ungerade und repraesentiert ein NxN-Filter
 */

int main(int argc, char *argv[])
{
   printf("P3\n");

   const char *data_path = argv[1]; // source pgm
   const char *N         = argv[2]; // N fuer NxN-Matrix
   const char *min_path  = argv[3]; // export Minimum-Filter
   const char *med_path  = argv[4]; // export Median-Filter
   const char *max_path  = argv[5]; // export Maximum-Filter

   PGMData pgm_min, pgm_med, pgm_max;

   PGMData *data1 = &pgm_min;
   PGMData *data2 = &pgm_med;
   PGMData *data3 = &pgm_max;

   readFile(data_path, data1);
   minimumFilter(data1, atoi(N));
   writeFile(min_path, data1);
   puts("[+] Finished Minimum-Filter-Processing!");

   readFile(data_path, data2);
   medianFilter(data2, atoi(N));
   writeFile(med_path, data2);
   puts("[+] Finished Median-Filter-Processing!");

   readFile(data_path, data3);
   maximumFilter(data3, atoi(N));
   writeFile(max_path, data3);
   puts("[+] Finished Maximum-Filter-Processing!");

   return 0;
}
