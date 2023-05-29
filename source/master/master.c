#include "../engine/header/engine-include-header.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[])
{
	srand(time(NULL));

	int layerAmount = 4;

	int layerSizes[] = {2, 16, 16, 2};
	int layerActivs[] = {1, 1, 1};

  int maxShape = maximum_layer_shape(layerSizes, layerAmount);

  float*** weights = create_fmatrix_array(layerAmount - 1, maxShape, maxShape);
  float** biases = create_float_matrix(layerAmount - 1, maxShape);

  weights = fill_fmatarr_random(weights, layerAmount - 1, maxShape, maxShape, -1.0, +1.0);
  biases = fill_fmatrix_random(biases, layerAmount - 1, maxShape, -1.0, +1.0);

  float hardInputs[4][2] =
  {
    {0.0, 0.0},
    {1.0, 0.0},
    {0.0, 1.0},
    {1.0, 1.0}
  };

  float hardTargets[4][2] =
  {
    {0.0, 1.0},
    {1.0, 0.0},
    {1.0, 0.0},
    {0.0, 1.0}
  };

  float** inputs = create_float_matrix(4, 2);
  float** targets = create_float_matrix(4, 2);

  for(int hIndex = 0; hIndex < 4; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < 2; wIndex += 1)
    {
      inputs[hIndex][wIndex] = hardInputs[hIndex][wIndex];
    }
  }
  for(int hIndex = 0; hIndex < 4; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < 2; wIndex += 1)
    {
      targets[hIndex][wIndex] = hardTargets[hIndex][wIndex];
    }
  }



  float learnRate = 0.7;
  float momentum = 0.2;
  int batchSize = 4;
  int epochAmount = 1000;


  float* outputs = create_float_vector(layerSizes[layerAmount - 1]);



  for(int index = 0; index < batchSize; index += 1)
  {
    frwrd_network_inputs(outputs, layerAmount, layerSizes, layerActivs, weights, biases, inputs[index]);

    printf("(");
    for(int iIndex = 0; iIndex < layerSizes[0]; iIndex += 1)
    {
      printf("%.2f ", inputs[index][iIndex]);
    }
    printf(") ->");

    printf("(");
    for(int oIndex = 0; oIndex < layerSizes[layerAmount - 1]; oIndex += 1)
    {
      printf("%.2f ", outputs[oIndex]);
    }
    printf(")\n");
  }
  printf("\n");



  for(int epochIndex = 0; epochIndex < epochAmount; epochIndex += 1)
  {
    // train_network_minbat(layerAmount, layerSizes, layerActivs, weights, biases, learnRate, momentum, inputs, targets, batchSize);

    int* randIndexis = create_integ_array(batchSize);

    random_indexis_array(randIndexis, batchSize);

    for(int index = 0; index < batchSize; index += 1)
    {
      int randIndex = randIndexis[index];

      train_network_stcast(layerAmount, layerSizes, layerActivs, weights, biases, learnRate, momentum, inputs[randIndex], targets[randIndex]);
    }

    free_integ_array(randIndexis, batchSize);
  }


  for(int index = 0; index < batchSize; index += 1)
  {
    frwrd_network_inputs(outputs, layerAmount, layerSizes, layerActivs, weights, biases, inputs[index]);

    printf("(");
    for(int iIndex = 0; iIndex < layerSizes[0]; iIndex += 1)
    {
      printf("%.2f ", inputs[index][iIndex]);
    }
    printf(") ->");

    printf("(");
    for(int oIndex = 0; oIndex < layerSizes[layerAmount - 1]; oIndex += 1)
    {
      printf("%.2f ", outputs[oIndex]);
    }
    printf(")\n");
  }
  printf("\n");



  free_float_vector(outputs, layerSizes[layerAmount - 1]);


  free_float_matrix(inputs, 4, 2);
  free_float_matrix(targets, 4, 2);


  free_fmatrix_array(weights, layerAmount - 1, maxShape, maxShape);
  free_float_matrix(biases, layerAmount - 1, maxShape);

	return 0;
}