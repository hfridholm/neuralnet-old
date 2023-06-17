#include "../image.h"

float* pixels_nrmliz_vector(int* imgWidth, int* imgHeight, const char filePath[])
{
  int tempWidth, tempHeight, tempComp;

  uint8_t* imgPixels = (uint8_t*) stbi_load(filePath, &tempWidth, &tempHeight, &tempComp, 0);

  if(imgPixels == NULL)
  {
    return NULL;
  }

  if(tempComp != 1)
  {
    free(imgPixels);
    return NULL;
  }

  *imgWidth = tempWidth;
  *imgHeight = tempHeight;
  
  int length = (tempWidth * tempHeight);

  float* vector = create_float_vector(length);

  for(int index = 0; index < length; index += 1)
  {
    vector[index] = (float) imgPixels[index] / 255.f;
  }
  
  free(imgPixels);

  return vector;
}

float** pixels_nrmliz_matrix(int* imgWidth, int* imgHeight, const char filePath[])
{
  int tempWidth, tempHeight, tempComp;

  uint8_t* imgPixels = (uint8_t*) stbi_load(filePath, &tempWidth, &tempHeight, &tempComp, 0);

  if(imgPixels == NULL)
  {
    return NULL;
  }

  if(tempComp != 1)
  {
    free(imgPixels);
    return NULL;
  }

  *imgWidth = tempWidth;
  *imgHeight = tempHeight;
  
  
  int matHeight = tempWidth * tempHeight;
  int matWidth = 3;

  float** matrix = create_float_matrix(matHeight, matWidth);


  for(int yValue = 0; yValue < tempHeight; yValue += 1)
  {
    for(int xValue = 0; xValue < tempWidth; xValue += 1)
    {
      int index = (yValue * tempWidth + xValue);

      matrix[index][0] = (float) xValue / (tempWidth - 1);
      matrix[index][1] = (float) yValue / (tempHeight - 1);
      matrix[index][2] = (float) imgPixels[index] / 255.0f;
    }
  }

  free(imgPixels);

  return matrix;
}

bool write_nrmmat_pixels(const char filePath[], float** nrmmat, int width, int height)
{
  float* nrmarr = create_float_vector(width * height);

  matrix_column_vector(nrmarr, nrmmat, width * height, 3, 2);

  bool result = write_nrmarr_pixels(filePath, nrmarr, width, height);

  free_float_vector(&nrmarr, width * height);

  return result;
}

bool write_nrmarr_pixels(const char filePath[], float* nrmarr, int width, int height)
{
  uint8_t* pixels = malloc(sizeof(uint8_t) * width * height);
 
  for(int index = 0; index < (width * height); index += 1)
  {
    pixels[index] = (uint8_t) (nrmarr[index] * 255); 
  }

  if(!stbi_write_png(filePath, width, height, 1, pixels, width * sizeof(uint8_t)))
  {
    printf("Error: stbi_write_png\n");
  
    free(pixels);

    return false;
  }
  
  free(pixels);

  return true;
}