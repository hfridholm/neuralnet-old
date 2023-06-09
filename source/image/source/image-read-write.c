#include "../image.h"

float** image_pixels_nrmmat(int* width, int* height, const char imgPath[])
{
  int imgWidth, imgHeight, imgComp;
  uint8_t* imgPixels = (uint8_t*) stbi_load(imgPath, &imgWidth, &imgHeight, &imgComp, 0);

  if(imgPixels == NULL)
  {
    return NULL;
  }

  *width = imgWidth;
  *height = imgHeight;
  
  
  int matHeight = imgWidth * imgHeight;
  int matWidth = 3;

  float** matrix = create_float_matrix(matHeight, matWidth);


  for(int yValue = 0; yValue < imgHeight; yValue += 1)
  {
    for(int xValue = 0; xValue < imgWidth; xValue += 1)
    {
      float normX = (float) xValue / (imgWidth - 1);
      float normY = (float) yValue / (imgHeight - 1);

      int index = (yValue * imgWidth + xValue);

      float alpha = (float) imgPixels[index];

      float normAlpha = (float) alpha / 255.0f;

      matrix[index][0] = normX;
      matrix[index][1] = normY;
      matrix[index][2] = normAlpha;
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
