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

    M1.print();

    iteration(&M2, &M1, &obs);

    M2.print();

    return 0;
}
