#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../engine/engine.h"
#include "../dataset/dataset.h"
#include "../image/image.h"

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


  float** inputs = create_float_matrix(imgWidth * imgHeight, 2);
  float** targets = create_float_matrix(imgWidth * imgHeight, 1);

  matrix_index_filter(inputs, matrix, imgWidth * imgHeight, 3, (int[]) {0, 1}, 2);
  matrix_index_filter(targets, matrix, imgWidth * imgHeight, 3, (int[]) {2}, 1);



  int layers = 4;
  int sizes[] = {2, 7, 4, 1};
  Activ activs[] = {ACTIV_SIGMOID, ACTIV_SIGMOID, ACTIV_SIGMOID};

  int maxShape = maximum_layer_shape(sizes, layers);

  float*** weights = create_random_fmatarr(layers - 1, maxShape, maxShape, -1.0f, +1.0f);
  float** biases = create_random_fmatrix(layers - 1, maxShape, -1.0f, +1.0f);

  Network network = {layers, sizes, activs, weights, biases};


  float learnRate = 0.1;
  float momentum = 0.1;
  int epochAmount = 10000;


  train_epochs_stcast(network, learnRate, momentum, inputs, targets, imgWidth * imgHeight, epochAmount);



  int outWidth = 256;
  int outHeight = 256;

  float* outPixels = create_float_vector(outWidth * outHeight);


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


  write_nrmarr_pixels("../source/assets/result101.png", outPixels, outWidth, outHeight);

  free_float_vector(&outPixels, outWidth * outHeight);




  free_fmatrix_array(&network.weights, network.layers - 1, maxShape, maxShape);
  free_float_matrix(&network.biases, network.layers - 1, maxShape);


  free_float_matrix(&inputs, imgWidth * imgHeight, 2);
  free_float_matrix(&targets, imgWidth * imgHeight, 1);


  free_float_matrix(&matrix, imgWidth * imgHeight, 3);
  
  return 0;
}
