#include "rng.h"

RandomGenerator::RandomGenerator(){
    std::uniform_real_distribution<double> dist(0.0,1.0);
    std::random_device dev;
    _rdist=dist;
    _gen.seed(dev());
}

RandomGenerator::RandomGenerator(int seed){
    std::uniform_real_distribution<double> dist(0.0,1.0);
    _rdist=dist;
    _gen.seed(seed);
}

