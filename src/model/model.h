#ifndef _GENERAL_PURPOSE_MC_MODEL_
#define _GENERAL_PURPOSE_MC_MODEL_

#include <vector>
#include <string>

class Model{
    //a general purpose abstract class for mc loop
    private:
        int rand_per_update;//random numbers required by one update
    public:
        inline Model(int n):rand_per_update(n){};
        inline int get_rpu() {return rand_per_update;}
        virtual void init();//initializer
        virtual void update(std::vector<double> rand);//update with random numbers in rand
        virtual std::string sresult();//write results,return a string of results to be written in the output file
};

#endif
