#include "../persue.h"
#include "p-activs-intern.h"

int network_sizes_maximum(const int networkSizes[], int networkLayers)
{
  int maxShape = 0;

  for(int layerIndex = 0; layerIndex < networkLayers; layerIndex += 1)
  {
    if(networkSizes[layerIndex] <= maxShape) continue;

    maxShape = networkSizes[layerIndex];
  }
  return maxShape;
}

static void weight_deltas_inherit(float*** weightDeltas, int networkLayers, int maxShape, float momentum, float*** oldWeightDeltas)
{
  float*** tempWeightDeltas = float_matarr_create(networkLayers - 1, maxShape, maxShape);

  float_matarr_scale_multi(tempWeightDeltas, oldWeightDeltas, networkLayers - 1, maxShape, maxShape, momentum);

  float_matarr_elem_addit(weightDeltas, weightDeltas, tempWeightDeltas, networkLayers - 1, maxShape, maxShape);

  float_matarr_free(&tempWeightDeltas, networkLayers - 1, maxShape, maxShape);
}

static void bias_deltas_inherit(float** biasDeltas, int networkLayers, int maxShape, float momentum, float** oldBiasDeltas)
{
  float** tempBiasDeltas = float_matrix_create(networkLayers - 1, maxShape);

  float_matrix_scale_multi(tempBiasDeltas, oldBiasDeltas, networkLayers - 1, maxShape, momentum);

  float_matrix_elem_addit(biasDeltas, biasDeltas, tempBiasDeltas, networkLayers - 1, maxShape);

  float_matrix_free(&tempBiasDeltas, networkLayers - 1, maxShape);
}

static bool node_derivs_create(float** nodeDerivs, Network network, float** nodeValues, float* targets)
{
  cross_entropy_derivs(nodeDerivs[network.layers - 2], nodeValues[network.layers - 1], targets, network.sizes[network.layers - 1]);

  activ_derivs_apply(nodeDerivs[network.layers - 2], nodeValues[network.layers - 1], network.sizes[network.layers - 1], network.activs[network.layers - 2]);

  for(int layerIndex = (network.layers - 1); layerIndex >= 2; layerIndex -= 1)
  {
    int layerHeight = network.sizes[layerIndex];
    int layerWidth = network.sizes[layerIndex - 1];

    float** weightTransp = float_matrix_create(layerWidth, layerHeight);

    float_matrix_transp(weightTransp, network.weights[layerIndex - 1], layerHeight, layerWidth);

    float_matrix_vector_dotprod(nodeDerivs[layerIndex - 2], weightTransp, layerWidth, layerHeight, nodeDerivs[layerIndex - 1], layerHeight);

    float_matrix_free(&weightTransp, layerWidth, layerHeight);

    activ_derivs_apply(nodeDerivs[layerIndex - 2], nodeValues[layerIndex - 1], layerWidth, network.activs[layerIndex - 2]);
  }
  return true;
}

static bool node_values_create(float** nodeValues, Network network, float* inputs)
{
  float_vector_copy(nodeValues[0], inputs, network.sizes[0]);

  for(int layerIndex = 1; layerIndex < network.layers; layerIndex += 1)
  {
    int layerHeight = network.sizes[layerIndex];
    int layerWidth = network.sizes[layerIndex - 1];

    float_matrix_vector_dotprod(nodeValues[layerIndex], network.weights[layerIndex - 1], layerHeight, layerWidth, nodeValues[layerIndex - 1], layerWidth);

    float_vector_elem_addit(nodeValues[layerIndex], nodeValues[layerIndex], network.biases[layerIndex - 1], layerHeight);

    activ_values(nodeValues[layerIndex], nodeValues[layerIndex], layerHeight, network.activs[layerIndex - 1]);
  }
  return true;
}

static bool node_values_derivs_create(float** nodeValues, float** nodeDerivs, Network network, float* inputs, float* targets)
{
  if(!node_values_create(nodeValues, network, inputs)) return false;

  if(!node_derivs_create(nodeDerivs, network, nodeValues, targets)) return false;

  return true;
}

static bool weight_bias_derivs_create(float*** weightDerivs, float** biasDerivs, Network network, float* inputs, float* targets)
{
  int maxShape = network_sizes_maximum(network.sizes, network.layers);

  float** nodeValues = float_matrix_create(network.layers, maxShape);
  float** nodeDerivs = float_matrix_create(network.layers - 1, maxShape);

  node_values_derivs_create(nodeValues, nodeDerivs, network, inputs, targets);

  for(int layerIndex = (network.layers - 1); layerIndex >= 1; layerIndex -= 1)
  {
    int layerHeight = network.sizes[layerIndex];
    int layerWidth = network.sizes[layerIndex - 1];

    float_vector_dotprod(weightDerivs[layerIndex - 1], nodeDerivs[layerIndex - 1], layerHeight, nodeValues[layerIndex - 1], layerWidth);

    float_vector_copy(biasDerivs[layerIndex - 1], nodeDerivs[layerIndex - 1], layerHeight);
  }

  float_matrix_free(&nodeDerivs, network.layers - 1, maxShape);

  float_matrix_free(&nodeValues, network.layers, maxShape);

  return true;
}

static void weight_bias_deltas_create(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float* inputs, float* targets, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = network_sizes_maximum(network.sizes, network.layers);

  float*** weightDerivs = float_matarr_create(network.layers - 1, maxShape, maxShape);
  float** biasDerivs = float_matrix_create(network.layers - 1, maxShape);

  weight_bias_derivs_create(weightDerivs, biasDerivs, network, inputs, targets);
  

  float_matarr_scale_multi(weightDeltas, weightDerivs, network.layers - 1, maxShape, maxShape, -learnRate);

  if(oldWeightDeltas != NULL)
  {
    weight_deltas_inherit(weightDeltas, network.layers, maxShape, momentum, oldWeightDeltas);
  }

  float_matrix_scale_multi(biasDeltas, biasDerivs, network.layers - 1, maxShape, -learnRate);

  if(oldBiasDeltas != NULL)
  {
    bias_deltas_inherit(biasDeltas, network.layers, maxShape, momentum, oldBiasDeltas);
  }


  float_matarr_free(&weightDerivs, network.layers - 1, maxShape, maxShape);
  float_matrix_free(&biasDerivs, network.layers - 1, maxShape);
}

// Tip: Check pointer arguments before assigning
bool network_train_stcast(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float* inputs, float* targets, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = network_sizes_maximum(network.sizes, network.layers);

  weight_bias_deltas_create(weightDeltas, biasDeltas, network, learnRate, momentum, inputs, targets, oldWeightDeltas, oldBiasDeltas);

  float_matarr_elem_addit(network.weights, network.weights, weightDeltas, network.layers - 1, maxShape, maxShape);
  float_matrix_elem_addit(network.biases, network.biases, biasDeltas, network.layers - 1, maxShape);

  return true;
}

// Tip: store mean weight/bias derivs in temp variables before asigning pointers
// Tip: Check pointer arguments before assigning
/*
static void weight_bias_derivs_mean(float*** meanWeightDerivs, float** meanBiasDerivs, Network network, float** inputs, float** targets, int batchSize)
{
  int maxShape = network_sizes_maximum(network.sizes, network.layers);

  float*** weightDerivs = float_matarr_create(network.layers - 1, maxShape, maxShape);
  float** biasDerivs = float_matrix_create(network.layers - 1, maxShape);

  for(int inputIndex = 0; inputIndex < batchSize; inputIndex += 1)
  {
    weight_bias_derivs_create(weightDerivs, biasDerivs, network, inputs[inputIndex], targets[inputIndex]);

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
static void minbat_weight_bias_deltas(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = network_sizes_maximum(network.sizes, network.layers);

  float*** meanWeightDerivs = float_matarr_create(network.layers - 1, maxShape, maxShape);
  float** meanBiasDerivs = float_matrix_create(network.layers - 1, maxShape);

  weight_bias_derivs_mean(meanWeightDerivs, meanBiasDerivs, network, inputs, targets, batchSize);

  weight_bias_deltas_create(weightDeltas, biasDeltas, network.layers, maxShape, learnRate, momentum, meanWeightDerivs, meanBiasDerivs, oldWeightDeltas, oldBiasDeltas);

  float_matarr_free(&meanWeightDerivs, network.layers - 1, maxShape, maxShape);
  float_matrix_free(&meanBiasDerivs, network.layers - 1, maxShape);
}
*/

// Tip: Check pointer arguments before assigning
/*
static bool network_train_minbat(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = network_sizes_maximum(network.sizes, network.layers);

  minbat_weight_bias_deltas(weightDeltas, biasDeltas, network, learnRate, momentum, inputs, targets, batchSize, oldWeightDeltas, oldBiasDeltas);

  float_matarr_elem_addit(network.weights, network.weights, weightDeltas, network.layers - 1, maxShape, maxShape);
  float_matrix_elem_addit(network.biases, network.biases, biasDeltas, network.layers - 1, maxShape);

  return true;
}
*/

static void network_train_minbat_epoch(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas)
{

}

void network_train_minbat_epochs(Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, int epochAmount)
{
  int maxShape = network_sizes_maximum(network.sizes, network.layers);

  float*** weightDeltas = float_matarr_create(network.layers - 1, maxShape, maxShape);
  float** biasDeltas = float_matrix_create(network.layers - 1, maxShape);

  float*** oldWeightDeltas = float_matarr_create(network.layers - 1, maxShape, maxShape);
  float** oldBiasDeltas = float_matrix_create(network.layers - 1, maxShape);

  for(int epochIndex = 0; epochIndex < epochAmount; epochIndex += 1)
  {
    network_train_minbat_epoch(weightDeltas, biasDeltas, network, learnRate, momentum, inputs, targets, batchSize, oldWeightDeltas, oldBiasDeltas);
  }

  float_matarr_free(&oldWeightDeltas, network.layers - 1, maxShape, maxShape);
  float_matrix_free(&oldBiasDeltas, network.layers - 1, maxShape);

  float_matarr_free(&weightDeltas, network.layers - 1, maxShape, maxShape);
  float_matrix_free(&biasDeltas, network.layers - 1, maxShape);
}

// Tip: Check pointer arguments before assigning
bool network_forward(float* outputs, Network network, float* inputs)
{
  int maxShape = network_sizes_maximum(network.sizes, network.layers);

  float** nodeValues = float_matrix_create(network.layers, maxShape);

  node_values_create(nodeValues, network, inputs);

  float_vector_copy(outputs, nodeValues[network.layers - 1], network.sizes[network.layers - 1]);

  float_matrix_free(&nodeValues, network.layers, maxShape);

  return true;
}

static unsigned long long mills_get_current()
{
  struct timeval time;

  gettimeofday(&time, NULL);

  return time.tv_sec * 1000 + time.tv_usec / 1000;
}

static void network_train_stcast_epoch(float*** weightDeltas, float** biasDeltas, Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = network_sizes_maximum(network.sizes, network.layers);

  int* randIndexes = index_array_create(batchSize);

  index_array_shuffle(randIndexes, batchSize);

  for(int index = 0; index < batchSize; index += 1)
  {
    int randIndex = randIndexes[index];

    network_train_stcast(weightDeltas, biasDeltas, network, learnRate, momentum, inputs[randIndex], targets[randIndex], oldWeightDeltas, oldBiasDeltas);

    float_matarr_copy(oldWeightDeltas, weightDeltas, network.layers - 1, maxShape, maxShape);
    float_matrix_copy(oldBiasDeltas, biasDeltas, network.layers - 1, maxShape);
  }

  index_array_free(&randIndexes, batchSize);
}

void _network_train_stcast_epochs(Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, int epochAmount, unsigned long totalMills, unsigned long long startMills, float*** weightDeltas, float** biasDeltas, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  if(epochAmount <= 0 && totalMills <= 0)
  {
    printf("epochAmount == 0 && totalMills == 0\n");
    return;
  }

  int epochIndex = 0;

  while(true)
  {
    if(epochAmount > 0)
    {
      if(epochIndex++ >= epochAmount) break;
    }
    if(totalMills > 0)
    {
      if(mills_get_current() - startMills > totalMills) break;
    }
    network_train_stcast_epoch(weightDeltas, biasDeltas, network, learnRate, momentum, inputs, targets, batchSize, oldWeightDeltas, oldBiasDeltas);
  }
}

void network_train_stcast_epochs(Network network, float learnRate, float momentum, float** inputs, float** targets, int batchSize, int epochAmount, unsigned long totalMills)
{
  unsigned long long startMills = mills_get_current();

  int maxShape = network_sizes_maximum(network.sizes, network.layers);

  float*** weightDeltas = float_matarr_create(network.layers - 1, maxShape, maxShape);
  float** biasDeltas = float_matrix_create(network.layers - 1, maxShape);

  float*** oldWeightDeltas = float_matarr_create(network.layers - 1, maxShape, maxShape);
  float** oldBiasDeltas = float_matrix_create(network.layers - 1, maxShape);

  _network_train_stcast_epochs(network, learnRate, momentum, inputs, targets, batchSize, epochAmount, totalMills, startMills, weightDeltas, biasDeltas, oldWeightDeltas, oldBiasDeltas);

  float_matarr_free(&oldWeightDeltas, network.layers - 1, maxShape, maxShape);
  float_matrix_free(&oldBiasDeltas, network.layers - 1, maxShape);

  float_matarr_free(&weightDeltas, network.layers - 1, maxShape, maxShape);
  float_matrix_free(&biasDeltas, network.layers - 1, maxShape);
}
