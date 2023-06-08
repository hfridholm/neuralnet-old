#ifndef NEURAL_NETWORK_HANDLER_H
#define NEURAL_NETWORK_HANDLER_H

extern int maximum_layer_shape(const int layerSizes[], int layerAmount);

extern void addit_oldwei_deltas(float*** weightDeltas, int layerAmount, const int layerSizes[], float momentum, float*** oldWeightDeltas);

extern void addit_oldbia_deltas(float** biasDeltas, int layerAmount, const int layerSizes[], float momentum, float** oldBiasDeltas);

extern bool create_weibia_deltas(float*** weightDeltas, float** biasDeltas, int layerAmount, const int layerSizes[], float learnRate, float momentum, float*** weightDerivs, float** biasDerivs, float*** oldWeightDeltas, float** oldBiasDeltas);

extern bool create_node_derivs(float** nodeDerivs, int layerAmount, const int layerSizes[], const Activ layerActivs[], float*** weights, float** biases, float** nodeValues, float* targets);

extern bool create_weibia_derivs(float*** weightDerivs, float** biasDerivs, int layerAmount, const int layerSizes[], const Activ layerActivs[], float*** weights, float** biases, float** nodeValues, float* targets);

extern bool create_node_values(float** nodeValues, int layerAmount, const int layerSizes[], const Activ layerActivs[], float*** weights, float** biases, float* inputs);

#endif
