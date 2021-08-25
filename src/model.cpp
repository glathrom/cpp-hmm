#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <random>
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

void Model::initialize(void){
    double uniform = (1.0/(double) N);
    double sigma = uniform*0.00033333;
    double uniform2 = (1.0/(double) M);
    double sigma2 = uniform2*0.00033333;
    double x;
    
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0, sigma);
    std::normal_distribution<double> distribution2(0, sigma2);

    // initialize initial probs
    double sum = 0.0;
    for( int i = 0; i < N; i++ ){
        while(true){
            x = distribution(generator);
            if( (x < uniform) && (x > -uniform) )
                break;
        }
        initial[i] = (uniform + x);
        sum += initial[i];
    }   
   
   for( int i  = 0; i < N; i++ )
      initial[i] /= sum; 

   double sumA, sumB;
   for( int i = 0; i < N; i++ ){
       sumA = 0.0;
       for(int j = 0; j < N; j++){
           while( true ){
               x = distribution(generator);
               if( (x < uniform) && (x > -uniform) )
                   break;
           }
           state[i*N+j] = (uniform + x);
           sumA += state[i*N+j];
       }

       sumB = 0.0;
       for(int j = 0; j < M; j++){
           while( true ){
               x = distribution2(generator);
               if( (x < uniform2) && (x > -uniform2) )
                   break;
           }
           observe[i*M+j] = (uniform2 + x);
           sumB += observe[M*i+j];
       }

       for( int j = 0; j < N; j++ )
           state[i*N+j] /= sumA;
       
       for( int j = 0; j < M; j++ )
           observe[i*M+j] /= sumB;
   }
}
