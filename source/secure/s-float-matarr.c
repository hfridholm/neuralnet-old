#include "../secure.h"

float*** create_fmatrix_array(int amount, int height, int width)
{
  if(amount < 0 || height < 0 || width < 0) return NULL;
 
  float*** matarr = malloc(sizeof(float**) * amount);

  if(matarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    matarr[index] = create_float_matrix(height, width);
  }
  return matarr;
}

void free_fmatrix_array(float**** matarr, int amount, int height, int width)
{
  if(*matarr == NULL) return;

  for(int index = 0; index < amount; index += 1)
  {
    free_float_matrix((*matarr) + index, height, width);
  }
  free(*matarr);
  *matarr = NULL;
}

float*** create_random_fmatarr(int amount, int height, int width, float minimum, float maximum)
{
  float*** matarr = create_fmatrix_array(amount, height, width);

  return fill_fmatarr_random(matarr, amount, height, width, minimum, maximum);
}

float*** fill_fmatarr_random(float*** matarr, int amount, int height, int width, float minimum, float maximum)
{
  if(matarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    fill_fmatrix_random(matarr[index], height, width, minimum, maximum);
  }
  return matarr;
}

float*** addit_elem_fmatarr(float*** result, float*** matarr1, float*** matarr2, int amount, int height, int width)
{
  if(result == NULL || matarr1 == NULL || matarr2 == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    addit_elem_fmatrix(result[index], matarr1[index], matarr2[index], height, width);
  }
  return result;
}

float*** multi_scale_fmatarr(float*** result, float*** matarr, int amount, int height, int width, float scalor)
{
  if(result == NULL || matarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    multi_scale_fmatrix(result[index], matarr[index], height, width, scalor);
  }
  return result;
}

float*** copy_fmatrix_array(float*** destin, float*** matarr, int amount, int height, int width)
{
  if(destin == NULL || matarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    copy_float_matrix(destin[index], matarr[index], height, width);
  }
  return destin;
}

bool print_fmatrix_array(float*** matarr, int amount, int height, int width)
{
  if(matarr == NULL) return false;

  for(int index = 0; index < amount; index += 1)
  {
    if(!print_float_matrix(matarr[index], height, width)) return false;

    printf("\n");
  }
  return true;
}
