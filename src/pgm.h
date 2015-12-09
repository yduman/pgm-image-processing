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
PGMData* sobelX(PGMData *data);
PGMData* sobelY(PGMData *data);
PGMData* magFilter(PGMData* sobelx, PGMData* sobely, PGMData* data);
PGMData* threshFilter(PGMData* data);
float** directions(PGMData* gy, PGMData* gx);
PGMData* NMS(PGMData* G_matrix, float** O_matrix);
PGMData* binaryPGM(PGMData* data);
#endif //PRAKTIKUM2_PGM_H