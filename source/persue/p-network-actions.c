#include "../persue.h"
#include "p-activs-intern.h"

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

static void addit_oldwei_deltas(float*** weightDeltas, int networkLayers, int maxShape, float momentum, float*** oldWeightDeltas)
{
  float*** tempWeightDeltas = float_matarr_create(networkLayers - 1, maxShape, maxShape);

  float_matarr_scale_multi(tempWeightDeltas, oldWeightDeltas, networkLayers - 1, maxShape, maxShape, momentum);

  float_matarr_elem_addit(weightDeltas, weightDeltas, tempWeightDeltas, networkLayers - 1, maxShape, maxShape);

  float_matarr_free(&tempWeightDeltas, networkLayers - 1, maxShape, maxShape);
}

static void addit_oldbia_deltas(float** biasDeltas, int networkLayers, int maxShape, float momentum, float** oldBiasDeltas)
{
  float** tempBiasDeltas = float_matrix_create(networkLayers - 1, maxShape);

  float_matrix_scale_multi(tempBiasDeltas, oldBiasDeltas, networkLayers - 1, maxShape, momentum);

  float_matrix_elem_addit(biasDeltas, biasDeltas, tempBiasDeltas, networkLayers - 1, maxShape);

  float_matrix_free(&tempBiasDeltas, networkLayers - 1, maxShape);
}

static bool create_weibia_deltas(float*** weightDeltas, float** biasDeltas, int networkLayers, int maxShape, float learnRate, float momentum, float*** weightDerivs, float** biasDerivs, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  float_matarr_scale_multi(weightDeltas, weightDerivs, networkLayers - 1, maxShape, maxShape, -learnRate);

  if(oldWeightDeltas != NULL)
  {
    addit_oldwei_deltas(weightDeltas, networkLayers, maxShape, momentum, oldWeightDeltas);
  }

  float_matrix_scale_multi(biasDeltas, biasDerivs, networkLayers - 1, maxShape, -learnRate);

  if(oldBiasDeltas != NULL)
  {
    addit_oldbia_deltas(biasDeltas, networkLayers, maxShape, momentum, oldBiasDeltas);
  }

  return true;
}

static bool create_node_derivs(float** nodeDerivs, Network network, float** nodeValues, float* targets)
{
  cross_entropy_derivs(nodeDerivs[network.layers - 2], nodeValues[network.layers - 1], targets, network.sizes[network.layers - 1]);

  apply_activ_derivs(nodeDerivs[network.layers - 2], nodeValues[network.layers - 1], network.sizes[network.layers - 1], network.activs[network.layers - 2]);

  for(int layerIndex = (network.layers - 1); layerIndex >= 2; layerIndex -= 1)
  {
    int layerHeight = network.sizes[layerIndex];
    int layerWidth = network.sizes[layerIndex - 1];

    float** weightTransp = float_matrix_create(layerWidth, layerHeight);

    float_matrix_transp(weightTransp, network.weights[layerIndex - 1], layerHeight, layerWidth);

    float_matrix_vector_dotprod(nodeDerivs[layerIndex - 2], weightTransp, layerWidth, layerHeight, nodeDerivs[layerIndex - 1], layerHeight);

    float_matrix_free(&weightTransp, layerWidth, layerHeight);

    apply_activ_derivs(nodeDerivs[layerIndex - 2], nodeValues[layerIndex - 1], layerWidth, network.activs[layerIndex - 2]);
  }
  return true;
}

static bool create_weibia_derivs(float*** weightDerivs, float** biasDerivs, Network network, float** nodeValues, float* targets)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float** nodeDerivs = float_matrix_create(network.layers - 1, maxShape);

  create_node_derivs(nodeDerivs, network, nodeValues, targets);

  for(int layerIndex = (network.layers - 1); layerIndex >= 1; layerIndex -= 1)
  {
    int layerHeight = network.sizes[layerIndex];
    int layerWidth = network.sizes[layerIndex - 1];

    float_vector_dotprod(weightDerivs[layerIndex - 1], nodeDerivs[layerIndex - 1], layerHeight, nodeValues[layerIndex - 1], layerWidth);

    float_vector_copy(biasDerivs[layerIndex - 1], nodeDerivs[layerIndex - 1], layerHeight);
  }

  float_matrix_free(&nodeDerivs, network.layers - 1, maxShape);

  return true;
}

static bool create_node_values(float** nodeValues, Network network, float* inputs)
{
  float_vector_copy(nodeValues[0], inputs, network.sizes[0]);

  for(int layerIndex = 1; layerIndex < network.layers; layerIndex += 1)
  {
    int layerHeight = network.sizes[layerIndex];
    int layerWidth = network.sizes[layerIndex - 1];

    float_matrix_vector_dotprod(nodeValues[layerIndex], network.weights[layerIndex - 1], layerHeight, layerWidth, nodeValues[layerIndex - 1], layerWidth);

    float_vector_elem_addit(nodeValues[layerIndex], nodeValues[layerIndex], network.biases[layerIndex - 1], layerHeight);

    layer_activ_values(nodeValues[layerIndex], nodeValues[layerIndex], layerHeight, network.activs[layerIndex - 1]);
  }
  return true;
}

static void frwrd_create_derivs(float*** weightDerivs, float** biasDerivs, Network network, float* inputs, float* targets)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float** nodeValues = float_matrix_create(network.layers, maxShape);

  create_node_values(nodeValues, network, inputs);

  create_weibia_derivs(weightDerivs, biasDerivs, network, nodeValues, targets);

  float_matrix_free(&nodeValues, network.layers, maxShape);
}

static void stcast_weibia_deltas(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float* inputs, float* targets, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float*** weightDerivs = float_matarr_create(network.layers - 1, maxShape, maxShape);
  float** biasDerivs = float_matrix_create(network.layers - 1, maxShape);

  frwrd_create_derivs(weightDerivs, biasDerivs, network, inputs, targets);

  create_weibia_deltas(weightDeltas, biasDeltas, network.layers, maxShape, learnRate, momentum, weightDerivs, biasDerivs, oldWeightDeltas, oldBiasDeltas);

  float_matarr_free(&weightDerivs, network.layers - 1, maxShape, maxShape);
  float_matrix_free(&biasDerivs, network.layers - 1, maxShape);
}

// Tip: Check pointer arguments before assigning
bool train_network_stcast(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float* inputs, float* targets, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  stcast_weibia_deltas(weightDeltas, biasDeltas, network, learnRate, momentum, inputs, targets, oldWeightDeltas, oldBiasDeltas);

  float_matarr_elem_addit(network.weights, network.weights, weightDeltas, network.layers - 1, maxShape, maxShape);
  float_matrix_elem_addit(network.biases, network.biases, biasDeltas, network.layers - 1, maxShape);

  return true;
}

// Tip: store mean weight/bias derivs in temp variables before asigning pointers
// Tip: Check pointer arguments before assigning
/*
static void mean_weibia_derivs(float*** meanWeightDerivs, float** meanBiasDerivs, Network network, float** inputs, float** targets, int batchSize)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float*** weightDerivs = float_matarr_create(network.layers - 1, maxShape, maxShape);
  float** biasDerivs = float_matrix_create(network.layers - 1, maxShape);

  for(int inputIndex = 0; inputIndex < batchSize; inputIndex += 1)
  {
    frwrd_create_derivs(weightDerivs, biasDerivs, network, inputs[inputIndex], targets[inputIndex]);

    float_matarr_elem_addit(meanWeightDerivs, meanWeightDerivs, weightDerivs, network.layers - 1, maxShape, maxShape);
    float_matrix_elem_addit(meanBiasDerivs, meanBiasDerivs, biasDerivs, network.layers - 1, maxShape);
  }

  float_matarr_free(&weightDerivs, network.layers - 1, maxShape, maxShape);
  float_matrix_free(&biasDerivs, network.layers - 1, maxShape);

  float_matarr_scale_multi(meanWeightDerivs, meanWeightDerivs, network.layers - 1, maxShape, maxShape, 1.0f / batchSize);
  float_matrix_scale_multi(meanBiasDerivs, meanBiasDerivs, network.layers - 1, maxShape, 1.0f / batchSize);
}
*/

/*
static void minbat_weibia_deltas(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float*** meanWeightDerivs = float_matarr_create(network.layers - 1, maxShape, maxShape);
  float** meanBiasDerivs = float_matrix_create(network.layers - 1, maxShape);

  mean_weibia_derivs(meanWeightDerivs, meanBiasDerivs, network, inputs, targets, batchSize);

  create_weibia_deltas(weightDeltas, biasDeltas, network.layers, maxShape, learnRate, momentum, meanWeightDerivs, meanBiasDerivs, oldWeightDeltas, oldBiasDeltas);

  float_matarr_free(&meanWeightDerivs, network.layers - 1, maxShape, maxShape);
  float_matrix_free(&meanBiasDerivs, network.layers - 1, maxShape);
}
*/

// Tip: Check pointer arguments before assigning
/*
static bool train_network_minbat(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  minbat_weibia_deltas(weightDeltas, biasDeltas, network, learnRate, momentum, inputs, targets, batchSize, oldWeightDeltas, oldBiasDeltas);

  float_matarr_elem_addit(network.weights, network.weights, weightDeltas, network.layers - 1, maxShape, maxShape);
  float_matrix_elem_addit(network.biases, network.biases, biasDeltas, network.layers - 1, maxShape);

  return true;
}
*/

// Tip: Check pointer arguments before assigning
bool frwrd_network_inputs(float* outputs, Network network, float* inputs)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float** nodeValues = float_matrix_create(network.layers, maxShape);

  create_node_values(nodeValues, network, inputs);

  float_vector_copy(outputs, nodeValues[network.layers - 1], network.sizes[network.layers - 1]);

  float_matrix_free(&nodeValues, network.layers, maxShape);

  return true;
}

static void train_epoch_stcast(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  int* randIndexes = index_array_create(batchSize);

  index_array_shuffle(randIndexes, batchSize);

  for(int index = 0; index < batchSize; index += 1)
  {
    int randIndex = randIndexes[index];

    train_network_stcast(weightDeltas, biasDeltas, network, learnRate, momentum, inputs[randIndex], targets[randIndex], oldWeightDeltas, oldBiasDeltas);

    float_matarr_copy(oldWeightDeltas, weightDeltas, network.layers - 1, maxShape, maxShape);
    float_matrix_copy(oldBiasDeltas, biasDeltas, network.layers - 1, maxShape);
  }

  index_array_free(&randIndexes, batchSize);
}

void train_epochs_stcast(Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, int epochAmount)
{
  int maxShape = maximum_layer_shape(network.sizes, network.layers);

  float*** weightDeltas = float_matarr_create(network.layers - 1, maxShape, maxShape);
  float** biasDeltas = float_matrix_create(network.layers - 1, maxShape);

  float*** oldWeightDeltas = float_matarr_create(network.layers - 1, maxShape, maxShape);
  float** oldBiasDeltas = float_matrix_create(network.layers - 1, maxShape);

  for(int epochIndex = 0; epochIndex < epochAmount; epochIndex += 1)
  {
    train_epoch_stcast(weightDeltas, biasDeltas, network, learnRate, momentum, inputs, targets, batchSize, oldWeightDeltas, oldBiasDeltas);
  }

  float_matarr_free(&oldWeightDeltas, network.layers - 1, maxShape, maxShape);
  float_matrix_free(&oldBiasDeltas, network.layers - 1, maxShape);

  float_matarr_free(&weightDeltas, network.layers - 1, maxShape, maxShape);
  float_matrix_free(&biasDeltas, network.layers - 1, maxShape);
}
