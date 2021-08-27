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

    std::cout << "Beta Pass" << std::endl;
    
    // initialize beta for time T-1
    for( int i = 0; i < mod->N; i++ ){
        (*beta)[i] = 1.0;
    }

    std::cout << "t = 0" << "\t\t< ";
    for( int i = 0; i < mod->N; i++ )
        std::cout << beta->at(i) << " ";
    std::cout << ">" << std::endl;

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
        
        std::cout << "t = " << t << "\t\t< ";
        for( int i = 0; i < mod->N; i++ )
            std::cout << beta->at(i) << " ";
        std::cout << ">" << std::endl;

    }

    std::cout << std::endl;

    
}
