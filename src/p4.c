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
   PGMData *read = readFile(argv[1], data);
   puts("[+] Finished Reading PGM!");

   // Blur PGM
   PGMData* blurred = blur(read);
   puts("[+] Finished Blurring PGM!");

   // Sobel PGM
   PGMData* gx = sobel(blurred);
   puts("[+] Finished Sobel-Processing!");

   // Threshold
   PGMData* thresh = threshFilter(gx);
   puts("[+] Finished Threshold-Processing!");

   // Directions
   PGMData* dir = directionFilter(thresh);
   puts("[+] Finished Direction-Processing!");

   // NMS
   PGMData* nms = NMS(thresh, dir->pixel_matrix);
   puts("[+] Finished NMS-Processing");

   // Write PGM
   writeFile(argv[2], nms);
   puts("[+] Finished Writing PGM!");

   return 0;
}
