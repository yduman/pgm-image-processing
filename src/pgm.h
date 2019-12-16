#ifndef PGM_H
#define PGM_H

typedef struct
{
    int row;
    int col;
    int max_greyscale;
    float **pixel_matrix;
} PGMData;

float **mem_alloc(int row, int col);
void destroy(float **pixel_matrix, int row);
void ignoreComments(FILE *fp);
PGMData *readFile(const char *filename, PGMData *data);
void writeFile(const char *filename, const PGMData *data);

PGMData *blur(PGMData *data);
PGMData *sharpen(PGMData *data);

void sort(float *array, int length);
void minimumFilter(PGMData *data, int N);
void medianFilter(PGMData *data, int N);
void maximumFilter(PGMData *data, int N);

PGMData *sobelX(PGMData *data);
PGMData *sobelY(PGMData *data);
PGMData *magFilter(PGMData *sobelx, PGMData *sobely, PGMData *data);
PGMData *threshFilter(PGMData *data);
float **directions(PGMData *gy, PGMData *gx);
PGMData *NMS(PGMData *G_matrix, float **O_matrix);
PGMData *binaryPGM(PGMData *data);
#endif