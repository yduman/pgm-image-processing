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

   // Canny
   puts("Processing with Canny-Edge-Detection ...");

   // Blur PGM
   puts("Blurring PGM ...");
   PGMData* blurred = blur(read);
   puts("[+] Finished Blurring PGM!");

   // Sobel PGM
   puts("Processing with Sobel-Filter ...");
   PGMData* sobel_x = sobelX(blurred);
   PGMData* sobel_y = sobelY(blurred);
   puts("[+] Finished Sobel-Processing!");

   // Magnitude
   puts("Calculating magnitude ...");
   PGMData*magFiltered = magnitudeFilter(sobel_x, sobel_y);
   puts("[+] Finished calculating magnitude!");

   // Threshold
   puts("Removing all edges under threshold");
   PGMData* thresh = threshFilter(magFiltered);
   puts("[+] Finished removing edges under threshold!");

   // Write PGM
   puts("Writing PGM ...");
   writeFile(argv[2], thresh);
   puts("[+] Finished Writing PGM!");

   puts("[+] Finished Canny-Edge-Detection!");

   return 0;
}
