#include "../header/engine-include-header.h"

float activat_funct_sigm(float floatValue)
{
  return (1 / (1 + exp(-floatValue)) );
}

float derivat_funct_sigm(float sigmValue)
{
  return (sigmValue * (1 - sigmValue));
}

float activat_funct_relu(float floatValue)
{
  return (floatValue > 0) ? floatValue : 0;
}

float derivat_funct_relu(float reluValue)
{
  return (reluValue > 0) ? 1 : 0;
}

float activat_funct_tanh(float floatValue)
{
  return (exp(2 * floatValue) - 1) / (exp(2 * floatValue) + 1);
}

float derivat_funct_tanh(float tanhValue)
{
  return (1 - tanhValue * tanhValue);
}

float* layer_activat_funct(float* result, float* nodes, int amount, float (*ativat_funct)(float))
{
  for(int index = 0; index < amount; index += 1)
  {
    result[index] = ativat_funct(nodes[index]);
  }
  return result;
}

float* layer_derivat_funct(float* result, float* nodes, int amount, float (*derivat_funct)(float))
{
  for(int index = 0; index < amount; index += 1)
  {
    result[index] = derivat_funct(nodes[index]);
  }
  return result;
}

bool parse_activat_funct(float (**activat_funct)(float), int activatCode)
{
  if(activatCode == 1)
  {
    *activat_funct = activat_funct_sigm;
    return true;
  }
  if(activatCode == 2)
  {
    *activat_funct = activat_funct_relu;
    return true;
  }
  if(activatCode == 3)
  {
    *activat_funct = activat_funct_tanh;
    return true;
  }
  return false;
}

bool parse_derivat_funct(float (**derivat_funct)(float), int activatCode)
{
  if(activatCode == 1)
  {
    *derivat_funct = derivat_funct_sigm;
    return true;
  }
  if(activatCode == 2)
  {
    *derivat_funct = derivat_funct_relu;
    return true;
  }
  if(activatCode == 3)
  {
    *derivat_funct = derivat_funct_tanh;
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