#ifndef PERSUE_H
#define PERSUE_H

#include <math.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>

#include "stb_image.h"
#include "stb_image_write.h"

#include "secure.h"
#include "review.h"
#include "adjust.h"

typedef enum { ACTIV_NONE, ACTIV_SIGMOID, ACTIV_RELU, ACTIV_TANH, ACTIV_SOFTMAX } Activ;

typedef struct
{
  int layers;
  int* sizes;
  Activ* activs;
  float*** weights;
  float** biases;
} Network;

extern int    network_sizes_maximum(const int networkSizes[], int networkLayers);

extern float  cross_entropy_cost(float* nodes, float* targets, int amount);


extern bool network_forward(float* outputs, Network network, float* inputs);

extern void network_train_stcast_epochs(Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, int epochAmount, unsigned long totalMills);

extern void network_train_minbat_epochs(Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, int epochAmount);


extern float*   pixels_nrmliz_array_read(int* imgWidth, int* imgHeight, const char filePath[]);

extern float**  pixels_nrmliz_matrix_read(int* imgWidth, int* imgHeight, const char filePath[]);

extern bool     pixels_nrmliz_matrix_write(const char filePath[], float** nrmmat, int width, int height);

extern bool     pixels_nrmliz_array_write(const char filePath[], float* nrmarr, int width, int height);

#endif
