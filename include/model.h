#ifndef MODEL_H
#define MODEL_H


class Model {

    public:
        static const int N, M;
        double* pi;
        double** A;
        double** B;
        
        Model();
        ~Model();
        void initialize(void);
        
        void set_initial(double*);
        void set_state(double*);
        void set_observe(double*);
    
    private:
        double* initial;
        double* state;
        double* observe;

};


#endif
