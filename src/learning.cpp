#include <cstdlib>
#include <iostream>
#include <vector>
#include <string.h>
#include "model.h"

double alphaIncrement(std::vector<double> *alpha, Model *mod, unsigned int ob){
    int i, j;

    double c;
    std::vector<double> temp(mod->N);
    std::vector<double> zero(mod->N, 0.0);
    
    temp = (*alpha);
    (*alpha) = zero;
    c = 0.0;
    for( i = 0; i < mod->N; i++ ){
        for( j = 0; j < mod->N; j++ )
            (*alpha)[i] += (mod->state(j,i)* temp[j]);
        (*alpha)[i] *= mod->observe(i,ob);
        c += (*alpha)[i];
    } 

    for( i = 0; i < mod->N; i++ )
        (*alpha)[i] /= c;

    return c;

}

void betaIncrement(std::vector<double> *beta, Model *mod, unsigned int ob, double coef){
    std::vector<double> temp(mod->N);
    std::vector<double> zero(mod->N, 0.0);
    
    temp = *beta;
    *beta = zero;        

    for( int i = 0; i < mod->N; i++ ){
        beta->at(i) = 0.0;
        for( int j = 0; j < mod->N; j++ ){
            (*beta)[i] += (mod->state(i,j)*mod->observe(j,ob)*temp[j]);
        } 
        (*beta)[i] /= coef;
    }
}


void iteration(Model *newModel, Model *oldModel, std::vector<unsigned int> *ob){
    double x;
    unsigned int i, j, k, t;

    const unsigned int n = oldModel->N;
    const unsigned int m = oldModel->M;
    const unsigned int T = (unsigned int) ob->size();

    std::vector<double> alpha;
    std::vector<double> beta;
    std::vector<double> coefs;
    double prob;

    double *pi = new double [n];
    double *A = new double [n*n];
    double *B = new double [n*m];

    coefs.push_back(0.0);
    for( i = 0; i < n; i++ ){
        beta.push_back(0.0);
        alpha.push_back(oldModel->initial(i)* oldModel->observe(i,ob->at(0)));
        coefs[0] += alpha[i];
        prob = coefs[0];
    }
    for( i = 0; i < n; i++ )
        alpha[i] /= coefs[0];

    for( t = 1; t < T; t++ ){
        coefs.push_back( alphaIncrement(&alpha, oldModel, ob->at(t)) );
        prob *= coefs.back();
    }

    std::vector<std::vector<double> *> digamma;
    std::vector<std::vector<double> *> gamma;

    // initialize the digammas
    for( i = 0; i < n; i++ ){
        digamma.push_back(new std::vector<double>);
        for( j = 0; j < n; j++ )
            digamma[i]->push_back(0.0);
    }
   
    // initialize the gammas
    for( t = 0; t < T;  t++ ){
        gamma.push_back(new std::vector<double>);
        for( j = 0; j < n; j++ )
            gamma[t]->push_back(0.0);
    }

    
    for( t = 0; t < T-1; t++ ){

        // initialize alpha and increment alpha
        if( t == 0 ){
            for( i = 0; i < n; i++ )
                alpha[i] = oldModel->initial(i)* oldModel->observe(i,ob->at(t))/coefs[0];
        }
        else 
            alphaIncrement(&alpha, oldModel, ob->at(t));


        // initialize beta and increment beta 
        // increment back to time t+1
        for( i = 0; i < n; i++ )
            beta[i] = 1.0/coefs.back();
        for( unsigned int tau = ob->size()-2; tau > t; tau--)
            betaIncrement(&beta, oldModel, ob->at(tau+1), coefs[tau]);

   
        // calculate the digamma and gammas
        for( i = 0; i < n; i++ ){
            for( j = 0; j < n; j++ ){
                x = alpha[i]*oldModel->state(i,j)*oldModel->observe(j,ob->at(t+1))*beta[j];
                digamma[i]->at(j) += x;
                gamma[t]->at(i) += x;
            }
        }
    }

    // recalcualte model coefficients

    for( i = 0; i < n; i++ ){
        pi[i] = gamma[0]->at(i);
        x = 0.0;
        for(t = 0; t < T-1; t++ )
            x += gamma[t]->at(i);
        for( j = 0; j < n; j++ )
            A[n*i+j] = (digamma[i]->at(j))/x;
    }

    newModel->set_initial(pi);
    newModel->set_state(A);
    alphaIncrement(&alpha, oldModel, ob->back());
    *(gamma[T-1]) = alpha;

    
    memset(B, 0, n*m*sizeof(double));
    for( j = 0; j < n; j++ ){
        x = 0.0;
        for( t = 0; t < T; t++ ){
            x += gamma[t]->at(j);
            B[j*m + ob->at(t)] += gamma[t]->at(j);
        }
        for( k = 0; k < m; k++ )
            B[j*m+k] /= x;
    }
    
    newModel->set_observe(B);
}
