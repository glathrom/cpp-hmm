#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "model.h"


Model::Model(){
    
    initial = new double[N];
    state = new double [N*N];
    observe= new double [N*M];

    pi = initial;
    A = new double*[N];
    B = new double*[N];

    for( int i = 0; i < N; i++ ){
        A[i] = &state[i*N];
        B[i] = &observe[i*M];
    }
}

Model::~Model(){
    printf("model destructor ran\n");
}


void Model::set_initial(double* pi_){
    memcpy(initial, pi_, N*sizeof(double));
}

void Model::set_state(double *A_){
    for(int i = 0; i < N; i++)
        memcpy(state+N*i,A_+N*i,N*sizeof(double));
}

void Model::set_observe(double* B_){
    for(int i = 0; i < N; i++)
        memcpy(observe+M*i,B_+M*i,M*sizeof(double));
}
