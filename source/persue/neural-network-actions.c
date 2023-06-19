#include "../persue.h"

int maximum_layer_shape(const int networkSizes[], int networkLayers)
{
  int maxShape = 0;

  for(int layerIndex = 0; layerIndex < networkLayers; layerIndex += 1)
  {
    if(networkSizes[layerIndex] <= maxShape) continue;

    maxShape = networkSizes[layerIndex];
  }
  return maxShape;
}

void addit_oldwei_deltas(float*** weightDeltas, int networkLayers, int maxShape, float momentum, float*** oldWeightDeltas)
{
  float*** tempWeightDeltas = create_fmatrix_array(networkLayers - 1, maxShape, maxShape);

  multi_scale_fmatarr(tempWeightDeltas, oldWeightDeltas, networkLayers - 1, maxShape, maxShape, momentum);

  addit_elem_fmatarr(weightDeltas, weightDeltas, tempWeightDeltas, networkLayers - 1, maxShape, maxShape);

  free_fmatrix_array(&tempWeightDeltas, networkLayers - 1, maxShape, maxShape);
}

void addit_oldbia_deltas(float** biasDeltas, int networkLayers, int maxShape, float momentum, float** oldBiasDeltas)
{
  float** tempBiasDeltas = create_float_matrix(networkLayers - 1, maxShape);

  multi_scale_fmatrix(tempBiasDeltas, oldBiasDeltas, networkLayers - 1, maxShape, momentum);

  addit_elem_fmatrix(biasDeltas, biasDeltas, tempBiasDeltas, networkLayers - 1, maxShape);

  free_float_matrix(&tempBiasDeltas, networkLayers - 1, maxShape);
}

bool create_weibia_deltas(float*** weightDeltas, float** biasDeltas, int networkLayers, int maxShape, float learnRate, float momentum, float*** weightDerivs, float** biasDerivs, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  multi_scale_fmatarr(weightDeltas, weightDerivs, networkLayers - 1, maxShape, maxShape, -learnRate);

  if(oldWeightDeltas != NULL)
  {
    addit_oldwei_deltas(weightDeltas, networkLayers, maxShape, momentum, oldWeightDeltas);
  }

  multi_scale_fmatrix(biasDeltas, biasDerivs, networkLayers - 1, maxShape, -learnRate);

  if(oldBiasDeltas != NULL)
  {
    addit_oldbia_deltas(biasDeltas, networkLayers, maxShape, momentum, oldBiasDeltas);
  }

  return true;
}

bool create_node_derivs(float** nodeDerivs, Network network, float** nodeValues, float* targets)
{
  cross_entropy_derivs(nodeDerivs[network.layers - 2], nodeValues[network.layers - 1], targets, network.sizes[network.layers - 1]);

  apply_activ_derivs(nodeDerivs[network.layers - 2], nodeValues[network.layers - 1], network.sizes[network.layers - 1], network.activs[network.layers - 2]);

  for(int layerIndex = (network.layers - 1); layerIndex >= 2; layerIndex -= 1)
  {
    int layerHeight = network.sizes[layerIndex];
    int layerWidth = network.sizes[layerIndex - 1];

    float** weightTransp = create_float_matrix(layerWidth, layerHeight);

    transp_float_matrix(weightTransp, network.weights[layerIndex - 1], layerHeight, layerWidth);

    dotprod_fmatrix_vector(nodeDerivs[layerIndex - 2], weightTransp, layerWidth, layerHeight, nodeDerivs[layerIndex - 1], layerHeight);

    free_float_matrix(&weightTransp, layerWidth, layerHeight);

    apply_activ_derivs(nodeDerivs[layerIndex - 2], nodeValues[layerIndex - 1], layerWidth, network.activs[layerIndex - 2]);
  }
  return true;
}

bool create_weibia_derivs(float*** weightDerivs, float** biasDerivs, Network network, float** nodeValues, float* targets)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float** nodeDerivs = create_float_matrix(network.layers - 1, maxShape);

  create_node_derivs(nodeDerivs, network, nodeValues, targets);

  for(int layerIndex = (network.layers - 1); layerIndex >= 1; layerIndex -= 1)
  {
    int layerHeight = network.sizes[layerIndex];
    int layerWidth = network.sizes[layerIndex - 1];

    dotprod_float_vector(weightDerivs[layerIndex - 1], nodeDerivs[layerIndex - 1], layerHeight, nodeValues[layerIndex - 1], layerWidth);

    copy_float_vector(biasDerivs[layerIndex - 1], nodeDerivs[layerIndex - 1], layerHeight);
  }

  free_float_matrix(&nodeDerivs, network.layers - 1, maxShape);

  return true;
}

bool create_node_values(float** nodeValues, Network network, float* inputs)
{
  copy_float_vector(nodeValues[0], inputs, network.sizes[0]);

  for(int layerIndex = 1; layerIndex < network.layers; layerIndex += 1)
  {
    int layerHeight = network.sizes[layerIndex];
    int layerWidth = network.sizes[layerIndex - 1];

    dotprod_fmatrix_vector(nodeValues[layerIndex], network.weights[layerIndex - 1], layerHeight, layerWidth, nodeValues[layerIndex - 1], layerWidth);

    addit_elem_fvector(nodeValues[layerIndex], nodeValues[layerIndex], network.biases[layerIndex - 1], layerHeight);

    layer_activ_values(nodeValues[layerIndex], nodeValues[layerIndex], layerHeight, network.activs[layerIndex - 1]);
  }
  return true;
}

void frwrd_create_derivs(float*** weightDerivs, float** biasDerivs, Network network, float* inputs, float* targets)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float** nodeValues = create_float_matrix(network.layers, maxShape);

  create_node_values(nodeValues, network, inputs);

  create_weibia_derivs(weightDerivs, biasDerivs, network, nodeValues, targets);

  free_float_matrix(&nodeValues, network.layers, maxShape);
}

void stcast_weibia_deltas(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float* inputs, float* targets, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float*** weightDerivs = create_fmatrix_array(network.layers - 1, maxShape, maxShape);
  float** biasDerivs = create_float_matrix(network.layers - 1, maxShape);

  frwrd_create_derivs(weightDerivs, biasDerivs, network, inputs, targets);

  create_weibia_deltas(weightDeltas, biasDeltas, network.layers, maxShape, learnRate, momentum, weightDerivs, biasDerivs, oldWeightDeltas, oldBiasDeltas);

  free_fmatrix_array(&weightDerivs, network.layers - 1, maxShape, maxShape);
  free_float_matrix(&biasDerivs, network.layers - 1, maxShape);
}

// Tip: Check pointer arguments before assigning
bool train_network_stcast(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float* inputs, float* targets, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  stcast_weibia_deltas(weightDeltas, biasDeltas, network, learnRate, momentum, inputs, targets, oldWeightDeltas, oldBiasDeltas);

  addit_elem_fmatarr(network.weights, network.weights, weightDeltas, network.layers - 1, maxShape, maxShape);
  addit_elem_fmatrix(network.biases, network.biases, biasDeltas, network.layers - 1, maxShape);

  return true;
}

// Tip: store mean weight/bias derivs in temp variables before asigning pointers
// Tip: Check pointer arguments before assigning
void mean_weibia_derivs(float*** meanWeightDerivs, float** meanBiasDerivs, Network network, float** inputs, float** targets, int batchSize)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float*** weightDerivs = create_fmatrix_array(network.layers - 1, maxShape, maxShape);
  float** biasDerivs = create_float_matrix(network.layers - 1, maxShape);

  for(int inputIndex = 0; inputIndex < batchSize; inputIndex += 1)
  {
    frwrd_create_derivs(weightDerivs, biasDerivs, network, inputs[inputIndex], targets[inputIndex]);

    addit_elem_fmatarr(meanWeightDerivs, meanWeightDerivs, weightDerivs, network.layers - 1, maxShape, maxShape);
    addit_elem_fmatrix(meanBiasDerivs, meanBiasDerivs, biasDerivs, network.layers - 1, maxShape);
  }

  free_fmatrix_array(&weightDerivs, network.layers - 1, maxShape, maxShape);
  free_float_matrix(&biasDerivs, network.layers - 1, maxShape);

  multi_scale_fmatarr(meanWeightDerivs, meanWeightDerivs, network.layers - 1, maxShape, maxShape, 1.0f / batchSize);
  multi_scale_fmatrix(meanBiasDerivs, meanBiasDerivs, network.layers - 1, maxShape, 1.0f / batchSize);
}

void minbat_weibia_deltas(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float*** meanWeightDerivs = create_fmatrix_array(network.layers - 1, maxShape, maxShape);
  float** meanBiasDerivs = create_float_matrix(network.layers - 1, maxShape);

  mean_weibia_derivs(meanWeightDerivs, meanBiasDerivs, network, inputs, targets, batchSize);

  create_weibia_deltas(weightDeltas, biasDeltas, network.layers, maxShape, learnRate, momentum, meanWeightDerivs, meanBiasDerivs, oldWeightDeltas, oldBiasDeltas);

  free_fmatrix_array(&meanWeightDerivs, network.layers - 1, maxShape, maxShape);
  free_float_matrix(&meanBiasDerivs, network.layers - 1, maxShape);
}

// Tip: Check pointer arguments before assigning
bool train_network_minbat(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  minbat_weibia_deltas(weightDeltas, biasDeltas, network, learnRate, momentum, inputs, targets, batchSize, oldWeightDeltas, oldBiasDeltas);

  addit_elem_fmatarr(network.weights, network.weights, weightDeltas, network.layers - 1, maxShape, maxShape);
  addit_elem_fmatrix(network.biases, network.biases, biasDeltas, network.layers - 1, maxShape);

  return true;
}

// Tip: Check pointer arguments before assigning
bool frwrd_network_inputs(float* outputs, Network network, float* inputs)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float** nodeValues = create_float_matrix(network.layers, maxShape);

  create_node_values(nodeValues, network, inputs);

  copy_float_vector(outputs, nodeValues[network.layers - 1], network.sizes[network.layers - 1]);

  free_float_matrix(&nodeValues, network.layers, maxShape);

  return true;
}

void train_epoch_stcast(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  int* randIndexes = create_integ_array(batchSize);

  random_indexes_array(randIndexes, batchSize);

  for(int index = 0; index < batchSize; index += 1)
  {
    int randIndex = randIndexes[index];

    train_network_stcast(weightDeltas, biasDeltas, network, learnRate, momentum, inputs[randIndex], targets[randIndex], oldWeightDeltas, oldBiasDeltas);

    copy_fmatrix_array(oldWeightDeltas, weightDeltas, network.layers - 1, maxShape, maxShape);
    copy_float_matrix(oldBiasDeltas, biasDeltas, network.layers - 1, maxShape);
  }

  free_integ_array(&randIndexes, batchSize);
}

void train_epochs_stcast(Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, int epochAmount)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float*** weightDeltas = create_fmatrix_array(network.layers - 1, maxShape, maxShape);
  float** biasDeltas = create_float_matrix(network.layers - 1, maxShape);

  float*** oldWeightDeltas = create_fmatrix_array(network.layers - 1, maxShape, maxShape);
  float** oldBiasDeltas = create_float_matrix(network.layers - 1, maxShape);

  for(int epochIndex = 0; epochIndex < epochAmount; epochIndex += 1)
  {
    train_epoch_stcast(weightDeltas, biasDeltas, network, learnRate, momentum, inputs, targets, batchSize, oldWeightDeltas, oldBiasDeltas);
  }

  free_fmatrix_array(&oldWeightDeltas, network.layers - 1, maxShape, maxShape);
  free_float_matrix(&oldBiasDeltas, network.layers - 1, maxShape);

  free_fmatrix_array(&weightDeltas, network.layers - 1, maxShape, maxShape);
  free_float_matrix(&biasDeltas, network.layers - 1, maxShape);
}
