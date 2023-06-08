#ifndef NEURAL_ACTIVATE_FUNCS_H
#define NEURAL_ACTIVATE_FUNCS_H

extern float sigmoid_activ_value(float floatValue);

extern float sigmoid_deriv_value(float sigmValue);

extern float relu_activ_value(float floatValue);

extern float relu_deriv_value(float reluValue);

extern float tanh_activ_value(float floatValue);

extern float tanh_deriv_value(float tanhValue);

extern float* cross_entropy_deriv(float* result, float* nodes, float* targets, int amount);

extern float* softmax_activ_values(float* activValues, float* layerValues, int layerWidth);

extern float* sigmoid_activ_values(float* activValues, float* layerValues, int layerWidth);

extern float* relu_activ_values(float* activValues, float* layerValues, int layerWidth);

extern float* tanh_activ_values(float* activValues, float* layerValues, int layerWidth);

extern float** softmax_deriv_values(float** layerDerivs, float* layerValues, int layerWidth);

extern float* apply_softmax_derivs(float* layerDerivs, float* layerValues, int layerWidth);

extern float* apply_sigmoid_derivs(float* layerDerivs, float* layerValues, int layerWidth);

extern float* apply_relu_derivs(float* layerDerivs, float* layerValues, int layerWidth);

extern float* apply_tanh_derivs(float* layerDerivs, float* layerValues, int layerWidth);

extern void apply_activ_derivs(float* layerDerivs, float* layerValues, int layerWidth, int layerActive);

extern void layer_activ_values(float* activValues, float* layerValues, int layerWidth, int layerActive);

#endif
