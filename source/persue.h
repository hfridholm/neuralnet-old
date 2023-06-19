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

extern int maximum_layer_shape(const int networkSizes[], int networkLayers);

extern float* cross_entropy_derivs(float* derivs, float* nodes, float* targets, int amount);

extern float cross_entropy_cost(float* nodes, float* targets, int amount);

extern void apply_activ_derivs(float* layerDerivs, float* layerValues, int layerWidth, Activ layerActiv);

extern void layer_activ_values(float* activValues, float* layerValues, int layerWidth, Activ layerActiv);


extern bool frwrd_network_inputs(float* outputs, Network network, float* inputs);

extern void train_epochs_stcast(Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, int epochAmount);


extern float* pixels_nrmliz_vector(int* imgWidth, int* imgHeight, const char filePath[]);

extern float** pixels_nrmliz_matrix(int* imgWidth, int* imgHeight, const char filePath[]);

extern bool write_nrmmat_pixels(const char filePath[], float** nrmmat, int width, int height);

extern bool write_nrmarr_pixels(const char filePath[], float* nrmarr, int width, int height);

#endif
