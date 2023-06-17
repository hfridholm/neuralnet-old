#ifndef NEURAL_NETWORK_HANDLER_H
#define NEURAL_NETWORK_HANDLER_H

extern int maximum_layer_shape(const int networkSizes[], int networkLayers);

extern void addit_oldwei_deltas(float*** weightDeltas, int networkLayers, const int networkSizes[], float momentum, float*** oldWeightDeltas);

extern void addit_oldbia_deltas(float** biasDeltas, int networkLayers, const int networkSizes[], float momentum, float** oldBiasDeltas);

extern bool create_weibia_deltas(float*** weightDeltas, float** biasDeltas, int networkLayers, const int networkSizes[], float learnRate, float momentum, float*** weightDerivs, float** biasDerivs, float*** oldWeightDeltas, float** oldBiasDeltas);

extern bool create_node_derivs(float** nodeDerivs, Network network, float** nodeValues, float* targets);

extern bool create_weibia_derivs(float*** weightDerivs, float** biasDerivs, Network network, float** nodeValues, float* targets);

extern bool create_node_values(float** nodeValues, Network network, float* inputs);

#endif
