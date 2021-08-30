#ifndef MODEL_H
#define MODEL_H

#include <vector>

class Model {

    public:
        static const int N, M;
        
        Model();
        ~Model();
        void randomize(void);
        
        // getters
        double initial(unsigned int);
        double state(unsigned int, unsigned int);
        double observe(unsigned int, unsigned int);

        // setters
        void set_initial(double *);
        void set_state(double *);
        void set_observe(double *);
    
    private:
        std::vector<double> pi;
        std::vector<std::vector<double> *> A;
        std::vector<std::vector<double> *> B;

};


#endif
