#include "../engine/header/engine-include-header.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[])
{
	srand(time(NULL));

	int layerAmount = 3;

	int layerSizes[] = {2, 3, 1};
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

  float hardTargets[4][1] =
  {
    {0.0},
    {1.0},
    {1.0},
    {0.0}
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

  float* outputs = create_float_vector(layerSizes[layerAmount - 1]);


  frwrd_network_inputs(outputs, layerAmount, layerSizes, layerActivs, weights, biases, inputs[0]);

  printf("0 0 => %f (0)\n", outputs[0]);

  frwrd_network_inputs(outputs, layerAmount, layerSizes, layerActivs, weights, biases, inputs[1]);

  printf("1 0 => %f (1)\n", outputs[0]);

  frwrd_network_inputs(outputs, layerAmount, layerSizes, layerActivs, weights, biases, inputs[2]);

  printf("0 1 => %f (1)\n", outputs[0]);

  frwrd_network_inputs(outputs, layerAmount, layerSizes, layerActivs, weights, biases, inputs[3]);

  printf("1 1 => %f (0)\n\n", outputs[0]);


  float learnRate = 10;
  float momentum = 0.2;
  int batchSize = 4;
  int epochAmount = 1000;

  for(int epochIndex = 0; epochIndex < epochAmount; epochIndex += 1)
  {
    train_network_minbat(layerAmount, layerSizes, layerActivs, weights, biases, learnRate, momentum, (float**) inputs, (float**) targets, batchSize);
  }


  frwrd_network_inputs(outputs, layerAmount, layerSizes, layerActivs, weights, biases, inputs[0]);

  printf("0 0 => %f (0)\n", outputs[0]);

  frwrd_network_inputs(outputs, layerAmount, layerSizes, layerActivs, weights, biases, inputs[1]);

  printf("1 0 => %f (1)\n", outputs[0]);

  frwrd_network_inputs(outputs, layerAmount, layerSizes, layerActivs, weights, biases, inputs[2]);

  printf("0 1 => %f (1)\n", outputs[0]);

  frwrd_network_inputs(outputs, layerAmount, layerSizes, layerActivs, weights, biases, inputs[3]);

  printf("1 1 => %f (0)\n\n", outputs[0]);



  free_float_vector(outputs, layerSizes[layerAmount - 1]);


  free_float_matrix(inputs, 4, 2);
  free_float_matrix(targets, 4, 2);


  free_fmatrix_array(weights, layerAmount - 1, maxShape, maxShape);
  free_float_matrix(biases, layerAmount - 1, maxShape);

	return 0;
}