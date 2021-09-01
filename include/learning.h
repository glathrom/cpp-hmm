#ifndef LEARNING_H
#define LEARNING_H

#include <vector>
#include "model.h"

double alphaIncrement(std::vector<double> *, Model *, unsigned int );

void betaIncrement(std::vector<double> *, Model *, unsigned int , double );

void iteration(Model *, Model *, std::vector<unsigned int> *);

#endif
