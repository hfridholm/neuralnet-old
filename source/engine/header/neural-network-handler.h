#ifndef NEURAL_NETWORK_HANDLER_H
#define NEURAL_NETWORK_HANDLER_H

int maximum_layer_shape(const int layerSizes[], int layerAmount);

bool create_weibia_deltas(float*** weightDeltas, float** biasDeltas, int layerAmount, const int layerSizes[], float learnRate, float momentum, float*** weightDerivs, float** biasDerivs, float*** oldWeightDeltas, float** oldBiasDeltas);

void multi_layer_derivs(float* layerDerivs, float* layerValues, int layerWidth, int layerActive);

bool create_node_derivs(float** nodeDerivs, int layerAmount, const int layerSizes[], const int layerActivs[], float*** weights, float** biases, float** nodeValues, float* targets);

bool create_weibia_derivs(float*** weightDerivs, float** biasDerivs, int layerAmount, const int layerSizes[], const int layerActivs[], float*** weights, float** biases, float** nodeValues, float* targets);

bool create_node_values(float** nodeValues, int layerAmount, const int layerSizes[], const int layerActivs[], float*** weights, float** biases, float* inputs);

#endif