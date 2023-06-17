#include "../engine.h"

int maximum_layer_shape(const int networkSizes[], int networkLayers)
{
  int maxShape = 0;

  for(int lIndex = 0; lIndex < networkLayers; lIndex += 1)
  {
    if(networkSizes[lIndex] > maxShape) maxShape = networkSizes[lIndex];
  }
  return maxShape;
}

void addit_oldwei_deltas(float*** weightDeltas, int networkLayers, const int networkSizes[], float momentum, float*** oldWeightDeltas)
{
  int maxShape = maximum_layer_shape(networkSizes, networkLayers);

  float*** tempWeightDeltas = create_fmatrix_array(networkLayers - 1, maxShape, maxShape);

  multi_scale_fmatarr(tempWeightDeltas, oldWeightDeltas, networkLayers - 1, maxShape, maxShape, momentum);

  addit_elem_fmatarr(weightDeltas, weightDeltas, tempWeightDeltas, networkLayers - 1, maxShape, maxShape);

  free_fmatrix_array(&tempWeightDeltas, networkLayers - 1, maxShape, maxShape);
}

void addit_oldbia_deltas(float** biasDeltas, int networkLayers, const int networkSizes[], float momentum, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(networkSizes, networkLayers);

  float** tempBiasDeltas = create_float_matrix(networkLayers - 1, maxShape);

  multi_scale_fmatrix(tempBiasDeltas, oldBiasDeltas, networkLayers - 1, maxShape, momentum);

  addit_elem_fmatrix(biasDeltas, biasDeltas, tempBiasDeltas, networkLayers - 1, maxShape);

  free_float_matrix(&tempBiasDeltas, networkLayers - 1, maxShape);
}

bool create_weibia_deltas(float*** weightDeltas, float** biasDeltas, int networkLayers, const int networkSizes[], float learnRate, float momentum, float*** weightDerivs, float** biasDerivs, float*** oldWeightDeltas, float** oldBiasDeltas)
{
  int maxShape = maximum_layer_shape(networkSizes, networkLayers);

  multi_scale_fmatarr(weightDeltas, weightDerivs, networkLayers - 1, maxShape, maxShape, -learnRate);

  if(oldWeightDeltas != NULL)
  {
    addit_oldwei_deltas(weightDeltas, networkLayers, networkSizes, momentum, oldWeightDeltas);
  }

  multi_scale_fmatrix(biasDeltas, biasDerivs, networkLayers - 1, maxShape, -learnRate);

  if(oldBiasDeltas != NULL)
  {
    addit_oldbia_deltas(biasDeltas, networkLayers, networkSizes, momentum, oldBiasDeltas);
  }

  return true;
}

bool create_node_derivs(float** nodeDerivs, Network network, float** nodeValues, float* targets)
{
  cross_entropy_deriv(nodeDerivs[network.layers - 2], nodeValues[network.layers - 1], targets, network.sizes[network.layers - 1]);

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
