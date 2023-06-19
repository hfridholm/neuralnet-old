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

  char* program = extract_shift_args(&argc, &argv);
  if(program == NULL) return 1;

  char* filePath = extract_shift_args(&argc, &argv);
  if(filePath == NULL)
  {
    printf("no file was inputted\n");
    return 1;
  }

  printf("%s: %d lines\n", filePath, count_file_lines(filePath));

  return 0;
}
