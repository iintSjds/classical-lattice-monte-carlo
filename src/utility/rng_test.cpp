#include "./rng.h"
#include <iostream>

int test(){
    double x=0;
    RandomGenerator RNG;
    int i;
    for(i=0;i<1000000;i++)
        x+=RNG.urn();
    std::cout<<x/i<<std::endl;

    return 0;
}

int main(){
    test();
    return 0;
}
