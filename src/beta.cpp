#include <cstdlib>
#include <vector>
#include <model.h>
#include <string.h>
#include <iostream>
#include <cmath>

void generateConstants(Model *mod, std::vector<unsigned int> *ob, std::vector<double> *coef){
    int i, j, t;
    std::vector<double> alpha(mod->N);
    std::vector<double> temp(mod->N);
    std::vector<double> zero(mod->N, 0.0);

    double c;

    t = 0;
    c = 0.0;
    for( i = 0; i < mod->N; i++ ){
        alpha.at(i) = mod->initial(i)* mod->observe(i,ob->at(t));
        c += alpha.at(i);
    }

    coef->at(0) = c;

    for( i = 0; i < mod->N; i++ )
        alpha.at(i) /= c;    

    for( t = 1; t < (int) ob->size(); t++ ){
        temp = alpha;
        alpha = zero;
        c = 0.0;
        for( i = 0; i < mod->N; i++ ){
            for( j = 0; j < mod->N; j++ )
                alpha[i] += (mod->state(j,i)* temp[j]);
            alpha[i] *= mod->observe(i,ob->at(t));
            c += alpha[i];
        } 

        coef->at(t) = c;

        for( i = 0; i < mod->N; i++ )
            alpha[i] /= c;
    }
}


void betaPass(Model *mod, std::vector<unsigned int> *ob, std::vector<double> *beta){
    std::vector<double> temp(mod->N);
    std::vector<double> zero(mod->N, 0.0);
    std::vector<double> coefs(ob->size(), 0.0);

    generateConstants(mod, ob, &coefs);
    
    std::cout << "Beta Pass" << std::endl;

    // initialize beta for time T-1
    for( int i = 0; i < mod->N; i++ ){
        (*beta)[i] = 1.0;
    }

    for( int i = 0; i < mod->N; i++ )
        (*beta)[i] /= coefs[coefs.size()-1];

    std::cout << "t = " << ob->size() - 1 << "\t\t< ";
    for( int i = 0; i < mod->N; i++ )
        std::cout << beta->at(i) << " ";
    std::cout << ">" << std::endl;

    // iteration for beta from time T-2 down to 0
    for(int t = (int) ob->size()-2; t >= 0; --t){
        temp = *beta;
        *beta = zero;        
        
        for( int i = 0; i < mod->N; i++ ){
            (*beta)[i] = 0.0;
            for( int j = 0; j < mod->N; j++ ){
                (*beta)[i] += (mod->state(i,j)*mod->observe(j,ob->at(t+1))*temp[j]);
            } 
        }

        for( int i = 0; i < mod->N; i++ )
            (*beta)[i] /= coefs[t];

        std::cout << "t = " << t << "\t\t< ";
        for( int i = 0; i < mod->N; i++ )
            std::cout << beta->at(i) << " ";
        std::cout << ">" << std::endl;

    }

    std::cout << std::endl;
    
}
