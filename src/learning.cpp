#include <cstdlib>
#include <iostream>
#include <vector>
#include "model.h"


void learning(Model *newModel, Model *oldModel, std::vector<unsigned int> *ob){
    double *pi = oldModel->pi;
    double **A = oldModel->A;
    double **B = oldModel->B;
    int i, j, t;

    const unsigned int n = oldModel->N;
    const unsigned int m = oldModel->M;
    const unsigned int T = (unsigned int) ob->size();

    std::vector<double> alpha;
    std::vector<double> tempA;

    std::vector<double> beta;
    std::vector<double> tempB;

    for( t = 0; t < (int) ob->size(); t++ ){

        if( t == 0 ){
            for( i = 0; i < (int)  oldModel->N; i++ ){
                alpha[i] = pi[i]* B[i][ob->at(t)];
                beta[i] = 1.0;
            }
        } else {
            // form alpha vector @ time t

            // form beta vector @ time T-1-t

        }

        // calculate the digamma

        // calculate the gammas

        // recalcualte model coefficients
    }

}
