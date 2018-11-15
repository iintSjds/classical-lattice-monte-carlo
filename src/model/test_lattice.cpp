#include <iostream>
#include "lattice.h"

int test(){
    Lattice lat1(2,3,4);
    Square_2D sq1(4);
    std::vector<int> p;
    for(int i=0;i<lat1.get_N();i++){
        p=lat1.i2p(i);
        std::cout<<i<<"\t";
        for(int j=0;j<lat1.get_d();j++)
            std::cout<<p[j]<<"\t";
        std::cout<<p[lat1.get_d()]<<"\t"<<lat1.p2i(p)<<std::endl;
        
    }
    for(int i=0;i<sq1.get_N();i++){
        p=sq1.i2p(i);
        std::cout<<i<<"\t";
        for(int j=0;j<lat1.get_d();j++)
            std::cout<<p[j]<<"\t";
        std::cout<<"\t"<<sq1.p2i(p)<<std::endl;

    }
    std::cout<<"sub of sq:"<<sq1.get_sub()<<std::endl;
    std::cout<<sq1.nn(0)[0]<<"\t"<<sq1.nn(0)[1]<<std::endl;

    return 1;
}

int main(){
    test();
    return 0;
}
