#include <cstdlib>
#include <iostream>
#include <vector>
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
        (*beta)[i] = 0.0;
        for( int j = 0; j < mod->N; j++ ){
            (*beta)[i] += (mod->state(i,j)*mod->observe(j,ob)*temp[j]);
        } 
        (*beta)[i] /= coef;
    }
}




void iteration(Model *newModel, Model *oldModel, std::vector<unsigned int> *ob){
    double x;
    unsigned int i, j, t;

    const unsigned int n = oldModel->N;
    const unsigned int m = oldModel->M;
    const unsigned int T = (unsigned int) ob->size();

    std::vector<double> alpha;
    std::vector<double> beta;
    std::vector<double> coefs;

    coefs.push_back(0.0);
    for( i = 0; i < n; i++ ){
        alpha.push_back(oldModel->initial(i)* oldModel->observe(i,ob->at(0)));
        coefs[0] += alpha[i];
    }
    for( i = 0; i < n; i++ )
        alpha[i] /= coefs[0];

    for( t = 1; t < T; t++ )
        coefs.push_back( alphaIncrement(&alpha, oldModel, ob->at(t)) );


    std::vector<std::vector<double> *> digamma;
    std::vector<std::vector<double> *> gamma;

    // initialize the digammas
    for( i = 0; i < n; i++ ){
        digamma.push_back(new std::vector<double>);
        for( j = 0; j < n; j++ )
            digamma[i]->push_back(0.0);
    }
   
    /* 
    for( i = 0; i < n; i++ ){
        for( j = 0; j < n; j++ ){
            std::cout << (*(digamma[i]))[j] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    */
    
    // initialize the gammas
    for( t = 0; t < T;  t++ ){
        gamma.push_back(new std::vector<double>);
        for( j = 0; j < n; j++ )
            gamma[t]->push_back(0.0);
    }

    /*
    for( t = 0; t < T;  t++ ){
        for( j = 0; j < n; j++ )
            std::cout << gamma[t]->at(j) << "  ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    */

    for( t = 0; t < T-1; t++ ){

        // initialize alpha and increment alpha
        if( t == 0 ){
            for( i = 0; i < n; i++ )
                alpha[i] = oldModel->initial(i)* oldModel->observe(i,ob->at(t));
        }
        else 
            alphaIncrement(&alpha, oldModel, ob->at(t));

        /*
        // initialize beta and increment beta 
        // increment back to time t+1
        for( i = 0; i < n; i++ )
            beta[i] = 1.0;
        for( unsigned int tau = ob->size()-2; tau > t; tau--)
            betaIncrement(&beta, oldModel, ob->at(tau), T-1-t);

        // calculate the digamma and gammas
        for( i = 0; i < n; i++ ){
            for( j = 0; j < n; j++ ){
                x = alpha[i]*oldModel->state(i,j)*oldModel->observe(j,ob->at(t+1))*beta[j];
                (*(digamma[i]))[j] += x;
                gamma[t]->at(i) += x;
            }
        }

        for( i = 0; i < n; i++ ){
            for( j = 0; j < n; j++ ){
                std::cout << (*(digamma[i]))[j] << "  ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        // recalcualte model coefficients
        for( i = 0; i < n; i++ ){
            newModel->pi[i] = gamma[0]->at(i);
            x = 0.0;
            for(t = 0; t < T-1; t++ )
                x += gamma[t]->at(i);
            for( j = 0; j < n; j++ )
                newModel->A[i][j] = (digamma[i]->at(j))/x;
        }
    */

    }

}
