 #include "../persue.h"

static float sigmoid_value(float floatValue)
{
  return (1 / (1 + exp(-floatValue)) );
}

static float sigmoid_deriv(float sigmValue)
{
  return (sigmValue * (1 - sigmValue));
}

static float relu_value(float floatValue)
{
  return (floatValue > 0) ? floatValue : 0;
}

static float relu_deriv(float reluValue)
{
  return (reluValue > 0) ? 1 : 0;
}

static float tanh_value(float floatValue)
{
  return (exp(2 * floatValue) - 1) / (exp(2 * floatValue) + 1);
}

static float tanh_deriv(float tanhValue)
{
  return (1 - tanhValue * tanhValue);
}

static float* softmax_values(float* activValues, float* layerValues, int layerWidth)
{
  if(activValues == NULL || layerValues == NULL) return NULL;

  float sum = 0.0f;

  for(int index = 0; index < layerWidth; index += 1)
  {
    sum += exp(layerValues[index]);
  }
  for(int index = 0; index < layerWidth; index += 1)
  {
    activValues[index] = exp(layerValues[index]) / sum;
  }
  return activValues;
}

static float* sigmoid_values(float* activValues, float* layerValues, int layerWidth)
{
  if(activValues == NULL || layerValues == NULL) return NULL;

  for(int index = 0; index < layerWidth; index += 1)
  {
    activValues[index] = sigmoid_value(layerValues[index]);
  }
  return activValues;
}

static float* relu_values(float* activValues, float* layerValues, int layerWidth)
{
  if(activValues == NULL || layerValues == NULL) return NULL;

  for(int index = 0; index < layerWidth; index += 1)
  {
    activValues[index] = relu_value(layerValues[index]);
  }
  return activValues;
}

static float* tanh_values(float* activValues, float* layerValues, int layerWidth)
{
  if(activValues == NULL || layerValues == NULL) return NULL;

  for(int index = 0; index < layerWidth; index += 1)
  {
    activValues[index] = tanh_value(layerValues[index]);
  }
  return activValues;
}

static float** softmax_derivs(float** layerDerivs, float* layerValues, int layerWidth)
{
  if(layerDerivs == NULL || layerValues == NULL) return NULL;

  for(int iIndex = 0; iIndex < layerWidth; iIndex += 1)
  {
    for(int jIndex = 0; jIndex < layerWidth; jIndex += 1)
    {
      if(iIndex == jIndex) layerDerivs[iIndex][jIndex] = layerValues[iIndex] * (1 - layerValues[iIndex]);

      else layerDerivs[iIndex][jIndex] = -layerValues[iIndex] * layerValues[jIndex];
    }
  }
  return layerDerivs;
}

static float* softmax_derivs_apply(float* layerDerivs, float* layerValues, int layerWidth)
{
  if(layerDerivs == NULL || layerValues == NULL) return NULL;
 
  float** activDerivs = float_matrix_create(layerWidth, layerWidth);

  softmax_derivs(activDerivs, layerValues, layerWidth);

  float_matrix_vector_dotprod(layerDerivs, activDerivs, layerWidth, layerWidth, layerValues, layerWidth);

  float_matrix_free(&activDerivs, layerWidth, layerWidth);

  return layerDerivs;
}

static float* sigmoid_derivs_apply(float* layerDerivs, float* layerValues, int layerWidth)
{
  if(layerDerivs == NULL || layerValues == NULL) return NULL;

  float* activDerivs = float_vector_create(layerWidth);

  for(int index = 0; index < layerWidth; index += 1)
  {
    activDerivs[index] = sigmoid_deriv(layerValues[index]);
  }

  float_vector_elem_multi(layerDerivs, layerDerivs, activDerivs, layerWidth);
  // Check if layerderivs is zero!

  float_vector_free(&activDerivs, layerWidth);

  return layerDerivs;
}

static float* relu_derivs_apply(float* layerDerivs, float* layerValues, int layerWidth)
{
  if(layerDerivs == NULL || layerValues == NULL) return NULL;

  float* activDerivs = float_vector_create(layerWidth);

  for(int index = 0; index < layerWidth; index += 1)
  {
    activDerivs[index] = relu_deriv(layerValues[index]);
  }

  float_vector_elem_multi(layerDerivs, layerDerivs, activDerivs, layerWidth);

  float_vector_free(&activDerivs, layerWidth);

  return layerDerivs;
}

static float* tanh_derivs_apply(float* layerDerivs, float* layerValues, int layerWidth)
{
  if(layerDerivs == NULL || layerValues == NULL) return NULL;

  float* activDerivs = float_vector_create(layerWidth);

  for(int index = 0; index < layerWidth; index += 1)
  {
    activDerivs[index] = tanh_deriv(layerValues[index]);
  }

  float_vector_elem_multi(layerDerivs, layerDerivs, activDerivs, layerWidth);

  float_vector_free(&activDerivs, layerWidth);

  return layerDerivs;
}

void activ_values(float* activValues, float* layerValues, int layerWidth, Activ layerActiv)
{
  switch(layerActiv)
  {
    case ACTIV_NONE: return;

    case ACTIV_SIGMOID: sigmoid_values(activValues, layerValues, layerWidth); break;

    case ACTIV_RELU: relu_values(activValues, layerValues, layerWidth); break;

    case ACTIV_TANH: tanh_values(activValues, layerValues, layerWidth); break;

    case ACTIV_SOFTMAX: softmax_values(activValues, layerValues, layerWidth); break;

    default: return;
  }
}

void activ_derivs_apply(float* layerDerivs, float* layerValues, int layerWidth, Activ layerActiv)
{
  switch(layerActiv)
  {
    case ACTIV_NONE: return;

    case ACTIV_SIGMOID: sigmoid_derivs_apply(layerDerivs, layerValues, layerWidth); break;

    case ACTIV_RELU: relu_derivs_apply(layerDerivs, layerValues, layerWidth); break;

    case ACTIV_TANH: tanh_derivs_apply(layerDerivs, layerValues, layerWidth); break;

    case ACTIV_SOFTMAX: softmax_derivs_apply(layerDerivs, layerValues, layerWidth); break;

    default: return;
  }
}

float* cross_entropy_derivs(float* derivs, float* nodes, float* targets, int amount)
{
  if(derivs == NULL || nodes == NULL || targets == NULL) return NULL;
 
  for(int index = 0; index < amount; index += 1)
  {
    derivs[index] = 2 * (nodes[index] - targets[index]);
  }
  return derivs;
}

float cross_entropy_cost(float* nodes, float* targets, int amount)
{
  if(nodes == NULL || targets == NULL) return -1.0f;

  float costValue = 0.0f;

  for(int index = 0; index < amount; index += 1)
  {
    costValue += pow(nodes[index] - targets[index], 2);
  }
  return costValue / (float) amount;
}
