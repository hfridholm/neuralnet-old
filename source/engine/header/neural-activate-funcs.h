#ifndef NEURAL_ACTIVATE_FUNCS_H
#define NEURAL_ACTIVATE_FUNCS_H

float sigmoid_activ_value(float floatValue);

float sigmoid_deriv_value(float sigmValue);

float relu_activ_value(float floatValue);

float relu_deriv_value(float reluValue);

float tanh_activ_value(float floatValue);

float tanh_deriv_value(float tanhValue);

float* cross_entropy_deriv(float* result, float* nodes, float* targets, int amount);

float* softmax_activ_values(float* result, float* nodes, int amount);

float* sigmoid_activ_values(float* activValues, float* layerValues, int layerWidth);

float* relu_activ_values(float* activValues, float* layerValues, int layerWidth);

float* tanh_activ_values(float* activValues, float* layerValues, int layerWidth);

float** softmax_deriv_values(float** result, float* procents, int amount);

float* apply_softmax_derivs(float* layerDerivs, float* layerValues, int layerWidth);

float* apply_sigmoid_derivs(float* layerDerivs, float* layerValues, int layerWidth);

float* apply_relu_derivs(float* layerDerivs, float* layerValues, int layerWidth);

float* apply_tanh_derivs(float* layerDerivs, float* layerValues, int layerWidth);

void apply_activ_derivs(float* layerDerivs, float* layerValues, int layerWidth, int layerActive);

void layer_activ_values(float* activValues, float* layerValues, int layerWidth, int layerActive);

#endif
