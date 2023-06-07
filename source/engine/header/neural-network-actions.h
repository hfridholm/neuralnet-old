#ifndef NEURAL_NETWORK_ACTIONS_H
#define NEURAL_NETWORK_ACTIONS_H

extern bool train_network_stcast(float*** weightDeltas, float** biasDeltas, int layerAmount, const int layerSizes[], const int layerActivs[], float*** weights, float** biases, float learnRate, float momentum, float* inputs, float* targets, float*** oldWeightDeltas, float** oldBiasDeltas);

extern void stcast_weibia_deltas(float*** weightDeltas, float** biasDeltas, int layerAmount, const int layerSizes[], const int layerActivs[], float*** weights, float** biases, float learnRate, float momentum, float* inputs, float* targets, float*** oldWeightDeltas, float** oldBiasDeltas);

extern void frwrd_create_derivs(float*** weightDerivs, float** biasDerivs, int layerAmount, const int layerSizes[], const int layerActivs[], float*** weights, float** biases, float* inputs, float* targets);

extern void mean_weibia_derivs(float*** meanWeightDerivs, float** meanBiasDerivs, int layerAmount, const int layerSizes[], const int layerActivs[], float*** weights, float** biases, float** inputs, float** targets, int batchSize);

extern void minbat_weibia_deltas(float*** weightDeltas, float** biasDeltas, int layerAmount, const int layerSizes[], const int layerActivs[], float*** weights, float** biases, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas);

extern bool train_network_minbat(float*** weightDeltas, float** biasDeltas, int layerAmount, const int layerSizes[], const int layerActivs[], float*** weights, float** biases, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas);

extern bool frwrd_network_inputs(float* outputs, int layerAmount, const int layerSizes[], const int layerActivs[], float*** weights, float** biases, float* inputs);

extern void train_epochs_stcast(int layerAmount, const int layerSizes[], const int layerActivs[], float*** weights, float** biases, float learnRate, float momentum, float** inputs, float** targets, int batchSize, int epochAmount);

extern void train_epoch_stcast(float*** weightDeltas, float** biasDeltas, int layerAmount, const int layerSizes[], const int layerActivs[], float*** weights, float** biases, float learnRate, float momentum, float** inputs, float** targets, int batchSize, float*** oldWeightDeltas, float** oldBiasDeltas);

#endif
