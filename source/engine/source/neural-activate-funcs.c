#include "../engine.h"

float sigmoid_activ_value(float floatValue)
{
  return (1 / (1 + exp(-floatValue)) );
}

float sigmoid_deriv_value(float sigmValue)
{
  return (sigmValue * (1 - sigmValue));
}

float relu_activ_value(float floatValue)
{
  return (floatValue > 0) ? floatValue : 0;
}

float relu_deriv_value(float reluValue)
{
  return (reluValue > 0) ? 1 : 0;
}

float tanh_activ_value(float floatValue)
{
  return (exp(2 * floatValue) - 1) / (exp(2 * floatValue) + 1);
}

float tanh_deriv_value(float tanhValue)
{
  return (1 - tanhValue * tanhValue);
}

float* cross_entropy_deriv(float* result, float* nodes, float* targets, int amount)
{
  for(int index = 0; index < amount; index += 1)
  {
    result[index] = 2 * (nodes[index] - targets[index]);
  }
  return result;
}

float* softmax_activ_values(float* result, float* nodes, int amount)
{
  float sum = 0.0f;

  for(int index = 0; index < amount; index += 1)
  {
    sum += exp(nodes[index]);
  }
  for(int index = 0; index < amount; index += 1)
  {
    result[index] = exp(nodes[index]) / sum;
  }
  return result;
}

float* sigmoid_activ_values(float* activValues, float* layerValues, int layerWidth)
{
  for(int index = 0; index < layerWidth; index += 1)
  {
    activValues[index] = sigmoid_activ_value(layerValues[index]);
  }
  return activValues;
}

float* relu_activ_values(float* activValues, float* layerValues, int layerWidth)
{
  for(int index = 0; index < layerWidth; index += 1)
  {
    activValues[index] = relu_activ_value(layerValues[index]);
  }
  return activValues;
}

float* tanh_activ_values(float* activValues, float* layerValues, int layerWidth)
{
  for(int index = 0; index < layerWidth; index += 1)
  {
    activValues[index] = tanh_activ_value(layerValues[index]);
  }
  return activValues;
}

float** softmax_deriv_values(float** result, float* procents, int amount)
{
  for(int iIndex = 0; iIndex < amount; iIndex += 1)
  {
    for(int jIndex = 0; jIndex < amount; jIndex += 1)
    {
      if(iIndex == jIndex) result[iIndex][jIndex] = procents[iIndex] * (1 - procents[iIndex]);

      else result[iIndex][jIndex] = -procents[iIndex] * procents[jIndex];
    }
  }
  return result;
}

float* apply_softmax_derivs(float* layerDerivs, float* layerValues, int layerWidth)
{
  float** activDerivs = create_float_matrix(layerWidth, layerWidth);

  softmax_deriv_values(activDerivs, layerValues, layerWidth);

  dotprod_fmatrix_vector(layerDerivs, activDerivs, layerWidth, layerWidth, layerValues, layerWidth);

  free_float_matrix(&activDerivs, layerWidth, layerWidth);

  return layerDerivs;
}

float* apply_sigmoid_derivs(float* layerDerivs, float* layerValues, int layerWidth)
{
  float* activDerivs = create_float_vector(layerWidth);

  for(int index = 0; index < layerWidth; index += 1)
  {
    activDerivs[index] = sigmoid_deriv_value(layerValues[index]);
  }

  multi_elem_fvector(layerDerivs, layerDerivs, activDerivs, layerWidth);

  free_float_vector(&activDerivs, layerWidth);

  return layerDerivs;
}

float* apply_relu_derivs(float* layerDerivs, float* layerValues, int layerWidth)
{
  float* activDerivs = create_float_vector(layerWidth);

  for(int index = 0; index < layerWidth; index += 1)
  {
    activDerivs[index] = relu_deriv_value(layerValues[index]);
  }

  multi_elem_fvector(layerDerivs, layerDerivs, activDerivs, layerWidth);

  free_float_vector(&activDerivs, layerWidth);

  return layerDerivs;
}

float* apply_tanh_derivs(float* layerDerivs, float* layerValues, int layerWidth)
{
  float* activDerivs = create_float_vector(layerWidth);

  for(int index = 0; index < layerWidth; index += 1)
  {
    activDerivs[index] = tanh_deriv_value(layerValues[index]);
  }

  multi_elem_fvector(layerDerivs, layerDerivs, activDerivs, layerWidth);

  free_float_vector(&activDerivs, layerWidth);

  return layerDerivs;
}

void layer_activ_values(float* activValues, float* layerValues, int layerWidth, int layerActive)
{
  switch(layerActive)
  {
    case 1: sigmoid_activ_values(activValues, layerValues, layerWidth); break;

    case 2: relu_activ_values(activValues, layerValues, layerWidth); break;

    case 3: tanh_activ_values(activValues, layerValues, layerWidth); break;

    case 4: softmax_activ_values(activValues, layerValues, layerWidth); break;
  }
}

void apply_activ_derivs(float* layerDerivs, float* layerValues, int layerWidth, int layerActive)
{
  switch(layerActive)
  {
    case 1: apply_sigmoid_derivs(layerDerivs, layerValues, layerWidth); break;

    case 2: apply_relu_derivs(layerDerivs, layerValues, layerWidth); break;

    case 3: apply_tanh_derivs(layerDerivs, layerValues, layerWidth); break;

    case 4: apply_softmax_derivs(layerDerivs, layerValues, layerWidth); break;
  }
}
