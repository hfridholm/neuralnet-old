#ifndef NEURAL_ACTIVATE_FUNCS_H
#define NEURAL_ACTIVATE_FUNCS_H

float activat_funct_sigm(float floatValue);

float derivat_funct_sigm(float sigmValue);

float activat_funct_relu(float floatValue);

float derivat_funct_relu(float sigmValue);

float activat_funct_tanh(float floatValue);

float derivat_funct_tanh(float sigmValue);


float* layer_activat_funct(float* result, float* nodes, int amount, float (*activat_funct)(float));

float* layer_derivat_funct(float* result, float* nodes, int amount, float (*derivat_funct)(float));


bool parse_activat_funct(float (**activat_funct)(float), int activatCode);

bool parse_derivat_funct(float (**derivat_funct)(float), int activatCode);


float* cross_entropy_deriv(float* result, float* nodes, float* targets, int amount);

#endif