#include "../secure.h"

int index_random_create(int min, int max)
{
  float fraction = ((float) rand() / (float) RAND_MAX);

  return (fraction * (max - min) + min);
}

int* index_array_create(int amount)
{
  if(amount < 0) return NULL;

  int* array = malloc(sizeof(int) * amount);

  if(array == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    array[index] = index;
  }
  return array;
}

void index_array_free(int** array, int amount)
{
  free(*array);
  *array = NULL;
}

static int* index_array_switch_index(int* array, int index1, int index2)
{
  int temp = array[index1];
  array[index1] = array[index2];
  array[index2] = temp;

  return array; 
}

int* index_array_shuffle(int* array, int amount)
{
  if(array == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    int randIndex = index_random_create(0, amount - 1);

    index_array_switch_index(array, index, randIndex);
  }
  return array;
}
