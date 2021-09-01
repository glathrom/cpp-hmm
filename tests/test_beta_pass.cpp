#include <cstdlib>
#include <iostream>
#include <vector>
#include "model.h"
#include "alpha.h"
#include "beta.h"


const int Model::N = 2;
const int Model::M = 3;

int main(){

    Model myModel;
    std::vector<unsigned int> obs{0,1,0,2};

    double pi[2] = {0.6, 0.4};

    double  A[2][2] = { {0.7, 0.3},
                        {0.4, 0.6} };

    double  B[2][3] = { {0.1, 0.4, 0.5},
                        {0.7, 0.2, 0.1} };
    
    myModel.set_initial(pi);
    myModel.set_state(&(A[0][0]));
    myModel.set_observe(&(B[0][0]));

    //myModel.initialize();


    std::cout << "The Model" << std::endl;
    for( int i = 0; i < myModel.N; i++ )
        std::cout << myModel.initial(i) << "  ";
    std::cout << std::endl;
    std::cout << std::endl;

    for( int i = 0; i < myModel.N; i++ ){
        for( int j = 0; j < myModel.N; j++ )
            std::cout << myModel.state(i,j) << "  ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    for( int i = 0; i < myModel.N; i++ ){
        for( int j = 0; j < myModel.M; j++ )
            std::cout << myModel.observe(i,j) << "  ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::vector<double> beta(myModel.N);

    betaPass(&myModel, &obs, &beta);

    return 0;
}
