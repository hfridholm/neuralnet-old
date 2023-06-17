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

  int layers = 3;
  int sizes[] = {2, 3, 1};
  int activs[] = {1, 4};

  int maxShape = maximum_layer_shape(sizes, layers);

  float*** weights = create_fmatrix_array(layers - 1, maxShape, maxShape);
  float** biases = create_float_matrix(layers - 1, maxShape);

  Network network = {layers, sizes, activs, weights, biases};

  frwrd_network_inputs(NULL, network, NULL);

  free_fmatrix_array(&weights, layers - 1, maxShape, maxShape);
  free_float_matrix(&biases, layers - 1, maxShape);

  return 0;
}
