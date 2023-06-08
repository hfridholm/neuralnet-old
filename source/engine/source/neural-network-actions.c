#include "../engine.h"

bool train_network_stcast(float*** weightDeltas, float** biasDeltas, int layerAmount, const int layerSizes[], const Activ layerActivs[], float*** weights, float** biases, float learnRate, float momentum, float* inputs, float* targets, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(layerSizes, layerAmount);

  stcast_weibia_deltas(weightDeltas, biasDeltas, layerAmount, layerSizes, layerActivs, weights, biases, learnRate, momentum, inputs, targets, oldWeightDeltas, oldBiasDeltas);

  addit_elem_fmatarr(weights, weights, weightDeltas, layerAmount - 1, maxShape, maxShape);
  addit_elem_fmatrix(biases, biases, biasDeltas, layerAmount - 1, maxShape);

  return true;
}

void stcast_weibia_deltas(float*** weightDeltas, float** biasDeltas, int layerAmount, const int layerSizes[], const Activ layerActivs[], float*** weights, float** biases, float learnRate, float momentum, float* inputs, float* targets, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(layerSizes, layerAmount);

  float*** weightDerivs = create_fmatrix_array(layerAmount - 1, maxShape, maxShape);
  float** biasDerivs = create_float_matrix(layerAmount - 1, maxShape);

  frwrd_create_derivs(weightDerivs, biasDerivs, layerAmount, layerSizes, layerActivs, weights, biases, inputs, targets);

  create_weibia_deltas(weightDeltas, biasDeltas, layerAmount, layerSizes, learnRate, momentum, weightDerivs, biasDerivs, oldWeightDeltas, oldBiasDeltas);

  free_fmatrix_array(&weightDerivs, layerAmount - 1, maxShape, maxShape);
  free_float_matrix(&biasDerivs, layerAmount - 1, maxShape);
}

void frwrd_create_derivs(float*** weightDerivs, float** biasDerivs, int layerAmount, const int layerSizes[], const Activ layerActivs[], float*** weights, float** biases, float* inputs, float* targets)
{
  int maxShape = maximum_layer_shape(layerSizes, layerAmount);

  float** nodeValues = create_float_matrix(layerAmount, maxShape);

  create_node_values(nodeValues, layerAmount, layerSizes, layerActivs, weights, biases, inputs);

  create_weibia_derivs(weightDerivs, biasDerivs, layerAmount, layerSizes, layerActivs, weights, biases, nodeValues, targets);

  free_float_matrix(&nodeValues, layerAmount, maxShape);
}

void mean_weibia_derivs(float*** meanWeightDerivs, float** meanBiasDerivs, int layerAmount, const int layerSizes[], const Activ layerActivs[], float*** weights, float** biases, float** inputs, float** targets, int batchSize)
{
  int maxShape = maximum_layer_shape(layerSizes, layerAmount);

  float*** weightDerivs = create_fmatrix_array(layerAmount - 1, maxShape, maxShape);
  float** biasDerivs = create_float_matrix(layerAmount - 1, maxShape);

  for(int inputIndex = 0; inputIndex < batchSize; inputIndex += 1)
  {
    frwrd_create_derivs(weightDerivs, biasDerivs, layerAmount, layerSizes, layerActivs, weights, biases, inputs[inputIndex], targets[inputIndex]);

    addit_elem_fmatarr(meanWeightDerivs, meanWeightDerivs, weightDerivs, layerAmount - 1, maxShape, maxShape);
    addit_elem_fmatrix(meanBiasDerivs, meanBiasDerivs, biasDerivs, layerAmount - 1, maxShape);
  }

  free_fmatrix_array(&weightDerivs, layerAmount - 1, maxShape, maxShape);
  free_float_matrix(&biasDerivs, layerAmount - 1, maxShape);

  multi_scale_fmatarr(meanWeightDerivs, meanWeightDerivs, layerAmount - 1, maxShape, maxShape, 1.0f / batchSize);
  multi_scale_fmatrix(meanBiasDerivs, meanBiasDerivs, layerAmount - 1, maxShape, 1.0f / batchSize);
}

void minbat_weibia_deltas(float*** weightDeltas, float** biasDeltas, int layerAmount, const int layerSizes[], const Activ layerActivs[], float*** weights, float** biases, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(layerSizes, layerAmount);

  float*** meanWeightDerivs = create_fmatrix_array(layerAmount - 1, maxShape, maxShape);
  float** meanBiasDerivs = create_float_matrix(layerAmount - 1, maxShape);

  mean_weibia_derivs(meanWeightDerivs, meanBiasDerivs, layerAmount, layerSizes, layerActivs, weights, biases, inputs, targets, batchSize);

  create_weibia_deltas(weightDeltas, biasDeltas, layerAmount, layerSizes, learnRate, momentum, meanWeightDerivs, meanBiasDerivs, oldWeightDeltas, oldBiasDeltas);

  free_fmatrix_array(&meanWeightDerivs, layerAmount - 1, maxShape, maxShape);
  free_float_matrix(&meanBiasDerivs, layerAmount - 1, maxShape);
}

bool train_network_minbat(float*** weightDeltas, float** biasDeltas, int layerAmount, const int layerSizes[], const Activ layerActivs[], float*** weights, float** biases, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(layerSizes, layerAmount);

  minbat_weibia_deltas(weightDeltas, biasDeltas, layerAmount, layerSizes, layerActivs, weights, biases, learnRate, momentum, inputs, targets, batchSize, oldWeightDeltas, oldBiasDeltas);

  addit_elem_fmatarr(weights, weights, weightDeltas, layerAmount - 1, maxShape, maxShape);
  addit_elem_fmatrix(biases, biases, biasDeltas, layerAmount - 1, maxShape);

  return true;
}

bool frwrd_network_inputs(float* outputs, int layerAmount, const int layerSizes[], const Activ layerActivs[], float*** weights, float** biases, float* inputs)
{
  int maxShape = maximum_layer_shape(layerSizes, layerAmount);

  float** nodeValues = create_float_matrix(layerAmount, maxShape);

  create_node_values(nodeValues, layerAmount, layerSizes, layerActivs, weights, biases, inputs);

  copy_float_vector(outputs, nodeValues[layerAmount - 1], layerSizes[layerAmount - 1]);

  free_float_matrix(&nodeValues, layerAmount, maxShape);

  return true;
}

void train_epochs_stcast(int layerAmount, const int layerSizes[], const Activ layerActivs[], float*** weights, float** biases, float learnRate, float momentum, float** inputs, float** targets, int batchSize, int epochAmount)
{
  int maxShape = maximum_layer_shape(layerSizes, layerAmount);

  float*** weightDeltas = create_fmatrix_array(layerAmount - 1, maxShape, maxShape);
  float** biasDeltas = create_float_matrix(layerAmount - 1, maxShape);

  float*** oldWeightDeltas = create_fmatrix_array(layerAmount - 1, maxShape, maxShape);
  float** oldBiasDeltas = create_float_matrix(layerAmount - 1, maxShape);

  for(int epochIndex = 0; epochIndex < epochAmount; epochIndex += 1)
  {
    train_epoch_stcast(weightDeltas, biasDeltas, layerAmount, layerSizes, layerActivs, weights, biases, learnRate, momentum, inputs, targets, batchSize, oldWeightDeltas, oldBiasDeltas);
  }

  free_fmatrix_array(&oldWeightDeltas, layerAmount - 1, maxShape, maxShape);
  free_float_matrix(&oldBiasDeltas, layerAmount - 1, maxShape);

  free_fmatrix_array(&weightDeltas, layerAmount - 1, maxShape, maxShape);
  free_float_matrix(&biasDeltas, layerAmount - 1, maxShape);
}

void train_epoch_stcast(float*** weightDeltas, float** biasDeltas, int layerAmount, const int layerSizes[], const Activ layerActivs[], float*** weights, float** biases, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(layerSizes, layerAmount);

  int* randIndexes = create_integ_array(batchSize);

  random_indexes_array(randIndexes, batchSize);

  for(int index = 0; index < batchSize; index += 1)
  {
    int randIndex = randIndexes[index];

    train_network_stcast(weightDeltas, biasDeltas, layerAmount, layerSizes, layerActivs, weights, biases, learnRate, momentum, inputs[randIndex], targets[randIndex], oldWeightDeltas, oldBiasDeltas);

    copy_fmatrix_array(oldWeightDeltas, weightDeltas, layerAmount - 1, maxShape, maxShape);
    copy_float_matrix(oldBiasDeltas, biasDeltas, layerAmount - 1, maxShape);
  }

  free_integ_array(&randIndexes, batchSize);
}

/* This is just some function that I thought might would be implemented in the future
   void train_stcast(int layerAmount, const int layerSizes[], const int layerActivs[], float*** weights, float** biases, float learnRate, float momentum, float** inputs, float** targets, int batchSize, int maxTime)
   {

   }
 */
