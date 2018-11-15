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
    initialize(l,sub);
}

Lattice::Lattice(int dim,int sub,int L){
    std::vector<int> l;
    for(int i=0;i<dim;i++){
        l.push_back(L);
    }
    initialize(l,sub);
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

Square_Lattice::Square_Lattice(int dim,int L)
    :Lattice(dim,1,L)
{}

Square_2D::Square_2D(int L)
    :Square_Lattice(2,L)
{
    //fill the nearest neighbor charts with constructor
    for(int i=0;i<get_N();i++){
        std::vector<int> nnlist;
        nnlist.push_back(((i2p(i)[0]+L+1)%L)*L + (i2p(i)[1]+L)%L);
        nnlist.push_back(((i2p(i)[0]+L-1)%L)*L + (i2p(i)[1]+L)%L);
        nnlist.push_back(((i2p(i)[0]+L)%L)*L + (i2p(i)[1]+L+1)%L);
        nnlist.push_back(((i2p(i)[0]+L)%L)*L + (i2p(i)[1]+L-1)%L);
        std::vector<int> nnnlist;
        nnnlist.push_back(((i2p(i)[0]+L+1)%L)*L + (i2p(i)[1]+L+1)%L);
        nnnlist.push_back(((i2p(i)[0]+L-1)%L)*L + (i2p(i)[1]+L+1)%L);
        nnnlist.push_back(((i2p(i)[0]+L+1)%L)*L + (i2p(i)[1]+L-1)%L);
        nnnlist.push_back(((i2p(i)[0]+L-1)%L)*L + (i2p(i)[1]+L-1)%L);
        nnchart.push_back(nnlist);
        nnnchart.push_back(nnnlist);
    }
}

std::vector<int> Square_2D::nn(int i){
    return nnchart[i];
}

std::vector<int> Square_2D::nnn(int i){
    return nnnchart[i];
}
/*
std::vector<int> Square_2D::nn(int i){
    return nn(i2p(i));
}

std::vector<int> Square_2D::nnn(int i){
    return nnn(i2p(i));
}

std::vector<int> Square_2D::nn(std::vector<int> p){
    std::vector<int> result;
    int L=get_L(0);
    if(p[0]!=0) result.push_back(p2i(p)-L);
    else result.push_back(p2i(p)+L*(L-1));
    if(p[0]==L-1) result.push_back(p2i(p)-L*(L-1));
    else result.push_back(p2i(p)+L);
    if(p[1]==0) result.push_back(p2i(p)+L-1);
    else result.push_back(p2i(p)-1);
    if(p[1]==L-1) result.push_back(p2i(p)-L+1);
    else result.push_back(p2i(p)+1);
    return result;
}

std::vector<int> Square_2D::nnn(std::vector<int> p){
    std::vector<int> result;
    int L=get_L(0);
    if(p[0]!=0) result.push_back(p2i(p)-L);
    else result.push_back(p2i(p)+L*(L-1));
    if(p[0]==L-1) result.push_back(p2i(p)-L*(L-1));
    else result.push_back(p2i(p)+L);
    if(p[1]==0) result.push_back(p2i(p)+L-1);
    else result.push_back(p2i(p)-1);
    if(p[1]==L-1) result.push_back(p2i(p)-L+1);
    else result.push_back(p2i(p)+1);
    return result;
}
*/

