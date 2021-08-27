#include <cstdlib>
#include <vector>
#include <model.h>
#include <string.h>
#include <iostream>


void betaPass(Model *mod, std::vector<unsigned int> *ob, std::vector<double> *beta){

    double *pi;
    double **A;
    double **B;
    
    std::vector<double> temp(mod->N);
    std::vector<double> zero(mod->N, 0.0);
    
    pi = mod->pi;
    A = mod->A;
    B = mod->B;

    std::cout << "entering betaPass function" << std::endl;
    
    // initialize beta for time T-1
    for( int i = 0; i < mod->N; i++ ){
        (*beta)[i] = 1.0;
    }

    // iteration for beta from time T-2 down to 0
    for(int t = (int) ob->size()-1; t > 0; --t){
        temp = *beta;
        *beta = zero;        
        
        for( int i = 0; i < mod->N; i++ ){
            (*beta)[i] = 0.0;
            for( int j = 0; j < mod->N; j++ ){
                (*beta)[i] += (A[i][j]*B[j][ob->at(t)]*temp[j]);
            } 
        }

        for( int i = 0; i < mod->N; i++ )
            std::cout << (*beta)[i] << "  ";
        std::cout << std::endl;
    }

    
}
