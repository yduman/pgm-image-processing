#include <stdio.h>
#include "pgm.h"

/**
 * Autoren: Yildiz Kasimay, Artjom Poljakow, Yadullah Duman
 * --------------------------------------------------------
 *
 * --> Erkennung von Kanten durch Canny-Algorithmus.
 *      --> Blurring
 *      --> Partielle Ableitung durch Sobeloperator
 *      --> Berechnung der Staerke der Kanten
 *      --> Kantendetektion
 *      --> Richtung der Kanten
 *      --> non-maximum-suppression
 *      --> Binaerkantenbild
 * --> Beispiel fuer einen Aufruf: $ ./p4 elk.pgm edges.pgm
 */

int main(int argc, char *argv[])
{
   printf("P4\n");

   PGMData pgm_data;
   PGMData *data = &pgm_data;

   // Read PGM
   puts("Reading PGM ...");
   PGMData *read = readFile(argv[1], data);
   puts("[+] Finished Reading PGM!");

   // Canny-Processing
   puts("Processing with Canny-Edge-Detection ...");

   // Blur PGM
   puts("Blurring PGM ...");
   PGMData* blurred = blur(read);
   puts("[+] Finished Blurring PGM!");

   // Sobel PGM
   puts("Processing with Sobel-Filter ...");
   PGMData* sobeled = sobel(blurred);
   puts("[+] Finished Sobel-Processing!");

   // Threshold
   puts("Processing with Threshold-Filter ...");
   PGMData* thresh = threshFilter(sobeled);
   puts("[+] Finished Threshold-Processing!");

   // Directions
   puts("Processing with Direction-Filter ...");
   PGMData* dir = directionFilter(thresh);
   puts("[+] Finished Direction-Processing!");

   // Write PGM
   puts("Writing PGM ...");
   writeFile(argv[2], dir);
   puts("[+] Finished Writing PGM!");

   puts("[+] Finished Canny-Edge-Detection!");

   return 0;
}
