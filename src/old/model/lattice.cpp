#include "lattice.h"

void Lattice::initialize(std::vector<int> l,int sub){
    dimension=l.size();
    length=l;
    subnum=sub;
    N=1;
    for(int i=0;i<dimension;i++)
        N*=length[i];
    N*=subnum;
}

Lattice::Lattice(std::vector<int> l,int sub){
    type=_CUSTOM_;
    initialize(l,sub);
}

Lattice::Lattice(Lattice_Type t, std::vector<int> l){
    type=t;
    switch (type){
        case _KAGOMI_: subnum=3;dimension=2;break;
        case _SQUARE_: subnum=1;dimension=2;break;
        case _TRIANGLE_: subnum=1;dimension=2;break;
        default: subnum=1;dimension=2;break;
    }
    if(l.size()!=dimension){
        throw "Dimension of parameters not met!";
    }
    initialize(l,subnum);
}

Lattice::Lattice(Lattice_Type t, int L){
    type=t;
    switch (type){
        case _KAGOMI_: subnum=3;dimension=2;break;
        case _SQUARE_: subnum=1;dimension=2;break;
        case _TRIANGLE_: subnum=1;dimension=2;break;
        default: subnum=1;dimension=2;break;
    }
    std::vector<int> l;
    for(int i=0;i<dimension;i++) l.push_back(L);
    initialize(l,subnum);
}

int Lattice::p2i(std::vector<int> p){
    if(p.size()!=dimension+1) throw "Dimension not met!";
    int result=0;
    result+=p[0];
    for(int i=1;i<dimension;i++){
        result*=length[i];
        result+=p[i];
    }
    result*=subnum;
    result+=p[dimension];
    return result;
}

std::vector<int> Lattice::i2p(int n){
    std::vector<int> result(dimension+1,0);
    result[dimension]=n%subnum;
    n=n/subnum;
    for(int i=dimension-1;i>0;i--){
        result[i]=n%length[i];
        n=n/length[i];
    }
    result[0]=n;
    return result;
}
