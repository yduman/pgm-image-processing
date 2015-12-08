#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "pgm.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

/**
 * Autoren: Yildiz Kasimay, Artjom Poljakow, Yadullah Duman
 */

float **mem_alloc(int row, int col) {
    float **ret;

    ret = malloc(sizeof(float*) * row);
    if (ret == NULL) {
        perror("Error while allocating memory (NULL)");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < row; i++) {
        ret[i] = malloc(sizeof(float) * col);
        if (ret[i] == NULL) {
            perror("Error while allocating memory (NULL)");
            exit(EXIT_FAILURE);
        }
    }
    return ret;
}

void destroy(float **pixel_matrix, int row) {
    for (int i = 0; i < row; i++) {
        free(pixel_matrix[i]);
    }
    free(pixel_matrix);
}

void ignoreComments(FILE *fp) {
    int c;
    char line[1000];

    while((c = fgetc(fp)) != EOF && isspace(c))
        ;
    if (c == '#') {
        fgets(line, sizeof(line), fp);
        ignoreComments(fp);
    } else {
        fseek(fp, -1, SEEK_CUR);
    }
}

PGMData* readFile(const char *filename, PGMData *data) {
    FILE *fp;
    char magic[3];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error while reading file (NULL)");
        exit(EXIT_FAILURE);
    }

    fgets(magic, sizeof(magic), fp);

    ignoreComments(fp);
    fscanf(fp, "%d", &data->col);

    ignoreComments(fp);
    fscanf(fp, "%d", &data->row);

    ignoreComments(fp);
    fscanf(fp, "%d", &data->max_greyscale);

    fgetc(fp);
    data->pixel_matrix = mem_alloc(data->row, data->col);

    // read
    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            fscanf(fp, "%f", &data->pixel_matrix[i][j]);
        }
    }
    fclose(fp);
    return data;
}

void writeFile(const char *filename, const PGMData *data) {
    FILE *fp;

    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error while writing file (NULL)");
        exit(EXIT_FAILURE);
    }

    // write :: magic, breite_hoehe, max. graustufe
    fprintf(fp, "P2\n");
    fprintf(fp, "%d %d\n", data->col, data->row);
    fprintf(fp, "%d\n", data->max_greyscale);

    // write :: matrix
    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            fprintf(fp, "%d", (int)data->pixel_matrix[i][j]);
            if ((j + 1) < data->col) {
                fputc(' ', fp);
            }
        }
        fputc('\n', fp);
    }

    fclose(fp);
    destroy(data->pixel_matrix, data->row);
}

PGMData* blur(PGMData *data)
{
    float kernel[3][3] = {
            {0.0625,  0.125,  0.0625},
            {0.125 ,  0.25 ,  0.125},
            {0.0625,  0.125,  0.0625}
    };

    float sum = 0;

    float **blurred_matrix;
    blurred_matrix = mem_alloc(data->row, data->col);
    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            blurred_matrix[i][j] = 0;
        }
    }

    for (int i = 1; i < data->row - 1; i++) {
        for (int j = 1; j < data->col - 1; j++) {
            sum = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    sum = sum + data->pixel_matrix[i + k][j + l] * kernel[1 + k][1 + l];
                }
            }
            blurred_matrix[i][j] = sum;
            if (blurred_matrix[i][j] < 0)
                blurred_matrix[i][j] = 0;
            else if (blurred_matrix[i][j] > 255)
                blurred_matrix[i][j] = 255;
        }
    }

    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++ ) {
            data->pixel_matrix[i][j] = blurred_matrix[i][j];
        }
    }

    return data;
}

PGMData* sharpen(PGMData *data)
{
    int kernel[3][3] = {
            {0, -1, 0},
            {-1, 5, -1},
            {0, -1, 0}
    };

    float sum = 0;

    float **sharpened_matrix;
    sharpened_matrix = mem_alloc(data->row, data->col);
    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            sharpened_matrix[i][j] = 0;
        }
    }

    for (int i = 1; i < data->row - 1; i++) {
        for (int j = 1; j < data->col - 1; j++) {
            sum = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    sum = sum + data->pixel_matrix[i + k][j + l] * kernel[1 + k][1 + l];
                }
            }
            sharpened_matrix[i][j] = sum;
            if (sharpened_matrix[i][j] < 0)
                sharpened_matrix[i][j] = 0;
            else if (sharpened_matrix[i][j] > 255)
                sharpened_matrix[i][j] = 255;
        }
    }

    for (int i = 0; i < data->row; ++i) {
        for (int j = 0; j < data->col; ++j) {
            data->pixel_matrix[i][j] = sharpened_matrix[i][j];
        }
    }

    return data;
}

void minimumFilter(PGMData *data, int N)
{
    float minval;

    float **minimum_filtered_matrix;
    minimum_filtered_matrix = mem_alloc(data->row, data->col);
    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            minimum_filtered_matrix[i][j] = 0;
        }
    }

    for (int i = N / 2; i < data->row - N / 2; i++) {
        for (int j = N / 2; j < data->col - N / 2; j++) {
            minval = data->pixel_matrix[i][j];
            for (int k = -N / 2; k <= N / 2; k++) {
                for (int l = -N / 2; l <= N / 2; l++) {
                    minval = min(data->pixel_matrix[i + k][j + l], minval);
                }
            }
            minimum_filtered_matrix[i][j] = minval;
            if (minimum_filtered_matrix[i][j] < 0)
                minimum_filtered_matrix[i][j] = 0;
            else if (minimum_filtered_matrix[i][j] > 255)
                minimum_filtered_matrix[i][j] = 255;
        }
    }

    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            data->pixel_matrix[i][j] = minimum_filtered_matrix[i][j];
        }
    }
}

void medianFilter(PGMData *data, int N)
{
    int counter = 0;
    float *unordered_list;
    int filter_size = N * N;
    float *ordered_list;

    unordered_list  = malloc(filter_size * sizeof(int));
    ordered_list    = malloc(filter_size * sizeof(int));

    float **median_filtered_matrix;
    median_filtered_matrix = mem_alloc(data->row, data->col);
    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            median_filtered_matrix[i][j] = 0;
        }
    }

    for (int i = N / 2; i < data->row - N / 2; i++) {
        for (int j = N / 2; j < data->col - N / 2; j++) {
            counter = 0;
            for (int k = -N / 2; k <= N / 2; k++) {
                for (int l = -N / 2; l <= N / 2; l++) {
                    unordered_list[counter] = data->pixel_matrix[i + k][j + l];
                    counter++;
                }
            }

            counter = 0;
            for (int m = 0; m < filter_size; m++) {
                float minval = unordered_list[0];
                for (int n = 0; n < filter_size; n++) {
                    if (unordered_list[n] == 555)
                        continue;
                    if (unordered_list[n] < minval) {
                        minval = unordered_list[n];
                        unordered_list[n] = 555;
                    }
                }
                ordered_list[counter] = minval;
                counter++;
            }

            median_filtered_matrix[i][j] = ordered_list[filter_size / 2 + 1];
            if (median_filtered_matrix[i][j] < 0)
                median_filtered_matrix[i][j] = 0;
            else if (median_filtered_matrix[i][j] > 255)
                median_filtered_matrix[i][j] = 255;
        }
    }

    for (int i = 0; i < data->row; ++i) {
        for (int j = 0; j < data->col; ++j) {
            data->pixel_matrix[i][j] = median_filtered_matrix[i][j];
        }
    }
}

void maximumFilter(PGMData *data, int N)
{
    float maxval;

    float **maximum_filtered_matrix;
    maximum_filtered_matrix = mem_alloc(data->row, data->col);
    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            maximum_filtered_matrix[i][j] = 0;
        }
    }

    for (int i = N / 2; i < data->row - N / 2; i++) {
        for (int j = N / 2; j < data->col - N / 2; j++) {
            maxval = data->pixel_matrix[i][j];
            for (int k = -N / 2; k <= N / 2; k++) {
                for (int l = -N / 2; l <= N / 2; l++) {
                    maxval = max(data->pixel_matrix[i + k][j + l], maxval);
                }
            }
            maximum_filtered_matrix[i][j] = maxval;
            if (maximum_filtered_matrix[i][j] < 0)
                maximum_filtered_matrix[i][j] = 0;
            else if (maximum_filtered_matrix[i][j] > 255)
                maximum_filtered_matrix[i][j] = 255;
        }
    }

    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            data->pixel_matrix[i][j] = maximum_filtered_matrix[i][j];
        }
    }
}

PGMData* sobelX(PGMData *data)
{
    int sobelX[3][3] = {
            {1, 0, -1},
            {2, 0, -2},
            {1, 0, -1}
    };

    float valX = 0;
    float scale;
    float newPixel;

    int oldmin = 0;
    int oldmax = 950;
    int oldrange = oldmax - oldmin;

    int newmin = 0;
    int newmax = 255;
    int newrange = newmax - newmin;

    float **sobelX_filtered_matrix;
    sobelX_filtered_matrix = mem_alloc(data->row, data->col);
    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            sobelX_filtered_matrix[i][j] = 0;
        }
    }

    for (int i = 1; i < data->row - 1; i++) {
        for (int j = 1; j < data->col - 1; j++) {
            valX = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= -1; l++) {
                    valX = valX + data->pixel_matrix[i + k][j + l] * sobelX[1 + k][1 + l];
                }
            }
            scale = valX / oldrange;
            newPixel = (newrange * scale) + newmin;

            sobelX_filtered_matrix[i][j] = newPixel;
            if (sobelX_filtered_matrix[i][j] < 0)
                sobelX_filtered_matrix[i][j] = 0;
            else if (sobelX_filtered_matrix[i][j] > 255)
                sobelX_filtered_matrix[i][j] = 255;
        }
    }

    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            data->pixel_matrix[i][j] = sobelX_filtered_matrix[i][j];
        }
    }

    return data;
}

PGMData* sobelY(PGMData *data)
{
    int sobelY[3][3] = {
            {1, 2, 1},
            {0, 0, 0},
            {-1, -2, -1}
    };

    float valY = 0;
    float scale;
    float newPixel;

    int oldmin = -174;
    int oldmax = 237;
    int oldrange = oldmax - oldmin;

    int newmin = 0;
    int newmax = 255;
    int newrange = newmax - newmin;

    float **sobelY_filtered_matrix;
    sobelY_filtered_matrix = mem_alloc(data->row, data->col);
    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            sobelY_filtered_matrix[i][j] = 0;
        }
    }

    for (int i = 1; i < data->row - 1; i++) {
        for (int j = 1; j < data->col - 1; j++) {
            valY = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= -1; l++) {
                    valY = valY + data->pixel_matrix[i + k][j + l] * sobelY[1 + k][1 + l];
                }
            }

            scale = valY / oldrange;
            newPixel = (newrange * scale) + newmin;

            sobelY_filtered_matrix[i][j] = newPixel;
            if (sobelY_filtered_matrix[i][j] < 0)
                sobelY_filtered_matrix[i][j] = 0;
            else if (sobelY_filtered_matrix[i][j] > 255)
                sobelY_filtered_matrix[i][j] = 255;
        }
    }

    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            data->pixel_matrix[i][j] = sobelY_filtered_matrix[i][j];
        }
    }

    return data;
}

PGMData* magnitudeFilter(PGMData* sobelx, PGMData* sobely)
{
    float gx = 0;
    float gy = 0;

    int pixel;

    float **magnitude_filtered_matrix = mem_alloc(sobelx->row, sobelx->col);
    for (int i = 0; i < sobelx->row; ++i) {
        for (int j = 0; j < sobelx->col; ++j) {
            magnitude_filtered_matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < sobelx->row; ++i) {
        for (int j = 0; j < sobelx->col; ++j) {
            gx = sobelx->pixel_matrix[i][j];
            gy = sobely->pixel_matrix[i][j];
            pixel = (int)(sqrt(gx * gx + gy * gy));

            magnitude_filtered_matrix[i][j] = pixel;
        }
    }

    for (int i = 0; i < sobelx->row; ++i) {
        for (int j = 0; j < sobelx->col; ++j) {
            sobelx->pixel_matrix[i][j] = magnitude_filtered_matrix[i][j];
        }
    }

    return sobelx;
}

PGMData* threshFilter(PGMData* data)
{
    for (int i = 0; i < data->row; ++i) {
        for (int j = 0; j < data->col; ++j) {
            if (data->pixel_matrix[i][j] < 0)
                data->pixel_matrix[i][j] = 0;
            else if (data->pixel_matrix[i][j] > 255)
                data->pixel_matrix[i][j] = 255;
        }
    }

    return data;
}
