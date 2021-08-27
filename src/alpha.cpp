#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include "model.h"
#include "alpha.h"




void alphaPass(Model *mod, std::vector<unsigned int> *ob, std::vector<double> *alpha){
    double *pi = mod->pi;
    double **A = mod->A;
    double **B = mod->B;
    int i, j, t;
    std::vector<double> temp(mod->N);
    std::vector<double> zero(mod->N, 0.0);

    std::cout << "Alpha Pass" << std::endl;

    t = 0;
    for( i = 0; i < mod->N; i++ )
        alpha->at(i) = pi[i]* B[i][ob->at(t)];
    

    std::cout << "t = 0" << "\t\t< ";
    for( i = 0; i < mod->N; i++ )
        std::cout << alpha->at(i) << " ";
    std::cout << ">" << std::endl;

    for( t = 1; t < (int) ob->size(); t++ ){
        temp = (*alpha);
        (*alpha) = zero;
        for( i = 0; i < mod->N; i++ ){
            for( j = 0; j < mod->N; j++ )
                (*alpha)[i] += (A[j][i]* temp[j]);
            (*alpha)[i] *= B[i][ob->at(t)];
        } 

        std::cout << "t = " << t << "\t\t< ";
        for( i = 0; i < mod->N; i++ )
            std::cout << alpha->at(i) << " ";
        std::cout << ">" << std::endl;

    }
    std::cout << std::endl;
}

