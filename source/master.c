#include "adjust.h"
#include "persue.h"
#include "secure.h"

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
  float** matrix = pixels_nrmliz_matrix_read(&imgWidth, &imgHeight, imgPath);

  if(matrix == NULL)
  {
    printf("Could not parse image\n");
    return 1;
  }


  float** inputs = float_matrix_create(imgWidth * imgHeight, 2);
  float** targets = float_matrix_create(imgWidth * imgHeight, 1);

  float_matrix_filter_index(inputs, matrix, imgWidth * imgHeight, 3, (int[]) {0, 1}, 2);
  float_matrix_filter_index(targets, matrix, imgWidth * imgHeight, 3, (int[]) {2}, 1);



  int sizes[] = {2, 8, 8, 16, 8, 8, 1};
  Activ activs[] = {ACTIV_RELU, ACTIV_RELU, ACTIV_RELU, ACTIV_RELU, ACTIV_RELU,  ACTIV_SIGMOID};

  int layers = sizeof(sizes) / sizeof(int);

  printf("layers: %d\n", layers);

  int maxShape = network_sizes_maximum(sizes, layers);

  float*** weights = float_matarr_random_create(layers - 1, maxShape, maxShape, -1.0f, +1.0f);
  float** biases = float_matrix_random_create(layers - 1, maxShape, -1.0f, +1.0f);

  Network network = {layers, sizes, activs, weights, biases};


  float learnRate = 0.0009;
  float momentum = 0.1;


  network_train_stcast_epochs(network, learnRate, momentum, inputs, targets, imgWidth * imgHeight, 0, 20 * 1000);


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

      network_forward(output, network, outInputs);

      int index = (yValue * outWidth + xValue);

      outPixels[index] = output[0];
    }
  }


  pixels_nrmliz_array_write("../assets/result101.png", outPixels, outWidth, outHeight);

  float_vector_free(&outPixels, outWidth * outHeight);




  float_matarr_free(&network.weights, network.layers - 1, maxShape, maxShape);
  float_matrix_free(&network.biases, network.layers - 1, maxShape);


  float_matrix_free(&inputs, imgWidth * imgHeight, 2);
  float_matrix_free(&targets, imgWidth * imgHeight, 1);


  float_matrix_free(&matrix, imgWidth * imgHeight, 3);
  
  return 0;
}
