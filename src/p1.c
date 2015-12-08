#include <stdio.h>
#include "pgm.h"

/**
 * Autoren: Yildiz Kasimay, Artjom Poljakow, Yadullah Duman
 * --------------------------------------------------------
 *
 * --> Das Einlesen und Schreiben von PGM-Dateien implementieren.
 * --> Beispiel fuer einen Aufruf: $ ./p1 src.pgm dst.pgm
 * --> D.h. die PGM-Datei src.pgm einlesen und als PGM in die Ausgabedatei dst.pgm exportieren
 */

int main(int argc, char *argv[])
{
   const char *data_path = argv[1]; // source pgm
   const char *dest_path = argv[2]; // export

   PGMData pgm_data;
   PGMData *data = &pgm_data;

   puts("Reading PGM ...");
   readFile(data_path, data);
   puts("[+] Finished Reading PGM!");

   puts("Writing PGM ...");
   writeFile(dest_path, data);
   puts("[+] Finished Writing PGM!");
}

