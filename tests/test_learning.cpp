#include <cstdlib>
#include <iostream>
#include <vector>
#include "model.h"
#include "learning.h"


const int Model::N = 2;
const int Model::M = 3;

int main(){

    Model M1, M2;
    std::vector<unsigned int> obs{0,1,0,2};

    double pi[2] = {0.6, 0.4};

    double  A[2][2] = { {0.7, 0.3},
                        {0.4, 0.6} };

    double  B[2][3] = { {0.1, 0.4, 0.5},
                        {0.7, 0.2, 0.1} };
     
    M1.set_initial(pi);
    M1.set_state(&(A[0][0]));
    M1.set_observe(&(B[0][0]));
    

    //M1.randomize();

    std::cout << "size of initial = " <<  M1.get_initial()->size() << std::endl;    
    std::cout << "size of state = " <<  M1.get_state()->size() << std::endl;    
    std::cout << "size of observe = " <<  M1.get_observe()->at(1)->size() << std::endl << std::endl;
    
    std::cout << "The Model" << std::endl;
    for( int i = 0; i < M1.N; i++ )
        std::cout << M1.initial(i) << "  ";
    std::cout << std::endl;
    std::cout << std::endl;

    for( int i = 0; i < M1.N; i++ ){
        for( int j = 0; j < M1.N; j++ )
            std::cout << M1.state(i,j) << "  ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    for( int i = 0; i < M1.N; i++ ){
        for( int j = 0; j < M1.M; j++ )
            std::cout << M1.observe(i,j) << "  ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    iteration(&M2, &M1, &obs);

    return 0;
}
