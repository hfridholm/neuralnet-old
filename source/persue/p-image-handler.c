#include "../persue.h"

bool pixels_nrmliz_array_write(const char filePath[], float* nrmarr, int width, int height)
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

float* pixels_nrmliz_array_read(int* imgWidth, int* imgHeight, const char filePath[])
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

  float* vector = float_vector_create(length);

  for(int index = 0; index < length; index += 1)
  {
    vector[index] = (float) imgPixels[index] / 255.f;
  }
  
  free(imgPixels);

  return vector;
}

float** pixels_nrmliz_matrix_read(int* imgWidth, int* imgHeight, const char filePath[])
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

  float** matrix = float_matrix_create(matHeight, matWidth);


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

bool pixels_nrmliz_matrix_write(const char filePath[], float** nrmmat, int width, int height)
{
  float* nrmarr = float_vector_create(width * height);

  float_matrix_column_vector(nrmarr, nrmmat, width * height, 3, 2);

  bool result = pixels_nrmliz_array_write(filePath, nrmarr, width, height);

  float_vector_free(&nrmarr, width * height);

  return result;
}
