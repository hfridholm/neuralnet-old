#ifndef ENGINE_H
#define ENGINE_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

typedef struct
{
  int layers;
  int* sizes;
  int* activs;
  float*** weights;
  float** biases;
} Network;

#include "header/neural-activate-funcs.h"
#include "header/neural-network-actions.h"
#include "header/neural-network-handler.h"
#include "header/vector-matrix-handler.h"

#endif
