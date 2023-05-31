#include "../engine/header/engine-include-header.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

bool extract_file_lines(char** fileLines, int* amount, FILE* filePointer)
{
  char buffer[256]; int index = 0;

  for(index = 0; !feof(filePointer); index += 1)
  {
    if(fgets(buffer, sizeof(buffer), filePointer) == NULL) break;

    sscanf(buffer, "%[^\n]%*c", fileLines[index]);
  }
  *amount = index; return true;
}

bool extract_text_file(char** fileLines, int* amount, const char filePath[])
{
  FILE* filePointer = fopen(filePath, "r");

  if(filePointer == NULL) return false;

  bool result = extract_file_lines(fileLines, amount, filePointer);
  
  fclose(filePointer); return result;
}

char** create_string_array(int amount, int length)
{
  char** strArray = malloc(sizeof(char*) * amount);

  for(int index = 0; index < amount; index += 1)
  {
    strArray[index] = malloc(sizeof(char) * length);

    memset(strArray[index], '\0', sizeof(char) * length);
  }
  return strArray;
}

char*** create_string_matrix(int height, int width, int length)
{
  char*** strMatrix = malloc(sizeof(char**) * height);

  for(int index = 0; index < height; index += 1)
  {
    strMatrix[index] = create_string_array(width, length);
  }
  return strMatrix;
}

void free_string_array(char** strArray, int amount, int length)
{
  for(int index = 0; index < amount; index += 1) 
  {
    free(strArray[index]);
  }
  free(strArray);
}

void free_string_matrix(char*** strMatrix, int height, int width, int length)
{
  for(int index = 0; index < height; index += 1)
  {
    free_string_array(strMatrix[index], width, length);
  }
  free(strMatrix);
}

int split_string_tokens(char** tokens, const char string[], const char delim[])
{
  char strCopy[256]; strcpy(strCopy, string);

  char* tempToken = strtok(strCopy, delim);

  int amount;

  for(amount = 0; tempToken != NULL; amount += 1)
  {
    strcpy(tokens[amount], tempToken);

    tempToken = strtok(NULL, delim);
  }
  return amount;
}

int string_array_tokens(char*** tokens, char** strArray, int strAmount, const char delim[])
{
  int tokenAmount = 0;

  for(int index = 0; index < strAmount; index += 1)
  {
    int tempAmount = split_string_tokens(tokens[index], strArray[index], delim);

    if(tempAmount > tokenAmount) tokenAmount = tempAmount;
  }
  return tokenAmount;
}

float** tokens_float_matrix(float** matrix, char*** tokens, int height, int width)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      sscanf(tokens[hIndex][wIndex], "%f", &matrix[hIndex][wIndex]);
    }
  }
  return matrix;
}

bool strmat_index_filter(char*** result, char*** strMatrix, int height, int width, const int indexis[], int amount)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int index = 0; index < amount; index += 1)
    {
      int wIndex = indexis[index];

      if(wIndex >= width) return false;

      strcpy(result[hIndex][index], strMatrix[hIndex][wIndex]);
    }
  }
  return true;
}

bool tokens_inpts_trgts(float** inputs, float** targets, char*** tokens, int height, int width, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount)
{
  char*** inputTokens = create_string_matrix(height, width, 10);
  char*** targetTokens = create_string_matrix(height, width, 10);

  if(!strmat_index_filter(inputTokens, tokens, height, width, inputIndexis, inputAmount));
  if(!strmat_index_filter(targetTokens, tokens, height, width, targetIndexis, targetAmount));

  tokens_float_matrix(inputs, inputTokens, height, inputAmount);
  tokens_float_matrix(targets, targetTokens, height, targetAmount);

  free_string_matrix(inputTokens, height, width, 10);
  free_string_matrix(targetTokens, height, width, 10);

  return true;
}

bool text_file_tokens_t(char*** tokens, int* height, int* width, const char filePath[], const char delim[], char** strArray)
{
  if(!extract_text_file(strArray, height, filePath)) return false;

  *width = string_array_tokens(tokens, strArray, *height, delim);

  return true;
}

bool text_file_tokens(char*** tokens, int* height, int* width, const char filePath[], const char delim[])
{
  char** strArray = create_string_array(256, 256);

  bool result = text_file_tokens_t(tokens, height, width, filePath, delim, strArray);

  free_string_array(strArray, 256, 256); return result;
}

bool csv_inputs_targets_t(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[], char*** tokens)
{
  int width = 0;

  if(!text_file_tokens(tokens, height, &width, filePath, ",")) return false;

  return tokens_inpts_trgts(inputs, targets, tokens, *height, width, inputIndexis, inputAmount, targetIndexis, targetAmount);
}

bool csv_inputs_targets(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[])
{
  char*** tokens = create_string_matrix(100, 10, 10);

  bool result = csv_inputs_targets_t(inputs, targets, height, inputIndexis, inputAmount, targetIndexis, targetAmount, filePath, tokens);

  free_string_matrix(tokens, 100, 10, 10); return result;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

  char filePath[256];

  if(argc >= 2) strcpy(filePath, argv[1]);

  else strcpy(filePath, "../source/datasets/test-dataset.csv");

  int inputNodes = 2;
  int outputNodes = 1;

  int inputIndexis[] = {0, 1};
  int targetIndexis[] = {3};


  float** inputs = create_float_matrix(10, inputNodes);
  float** targets = create_float_matrix(10, outputNodes);


  int batchSize = 0;

  if(!csv_inputs_targets(inputs, targets, &batchSize, inputIndexis, inputNodes, targetIndexis, outputNodes, filePath))
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



	int layerAmount = 3;

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
  free_float_matrix(biases, layerAmount - 1, maxShape);


  free_float_matrix(inputs, 10, inputNodes);
  free_float_matrix(targets, 10, outputNodes);

	return 0;
}