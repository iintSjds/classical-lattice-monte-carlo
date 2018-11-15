#include <iostream>
#include "lattice.h"

int test(){
    Lattice lat1(_KAGOMI_,4);
    std::vector<int> p;
    for(int i=0;i<lat1.get_N();i++){
        p=lat1.i2p(i);
        std::cout<<i<<"\t";
        for(int j=0;j<lat1.get_d();j++)
            std::cout<<p[j]<<"\t";
        std::cout<<p[lat1.get_d()]<<"\t"<<lat1.p2i(p)<<std::endl;
        
    }

    return 1;
}

int main(){
    test();
    return 0;
}
