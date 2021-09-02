#include <cstdlib>
#include <cstdio>
#include <random>
#include <vector>
#include <iostream>
#include "model.h"


Model::Model(){

    for( int i = 0; i < N; i++ ){
        pi.push_back(0.0);
        A.push_back( new std::vector<double> (N) );
        B.push_back( new std::vector<double> (M) );
    }
}

Model::~Model(){
    printf("model destructor ran\n");
}

std::vector<double> * Model::get_initial(void){
    return &pi;
}

void Model::set_initial(double* pi_){
    for(int i = 0; i < N; i++)
        pi[i] = *(pi_+i);
}

std::vector<std::vector<double> *> *Model::get_state(void){
    return &A;
}

void Model::set_state(double *A_){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++ )
            A[i]->at(j) = *(A_+i*N+j);
    }
}

std::vector<std::vector<double> *> *Model::get_observe(void){
    return &B;
}

void Model::set_observe(double* B_){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++ )
            B[i]->at(j) = *(B_+i*M+j);
    }
}

void Model::randomize(void){
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
        pi[i] = (uniform + x);
        sum += pi[i];
    }   
   
   for( int i  = 0; i < N; i++ )
      pi[i] /= sum; 

   double sumA, sumB;
   for( int i = 0; i < N; i++ ){
       sumA = 0.0;
       for(int j = 0; j < N; j++){
           while( true ){
               x = distribution(generator);
               if( (x < uniform) && (x > -uniform) )
                   break;
           }
           A[i]->at(j) = (uniform + x);
           sumA += A[i]->at(j);
       }

       sumB = 0.0;
       for(int j = 0; j < M; j++){
           while( true ){
               x = distribution2(generator);
               if( (x < uniform2) && (x > -uniform2) )
                   break;
           }
           B[i]->at(j) = (uniform2 + x);
           sumB += B[i]->at(j);
       }

       for( int j = 0; j < N; j++ )
           A[i]->at(j) /= sumA;
       
       for( int j = 0; j < M; j++ )
           B[i]->at(j) /= sumB;
   }
}

double Model::initial(unsigned int i){
    return pi[i];
}

double Model::state(unsigned int i, unsigned int j){
    return A[i]->at(j);
}

double Model::observe(unsigned int i, unsigned int j){
    return B[i]->at(j);
}

void Model::print(void){
    std::cout << "Number of States = " << N << std::endl;
    std::cout << "Number of Observables = " << M << std::endl;
    std::cout << std::endl;
    std::cout << "Initial Probabilities" << std::endl;
    std::cout << "\t";
    for( int i = 0; i < N; i++ )
        std::cout << pi[i] << "  ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "State Transition Probabilities" << std::endl << "\t";
    for( int i = 0; i < N; i++ ){
        for( int j = 0; j < N; j++ )
            std::cout << A[i]->at(j) << "  ";
        std::cout << std::endl << "\t";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Observation Probabilities" << std::endl << "\t";
    for( int i = 0; i < N; i++ ){
        for( int j = 0; j < M; j++ )
            std::cout << B[i]->at(j) << "  ";
        std::cout << std::endl << "\t";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}
