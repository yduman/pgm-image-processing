#include <stdio.h>
#include "pgm.h"

/**
 * Autoren: Yildiz Kasimay, Artjom Poljakow, Yadullah Duman
 * --------------------------------------------------------
 *
 * --> Blurring und Sharpening von PGM-Dateien
 * --> Beispiel fuer einen Aufruf: $ ./p2 src.pgm blur.pgm sharp.pgm
 * --> D.h. die PGM-Datei src.pgm einlesen
 *      --> blurren und als blur.pgm exportieren
 *      --> sharpen und als sharp.pgm exportieren
 *                             ( 0.0625  0.125  0.0625 )
 * --> Kernel fuer blurring :: ( 0.125   0.25   0.125  )
 *                             ( 0.0625  0.125  0.0625 )
 *
 *                               ( 0  -1   0)
 * --> Kernel fuer sharpening :: (-1   5  -1)
 *                               ( 0  -1   0)
 */

int main(int argc, char *argv[])
{
   printf("P2\n");

   const char *data_path = argv[1]; // source pgm
   const char *blur_path = argv[2]; // export blurred
   const char *shar_path = argv[3]; // export sharpened

   PGMData pgm_data, pgm_data2;

   PGMData *data = &pgm_data;
   PGMData *data2 = &pgm_data2;

   puts("Reading PGM ...");
   readFile(data_path, data);
   puts("[+] Finished Reading PGM!");

   puts("Blurring PGM ...");
   blur(data);
   writeFile(blur_path, data);
   puts("[+] Finished Blurring PGM!");

   puts("Reading PGM ...");
   readFile(data_path, data2);
   puts("[+] Finished Reading PGM!");

   puts("Sharpening PGM ...");
   sharpen(data2);
   writeFile(shar_path, data2);
   puts("[+] Finished Sharpening PGM!");

   return 0;
}