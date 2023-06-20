#include "adjust.h"
#include "persue.h"
#include "secure.h"
#include "review.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

char* extract_shift_args(int* argc, char*** argv)
{
  if(*argc <= 0) return NULL;

  char* result = **argv;
  (*argc) -= 1;
  (*argv) += 1;
  return result;
}

int main(int argc, char* argv[])
{
  srand(time(NULL));

  //const char* program =
  extract_shift_args(&argc, &argv);

  const char* imgPath = extract_shift_args(&argc, &argv);

  if(imgPath == NULL)
  {
    printf("No file was imputted\n");
    return 1;
  }

  
  int imgWidth, imgHeight;
  float** matrix = pixels_nrmliz_matrix(&imgWidth, &imgHeight, imgPath);

  if(matrix == NULL)
  {
    printf("Could not parse image\n");
    return 1;
  }


  float** inputs = float_matrix_create(imgWidth * imgHeight, 2);
  float** targets = float_matrix_create(imgWidth * imgHeight, 1);

  float_matrix_filter_index(inputs, matrix, imgWidth * imgHeight, 3, (int[]) {0, 1}, 2);
  float_matrix_filter_index(targets, matrix, imgWidth * imgHeight, 3, (int[]) {2}, 1);



  int layers = 4;
  int sizes[] = {2, 7, 4, 1};
  Activ activs[] = {ACTIV_SIGMOID, ACTIV_SIGMOID, ACTIV_SIGMOID};

  int maxShape = maximum_layer_shape(sizes, layers);

  float*** weights = float_matarr_random_create(layers - 1, maxShape, maxShape, -1.0f, +1.0f);
  float** biases = float_matrix_random_create(layers - 1, maxShape, -1.0f, +1.0f);

  Network network = {layers, sizes, activs, weights, biases};


  float learnRate = 0.1;
  float momentum = 0.1;
  int epochAmount = 10000;


  train_epochs_stcast(network, learnRate, momentum, inputs, targets, imgWidth * imgHeight, epochAmount);



  int outWidth = 256;
  int outHeight = 256;

  float* outPixels = float_vector_create(outWidth * outHeight);


  for(int yValue = 0; yValue < outHeight; yValue += 1)
  {
    for(int xValue = 0; xValue < outWidth; xValue += 1)
    {
      float output[10];

      float normX = (float) xValue / (outWidth - 1);
      float normY = (float) yValue / (outHeight - 1);

      float outInputs[] = {normX, normY};

      frwrd_network_inputs(output, network, outInputs);

      int index = (yValue * outWidth + xValue);

      outPixels[index] = output[0];
    }
  }


  write_nrmarr_pixels("../assets/result101.png", outPixels, outWidth, outHeight);

  float_vector_free(&outPixels, outWidth * outHeight);




  float_matarr_free(&network.weights, network.layers - 1, maxShape, maxShape);
  float_matrix_free(&network.biases, network.layers - 1, maxShape);


  float_matrix_free(&inputs, imgWidth * imgHeight, 2);
  float_matrix_free(&targets, imgWidth * imgHeight, 1);


  float_matrix_free(&matrix, imgWidth * imgHeight, 3);
  
  return 0;
}