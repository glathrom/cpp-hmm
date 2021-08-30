#include <cstdlib>
#include <iostream>
#include <vector>
#include "model.h"

void alphaIncrement(std::vector<double> *alpha, Model *mod, unsigned int ob){
    double **A = mod->A;
    double **B = mod->B;
    int i, j;

    std::vector<double> temp(mod->N);
    std::vector<double> zero(mod->N, 0.0);
    
    temp = (*alpha);
    (*alpha) = zero;
    for( i = 0; i < mod->N; i++ ){
        for( j = 0; j < mod->N; j++ )
            (*alpha)[i] += (A[j][i]* temp[j]);
        (*alpha)[i] *= B[i][ob];
    } 

}

void betaIncrement(std::vector<double> *beta, Model *mod, unsigned int ob){
    double *pi;
    double **A;
    double **B;
    
    std::vector<double> temp(mod->N);
    std::vector<double> zero(mod->N, 0.0);
    
    pi = mod->pi;
    A = mod->A;
    B = mod->B;
    
    temp = *beta;
    *beta = zero;        

    for( int i = 0; i < mod->N; i++ ){
        (*beta)[i] = 0.0;
        for( int j = 0; j < mod->N; j++ ){
            (*beta)[i] += (A[i][j]*B[j][ob]*temp[j]);
        } 
    }
}




void learning(Model *newModel, Model *oldModel, std::vector<unsigned int> *ob){
    double *pi = oldModel->pi;
    double **A = oldModel->A;
    double **B = oldModel->B;
    int i, j, t;

    const unsigned int n = oldModel->N;
    const unsigned int m = oldModel->M;
    const unsigned int T = (unsigned int) ob->size();

    std::vector<double> alpha;
    std::vector<double> beta;

    std::vector<std::vector<double> *> digamma;

    // initialize the digammas
    for( i = 0; i < (int) n; i++ ){
        digamma[i] = new std::vector<double>;
        for( j = 0; j < (int) n; j++ )
            digamma[i]->push_back(0.0);
    }


    for( t = 0; t < (int) ob->size()-1; t++ ){

        // initialize alpha and increment alpha
        if( t == 0 ){
            for( i = 0; i < (int)  oldModel->N; i++ )
                alpha[i] = pi[i]* B[i][ob->at(t)];
        }
        else 
            alphaIncrement(&alpha, oldModel, ob->at(t));

        // initialize beta and increment beta 
        // increment back to time t+1
        for( i = 0; i < (int) n; i++ )
            beta[i] = 1.0;
        for( int tau = ob->size()-2; tau > t; tau--)
            betaIncrement(&beta, oldModel, ob->at(tau));

        // calculate the digamma
        for( i = 0; i < (int) n; i++ ){
            for( j = 0; j < (int) n; j++ ){
                (*(digamma[i]))[j] = alpha[i]*A[i][j]*B[j][ob->at(t+1)]*beta[j];
            }
        }

        // calculate the gammas

        // recalcualte model coefficients
    }

}
