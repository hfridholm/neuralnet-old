#include "../header/engine-include-header.h"

float activat_funct_sigm(float floatValue)
{
  return (1 / (1 + exp(-floatValue)) );
}

float derivat_funct_sigm(float sigmValue)
{
  return (sigmValue * (1 - sigmValue));
}

float activate_func_relu(float floatValue)
{
  return (floatValue > 0) ? floatValue : 0;
}

float dervtive_func_relu(float reluValue)
{
  return (reluValue > 0) ? 1 : 0;
}

float activate_func_tanh(float floatValue)
{
  return (exp(2 * floatValue) - 1) / (exp(2 * floatValue) + 1);
}

float dervtive_func_tanh(float tanhValue)
{
  return (1 - tanhValue * tanhValue);
}

float* layer_activat_sigm(float* result, float* nodes, int amount)
{
  for(int index = 0; index < amount; index += 1)
  {
    result[index] = activat_funct_sigm(nodes[index]);
  }
  return result;
}

float* layer_derivat_sigm(float* result, float* nodes, int amount)
{
  for(int index = 0; index < amount; index += 1)
  {
    result[index] = derivat_funct_sigm(nodes[index]);
  }
  return result;
}

bool parse_activat_funct(float* (**layer_activat_funct)(float*, float*, int), int activatCode)
{
  if(activatCode == 1)
  {
    *layer_activat_funct = layer_activat_sigm;
    return true;
  }
  return false;
}

bool parse_derivat_funct(float* (**layer_derivat_funct)(float*, float*, int), int activatCode)
{
  if(activatCode == 1)
  {
    *layer_derivat_funct = layer_derivat_sigm;
    return true;
  }
  return false;
}

float* cross_entropy_deriv(float* result, float* nodes, float* targets, int amount)
{
  for(int index = 0; index < amount; index += 1)
  {
    result[index] = 2 * (nodes[index] - targets[index]);
  }
  return result;
}