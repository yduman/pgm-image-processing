#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "pgm.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

/* Autoren: Yildiz Kasimay, Artjom Poljakow, Yadullah Duman */

/**
 *  dient der Speicherallokation
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

/**
 *  dient der Speicherfreigabe
 */
void destroy(float **pixel_matrix, int row) {
    for (int i = 0; i < row; i++) {
        free(pixel_matrix[i]);
    }
    free(pixel_matrix);
}

/**
 *  Kommentare in der PGM werden ignoriert
 */
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

/**
 *  das Lesen der PGM
 */
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

/**
 *  das Schreiben der PGM
 */
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

/**
 *  Blurring der PGM
 */
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

    // Prozess des Blurrings
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

/**
 *  das Schaerfen der PGM
 */
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

    // sharpening Prozess
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

/**
 *  Minimum-Filter
 */
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

    // Filter-Prozess
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

/**
 *  Median-Filter
 */
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

    // Filter-Prozess
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

/**
 *  Maximum-Filter
 */
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

    // Filter-Prozess
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

/**
 *  Sobel-Operation + Kantenstaerke-Operation
 */
PGMData* sobel(PGMData *data)
{
    float valX = 0;
    float valY = 0;

    float **sobel_filtered_matrix;
    sobel_filtered_matrix = mem_alloc(data->row, data->col);
    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            sobel_filtered_matrix[i][j] = 0;
        }
    }

    // sobel
    for (int i = 1; i < data->row - 1; i++) {
        for (int j = 1; j < data->col - 1; j++) {
            valX = (data->pixel_matrix[i-1][j+1]+2 * data->pixel_matrix[i][j+1] + data->pixel_matrix[i+1][j+1]) -
                   (data->pixel_matrix[i-1][j-1]+2 * data->pixel_matrix[i][j-1] + data->pixel_matrix[i+1][j-1]);

            valY = (data->pixel_matrix[i+1][j-1]+2 * data->pixel_matrix[i+1][j] + data->pixel_matrix[i+1][j+1]) -
                   (data->pixel_matrix[i-1][j-1]+2 * data->pixel_matrix[i-1][j] + data->pixel_matrix[i-1][j+1]);

            // magnitude + normalization
            sobel_filtered_matrix[i][j] = 255 * sqrtf((valX * valX) + (valY * valY)) / 950;

        }
    }

    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            data->pixel_matrix[i][j] = sobel_filtered_matrix[i][j];
        }
    }

    return data;
}

/**
 *  Thresholding
 */
PGMData* threshFilter(PGMData* data)
{
    for (int i = 0; i < data->row; ++i) {
        for (int j = 0; j < data->col; ++j) {
            if (data->pixel_matrix[i][j] < 40)
                data->pixel_matrix[i][j] = 0;
            else if (data->pixel_matrix[i][j] > 255)
                data->pixel_matrix[i][j] = 255;
        }
    }
    return data;
}

/**
 *  Richtung der Kanten
 */
PGMData* directionFilter(PGMData* data)
{
    float atan;

    float **direction_filtered_matrix;
    direction_filtered_matrix = mem_alloc(data->row, data->col);
    for (int i = 0; i < data->row; i++) {
        for (int j = 0; j < data->col; j++) {
            direction_filtered_matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < data->row; ++i) {
        for (int j = 0; j < data->col; ++j) {
            atan = atanf(data->pixel_matrix[i][j]);
            direction_filtered_matrix[i][j] = atan;
        }
    }

    for (int i = 0; i < data->row; ++i) {
        for (int j = 0; j < data->col; ++j) {
            data->pixel_matrix[i][j] = direction_filtered_matrix[i][j];
        }
    }

    data->max_greyscale = 1;

    return data;
}

/**
 *  non-maximum-suppression
 */
PGMData* NMS(PGMData* mag_matrix, float** dir_matrix)
{
    // Matrix erstellen
    float **NMS_matrix = mem_alloc(mag_matrix->row, mag_matrix->col);
    for (int i = 0; i < mag_matrix->row; ++i) {
        for (int j = 0; j < mag_matrix->col; ++j) {
            NMS_matrix[i][j] = 0;
        }
    }

    // non-maximum suppression
    for (int i = 1; i < mag_matrix->row - 1; ++i) {
        for (int j = 1; j < mag_matrix->col - 1; ++j) {
            float t = dir_matrix[i][j];
            if(t > 67.5 && t <= 90 || t >= -90 && t <= -67.5) {
                if (mag_matrix->pixel_matrix[i - 1][j] > mag_matrix->pixel_matrix[i][j]
                    || mag_matrix->pixel_matrix[i + 1][j] > mag_matrix->pixel_matrix[i][j]) {
                    NMS_matrix[i][j] = 0;
                }
                else NMS_matrix[i][j] = mag_matrix->pixel_matrix[i][j];

            }
            if(t > -22.5 && t <= 22.5) {
                if (mag_matrix->pixel_matrix[i][j - 1] > mag_matrix->pixel_matrix[i][j]
                    || mag_matrix->pixel_matrix[i][j + 1] > mag_matrix->pixel_matrix[i][j]) {
                    NMS_matrix[i][j] = 0;
                }
                else NMS_matrix[i][j] = mag_matrix->pixel_matrix[i][j];
            }
            if(t > 22.5 && t <= 67.5) {
                if (mag_matrix->pixel_matrix[i - 1][j - 1] > mag_matrix->pixel_matrix[i][j]
                    || mag_matrix->pixel_matrix[i + 1][j + 1] > mag_matrix->pixel_matrix[i][j]) {
                    NMS_matrix[i][j] = 0;
                }
                else NMS_matrix[i][j] = mag_matrix->pixel_matrix[i][j];
            }
            if(t > 67.5 && t <= 90 || t >= -90 && t <= -67.5) {
                if (mag_matrix->pixel_matrix[i - 1][j + 1] > mag_matrix->pixel_matrix[i][j]
                    || mag_matrix->pixel_matrix[i + 1][j - 1] > mag_matrix->pixel_matrix[i][j]) {
                    NMS_matrix[i][j] = 0;
                }
                else NMS_matrix[i][j] = mag_matrix->pixel_matrix[i][j];
            }
        }
    }

    // G_matrix zu T_matrix aktualisieren
    for (int i = 0; i < mag_matrix->row; ++i) {
        for (int j = 0; j < mag_matrix->col; ++j) {
            mag_matrix->pixel_matrix[i][j] = dir_matrix[i][j];
        }
    }

    // G_matrix = T_matrix
    return mag_matrix;
}
