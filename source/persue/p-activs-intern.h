#ifndef P_ACTIVS_INTERN_H
#define P_ACTIVS_INTERN_H

extern float* cross_entropy_derivs(float* derivs, float* nodes, float* targets, int amount);

extern void activ_derivs_apply(float* layerDerivs, float* layerValues, int layerWidth, Activ layerActiv);

extern void activ_values(float* activValues, float* layerValues, int layerWidth, Activ layerActiv);

#endif // P_ACTIVS_INTERN_H
