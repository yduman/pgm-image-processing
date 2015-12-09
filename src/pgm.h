#ifndef PRAKTIKUM2_PGM_H
#define PRAKTIKUM2_PGM_H

// P1
typedef struct {
    int row;
    int col;
    int max_greyscale;
    float **pixel_matrix;
} PGMData;

float **mem_alloc(int row, int col);
void destroy(float **pixel_matrix, int row);
void ignoreComments(FILE *fp);
PGMData* readFile(const char *filename, PGMData *data);
void writeFile(const char *filename, const PGMData *data);

// P2
PGMData* blur(PGMData *data);
PGMData* sharpen(PGMData *data);

// P3
void minimumFilter(PGMData *data, int N);
void medianFilter(PGMData *data, int N);
void maximumFilter(PGMData *data, int N);

// P4
PGMData* sobel(PGMData *data);
PGMData* threshFilter(PGMData* data);
PGMData* directionFilter(PGMData* data);
PGMData* NMS(PGMData* mag_matrix, float** dir_matrix);

#endif //PRAKTIKUM2_PGM_H