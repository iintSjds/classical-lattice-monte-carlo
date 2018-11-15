#ifndef GENERAL_PURPOSE_RANDOM_GENERATOR_H
#define GENERAL_PURPOSE_RANDOM_GENERATOR_H

//
// random number generator
//

//
// currently using c++ std random
// trng could be added for support on MPI and openmp
//
#include <random>

class RandomGenerator{
    private:
        std::mt19937_64 _gen;
        std::uniform_real_distribution<double> _rdist;
        //std::uniform_int_distribution<int> _idist;
    public:
        RandomGenerator();
        RandomGenerator(int);
        inline double urn(){
            return _rdist(_gen);
        }
};


#endif
