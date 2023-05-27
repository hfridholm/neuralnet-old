#ifndef NEURAL_ACTIVATE_FUNCS_H
#define NEURAL_ACTIVATE_FUNCS_H

float activat_funct_sigm(float floatValue);

float derivat_funct_sigm(float sigmValue);


float* layer_activat_sigm(float* result, float* nodes, int amount);

float* layer_derivat_sigm(float* result, float* nodes, int amount);


bool parse_activat_funct(float* (**layer_activat_funct)(float*, float*, int), int activatCode);

bool parse_derivat_funct(float* (**layer_derivat_funct)(float*, float*, int), int activatCode);


float* cross_entropy_deriv(float* result, float* nodes, float* targets, int amount);

#endif