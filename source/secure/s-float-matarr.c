#include "../secure.h"

float*** float_matarr_create(int amount, int height, int width)
{
  if(amount < 0 || height < 0 || width < 0) return NULL;
 
  float*** matarr = malloc(sizeof(float**) * amount);

  if(matarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    matarr[index] = float_matrix_create(height, width);
  }
  return matarr;
}

void float_matarr_free(float**** matarr, int amount, int height, int width)
{
  if(*matarr == NULL) return;

  for(int index = 0; index < amount; index += 1)
  {
    float_matrix_free((*matarr) + index, height, width);
  }
  free(*matarr);
  *matarr = NULL;
}

float*** float_matarr_random_create(int amount, int height, int width, float minimum, float maximum)
{
  float*** matarr = float_matarr_create(amount, height, width);

  return float_matarr_random_fill(matarr, amount, height, width, minimum, maximum);
}

float*** float_matarr_random_fill(float*** matarr, int amount, int height, int width, float minimum, float maximum)
{
  if(matarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    float_matrix_random_fill(matarr[index], height, width, minimum, maximum);
  }
  return matarr;
}

float*** float_matarr_elem_addit(float*** result, float*** matarr1, float*** matarr2, int amount, int height, int width)
{
  if(result == NULL || matarr1 == NULL || matarr2 == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    float_matrix_elem_addit(result[index], matarr1[index], matarr2[index], height, width);
  }
  return result;
}

float*** float_matarr_scale_multi(float*** result, float*** matarr, int amount, int height, int width, float scalor)
{
  if(result == NULL || matarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    float_matrix_scale_multi(result[index], matarr[index], height, width, scalor);
  }
  return result;
}

float*** float_matarr_copy(float*** destin, float*** matarr, int amount, int height, int width)
{
  if(destin == NULL || matarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    float_matrix_copy(destin[index], matarr[index], height, width);
  }
  return destin;
}

bool float_matarr_print(float*** matarr, int amount, int height, int width)
{
  if(matarr == NULL) return false;

  for(int index = 0; index < amount; index += 1)
  {
    if(!float_matrix_print(matarr[index], height, width)) return false;

    printf("\n");
  }
  return true;
}
