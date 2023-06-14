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
  float* pixels = pixels_nrmliz_vector(&imgWidth, &imgHeight, imgPath);
 
  printf("%s is %dx%d pixels\n", imgPath, imgWidth, imgHeight);

  
  for(int index = 0; index < (imgWidth * imgHeight); index += 1)
  {
    printf("%.2f, ", pixels[index]);
  }
  printf("\n");


  free_float_vector(&pixels, imgWidth * imgHeight);

  return 0;
}
