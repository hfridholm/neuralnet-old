#include "../engine/header/engine-include-header.h"

int main(int argc, char* argv[])
{
  srand(time(NULL));

  char filePath[256];

  if(argc >= 2) strcpy(filePath, argv[1]);

  else strcpy(filePath, "../source/datasets/test-dataset.csv");

  int inputNodes = 2;
  int outputNodes = 1;

  // Fix input system for input and output nodes
  char* inputHeaders[] = {"number1", "grupp BIG"};
  char* targetHeaders[] = {"Team 4"};

  int lines = 0;
  if(!count_file_lines(&lines, filePath)) return 1;

  float** inputs = create_float_matrix(lines, inputNodes);
  float** targets = create_float_matrix(lines, outputNodes);


  int batchSize = 0;

  if(!csv_headers_inptrgs(inputs, targets, &batchSize, inputHeaders, inputNodes, targetHeaders, outputNodes, filePath))
  {
    printf("Error csv_inputs_targets\n");
  }


  for(int index = 0; index < batchSize; index += 1)
  {
    printf("Inputs: (");
    for(int iIndex = 0; iIndex < inputNodes; iIndex += 1)
    {
      printf("%.2f ", inputs[index][iIndex]);
    }
    printf(") ");

    printf("Targets: (");
    for(int tIndex = 0; tIndex < outputNodes; tIndex += 1)
    {
      printf("%.2f ", targets[index][tIndex]);
    }
    printf(")\n");
  }



  /*int layerAmount = 3;

  int layerSizes[] = {inputNodes, 4, outputNodes};
  int layerActivs[] = {1, 1, 1};

  int maxShape = maximum_layer_shape(layerSizes, layerAmount);

  float*** weights = create_fmatrix_array(layerAmount - 1, maxShape, maxShape);
  float** biases = create_float_matrix(layerAmount - 1, maxShape);

  weights = fill_fmatarr_random(weights, layerAmount - 1, maxShape, maxShape, -1.0, +1.0);
  biases = fill_fmatrix_random(biases, layerAmount - 1, maxShape, -1.0, +1.0);




  float learnRate = 0.7;
  float momentum = 0.5;
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
    printf(") -> ");

    printf("(");
    for(int oIndex = 0; oIndex < layerSizes[layerAmount - 1]; oIndex += 1)
    {
      printf("%.2f ", outputs[oIndex]);
    }
    printf(")\n");
  }
  printf("\n");


  train_epochs_stcast(layerAmount, layerSizes, layerActivs, weights, biases, learnRate, momentum, inputs, targets, batchSize, epochAmount);


  for(int index = 0; index < batchSize; index += 1)
  {
    frwrd_network_inputs(outputs, layerAmount, layerSizes, layerActivs, weights, biases, inputs[index]);

    printf("(");
    for(int iIndex = 0; iIndex < layerSizes[0]; iIndex += 1)
    {
      printf("%.2f ", inputs[index][iIndex]);
    }
    printf(") -> ");

    printf("(");
    for(int oIndex = 0; oIndex < layerSizes[layerAmount - 1]; oIndex += 1)
    {
      printf("%.2f ", outputs[oIndex]);
    }
    printf(")\n");
  }
  printf("\n");



  free_float_vector(outputs, layerSizes[layerAmount - 1]);


  free_fmatrix_array(weights, layerAmount - 1, maxShape, maxShape);
  free_float_matrix(biases, layerAmount - 1, maxShape);*/


  free_float_matrix(inputs, lines, inputNodes);
  free_float_matrix(targets, lines, outputNodes);

  return 0;
}
