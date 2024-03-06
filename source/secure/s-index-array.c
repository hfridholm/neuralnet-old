#include "../secure.h"

/*
 * Return random index between min and max
 */
size_t index_random_create(size_t min, size_t max)
{
  float fraction = ((float) rand() / (float) RAND_MAX);

  return (fraction * (max - min) + min);
}

/*
 * Create array allocated on the HEAP with values as indexes
 * Also clean the memory using memset
 *
 * RETURN
 * - SUCCESS | size_t* array
 * - ERROR   | NULL
 */
size_t* index_array_create(size_t amount)
{
  if(amount <= 0) return NULL;

  size_t* array = malloc(sizeof(size_t) * amount);

  if(array == NULL) return NULL;

  for(size_t index = 0; index < amount; index++)
  {
    array[index] = index;
  }
  return array;
}

/*
 * Free index array from the HEAP using free
 * Also assigns NULL to pointer
 */
void index_array_free(size_t** array, size_t amount)
{
  free(*array);

  *array = NULL;
}

/*
 * Swap two indexes in index array
 */
static size_t* index_array_switch_index(size_t* array, size_t index1, size_t index2)
{
  size_t temp = array[index1];

  array[index1] = array[index2];
  array[index2] = temp;

  return array; 
}

/*
 * Shuffle array of indexes
 *
 * RETURN
 * - SUCCESS | size_t* array
 * - ERROR   | NULL
 */
size_t* index_array_shuffle(size_t* array, size_t amount)
{
  if(array == NULL) return NULL;

  for(size_t index = 0; index < amount; index++)
  {
    size_t random = index_random_create(0, amount - 1);

    array = index_array_switch_index(array, index, random);
  }
  return array;
}
