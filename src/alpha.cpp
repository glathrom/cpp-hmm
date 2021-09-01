#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <cmath>
#include "model.h"
#include "alpha.h"

double alphaPass(Model *mod, std::vector<unsigned int> *ob, std::vector<double> *alpha){
    int i, j, t;
    std::vector<double> temp(mod->N);
    std::vector<double> zero(mod->N, 0.0);

    double logProb = 0.0;
    double c;

    std::cout << "Alpha Pass" << std::endl;

    t = 0;
    c = 0.0;
    for( i = 0; i < mod->N; i++ ){
        alpha->at(i) = mod->initial(i)* mod->observe(i,ob->at(t));
        c += alpha->at(i);
    }

    for( i = 0; i < mod->N; i++ )
        alpha->at(i) /= c;    

    logProb += log2(c);

    std::cout << "t = 0" << "\t\t< ";
    for( i = 0; i < mod->N; i++ )
        std::cout << alpha->at(i) << " ";
    std::cout << ">" << " normalizing constant = " << c << std::endl;

    for( t = 1; t < (int) ob->size(); t++ ){
        temp = (*alpha);
        (*alpha) = zero;
        c = 0.0;
        for( i = 0; i < mod->N; i++ ){
            for( j = 0; j < mod->N; j++ )
                (*alpha)[i] += (mod->state(j,i)* temp[j]);
            (*alpha)[i] *= mod->observe(i,ob->at(t));
            c += (*alpha)[i];
        } 

        for( i = 0; i < mod->N; i++ )
            (*alpha)[i] /= c;

        logProb += log2(c);

        std::cout << "t = " << t << "\t\t< ";
        for( i = 0; i < mod->N; i++ )
            std::cout << alpha->at(i) << " ";
        std::cout << ">" << " normalizing constant = " << c << std::endl;

    }
    std::cout << std::endl;

    return logProb;
}

