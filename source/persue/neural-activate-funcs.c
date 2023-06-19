 #include "../persue.h"

static float sigmoid_activ_value(float floatValue)
{
  return (1 / (1 + exp(-floatValue)) );
}

static float sigmoid_deriv_value(float sigmValue)
{
  return (sigmValue * (1 - sigmValue));
}

static float relu_activ_value(float floatValue)
{
  return (floatValue > 0) ? floatValue : 0;
}

static float relu_deriv_value(float reluValue)
{
  return (reluValue > 0) ? 1 : 0;
}

static float tanh_activ_value(float floatValue)
{
  return (exp(2 * floatValue) - 1) / (exp(2 * floatValue) + 1);
}

static float tanh_deriv_value(float tanhValue)
{
  return (1 - tanhValue * tanhValue);
}

static float* softmax_activ_values(float* activValues, float* layerValues, int layerWidth)
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

static float* sigmoid_activ_values(float* activValues, float* layerValues, int layerWidth)
{
  if(activValues == NULL || layerValues == NULL) return NULL;

  for(int index = 0; index < layerWidth; index += 1)
  {
    activValues[index] = sigmoid_activ_value(layerValues[index]);
  }
  return activValues;
}

static float* relu_activ_values(float* activValues, float* layerValues, int layerWidth)
{
  if(activValues == NULL || layerValues == NULL) return NULL;

  for(int index = 0; index < layerWidth; index += 1)
  {
    activValues[index] = relu_activ_value(layerValues[index]);
  }
  return activValues;
}

static float* tanh_activ_values(float* activValues, float* layerValues, int layerWidth)
{
  if(activValues == NULL || layerValues == NULL) return NULL;

  for(int index = 0; index < layerWidth; index += 1)
  {
    activValues[index] = tanh_activ_value(layerValues[index]);
  }
  return activValues;
}

static float** softmax_deriv_values(float** layerDerivs, float* layerValues, int layerWidth)
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

static float* apply_softmax_derivs(float* layerDerivs, float* layerValues, int layerWidth)
{
  if(layerDerivs == NULL || layerValues == NULL) return NULL;
 
  float** activDerivs = create_float_matrix(layerWidth, layerWidth);

  softmax_deriv_values(activDerivs, layerValues, layerWidth);

  dotprod_fmatrix_vector(layerDerivs, activDerivs, layerWidth, layerWidth, layerValues, layerWidth);

  free_float_matrix(&activDerivs, layerWidth, layerWidth);

  return layerDerivs;
}

static float* apply_sigmoid_derivs(float* layerDerivs, float* layerValues, int layerWidth)
{
  if(layerDerivs == NULL || layerValues == NULL) return NULL;

  float* activDerivs = create_float_vector(layerWidth);

  for(int index = 0; index < layerWidth; index += 1)
  {
    activDerivs[index] = sigmoid_deriv_value(layerValues[index]);
  }

  multi_elem_fvector(layerDerivs, layerDerivs, activDerivs, layerWidth);

  free_float_vector(&activDerivs, layerWidth);

  return layerDerivs;
}

static float* apply_relu_derivs(float* layerDerivs, float* layerValues, int layerWidth)
{
  if(layerDerivs == NULL || layerValues == NULL) return NULL;

  float* activDerivs = create_float_vector(layerWidth);

  for(int index = 0; index < layerWidth; index += 1)
  {
    activDerivs[index] = relu_deriv_value(layerValues[index]);
  }

  multi_elem_fvector(layerDerivs, layerDerivs, activDerivs, layerWidth);

  free_float_vector(&activDerivs, layerWidth);

  return layerDerivs;
}

static float* apply_tanh_derivs(float* layerDerivs, float* layerValues, int layerWidth)
{
  if(layerDerivs == NULL || layerValues == NULL) return NULL;

  float* activDerivs = create_float_vector(layerWidth);

  for(int index = 0; index < layerWidth; index += 1)
  {
    activDerivs[index] = tanh_deriv_value(layerValues[index]);
  }

  multi_elem_fvector(layerDerivs, layerDerivs, activDerivs, layerWidth);

  free_float_vector(&activDerivs, layerWidth);

  return layerDerivs;
}

void layer_activ_values(float* activValues, float* layerValues, int layerWidth, Activ layerActiv)
{
  switch(layerActiv)
  {
    case ACTIV_NONE: return;

    case ACTIV_SIGMOID: sigmoid_activ_values(activValues, layerValues, layerWidth); break;

    case ACTIV_RELU: relu_activ_values(activValues, layerValues, layerWidth); break;

    case ACTIV_TANH: tanh_activ_values(activValues, layerValues, layerWidth); break;

    case ACTIV_SOFTMAX: softmax_activ_values(activValues, layerValues, layerWidth); break;
  }
}

void apply_activ_derivs(float* layerDerivs, float* layerValues, int layerWidth, Activ layerActiv)
{
  switch(layerActiv)
  {
    case ACTIV_NONE: return;

    case ACTIV_SIGMOID: apply_sigmoid_derivs(layerDerivs, layerValues, layerWidth); break;

    case ACTIV_RELU: apply_relu_derivs(layerDerivs, layerValues, layerWidth); break;

    case ACTIV_TANH: apply_tanh_derivs(layerDerivs, layerValues, layerWidth); break;

    case ACTIV_SOFTMAX: apply_softmax_derivs(layerDerivs, layerValues, layerWidth); break;
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