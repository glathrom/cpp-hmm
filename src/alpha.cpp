#include <cstdlib>
#include <cstdio>
#include <vector>
#include "model.h"
#include "alpha.h"




void alphaPass(Model *mod, std::vector<unsigned int> *ob, std::vector<double> *alpha){
    double *pi = mod->pi;
    double **A = mod->A;
    double **B = mod->B;

    for( int i = 0; i < mod->N; i++ ){
        alpha->at(i) = pi[i]* B[i][ob->at(0)];
    }

    for( int i = 0; i < mod->N; i++ )
        printf("%lf\t", alpha->at(i));
}

