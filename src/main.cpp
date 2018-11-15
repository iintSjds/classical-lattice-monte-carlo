#include "./model/lattice.h"
#include <iostream>
#include <ostream>
#include <vector>
#include <cstdlib>
#include "./utility/rng.h"
#include <cmath>

RandomGenerator RNG;

const double pi=3.1415926535897932384626;


const int L=16;
const double BETA=1.0;
const double J1=1.0;
const double J2=0.5;
const long long int MT=100000;
const long long int M=10000000;

typedef Square_2D LAT;

class H_Spin{
    private:
    public:
        int d;
        std::vector<double> s;
        H_Spin():d(3),s(3,0) {s[0]=1;};
        H_Spin(int dim):d(dim),s(dim,0) {s[0]=1;};
        H_Spin(std::vector<double> s0):d(s0.size()),s(s0) {};

        inline const int get_d() {return d;}
        inline const double get_s(int i) {return s[i];}
        int operator+=(const H_Spin& S1){
            if(this->d!=S1.d){
                std::cerr<<"Dimension not match!"<<std::endl;
                std::abort();
            }
            for(int i=0;i<S1.d;i++) this->s[i]+=S1.s[i];
            return 1;
        }
};
H_Spin operator+(const H_Spin& S1, const H_Spin& S2){
    std::vector<double> ns;
    if(S1.d!=S2.d){
        std::cerr<<"Dimension not match!"<<std::endl;
        std::abort();
    }
    for(int i=0;i<S1.d;i++) ns.push_back(S1.s[i]+S2.s[i]);
    H_Spin Ns(ns);
    return Ns;
}
H_Spin operator-(const H_Spin& S1, const H_Spin& S2){
    H_Spin Ns(S1.d);
    if(S1.d!=S2.d){
        std::cerr<<"Dimension not match!"<<std::endl;
        std::abort();
    }
    for(int i=0;i<S1.d;i++) Ns.s[i]=(S1.s[i]-S2.s[i]);
    return Ns;
}
double operator*(const H_Spin S1,const H_Spin S2){
    if(S1.d!=S2.d){
        std::cerr<<"Dimension not match!"<<std::endl;
        std::abort();
    }
    double result=0;
    for(int i=0;i<S1.d;i++) result += (S1.s[i]*S2.s[i]);
    return result;
}
std::ostream& operator<<(std::ostream& os, const H_Spin& S1){
    for(int i=0;i<S1.d;i++) os<<S1.s[i]<<"\t";
    return os;
}

class MC_Machine{
    private:
        double beta;
        double j1;
        double j2;
        LAT lat;
        std::vector<H_Spin> spins;
        std::vector<double> corr;
        std::vector<long long int> tempcounts;
        long long int count;
        long long int accept;
    public:
        MC_Machine():beta(1),j1(1),j2(0), lat(1) {init();};
        MC_Machine(double b,double j,double jj,int l): beta(b),j1(j),j2(jj),lat(l) {init();};
        int init();
        int update(int);
        int clear();
        double dE(int,const  H_Spin&);
        int print();
};

int MC_Machine::init(){
    int N=lat.get_N();
    for(int i=0;i<N;i++){
        double costheta=2*RNG.urn()-1;
        double sintheta=std::sqrt(1-costheta*costheta);
        double phi=RNG.urn()*2*pi;
        std::vector<double> ns(3,3);
        ns[0]=sintheta*std::cos(phi);
        ns[1]=sintheta*std::sin(phi);
        ns[2]=(costheta);
        H_Spin S(ns);
        spins.push_back(S);
        corr.push_back(0);
        tempcounts.push_back(-1);
    }
    count=0;
    accept=0;
}

int MC_Machine::clear(){
    for(int i=0;i<spins.size();i++){
        corr[i]+=(count-tempcounts[i])*(spins[0]*spins[i]);
        tempcounts[i]=count;
    }
    return 1;
}

double MC_Machine::dE(int i,const H_Spin& NS){
    // to be optimized with primitive methods
    const std::vector<int>& nnlist=lat.nn(i);
    const std::vector<int>& nnnlist=lat.nnn(i);
    const H_Spin& DS=(NS-spins[i]);
    H_Spin S1=spins[nnlist[0]];
    H_Spin S2=spins[nnnlist[0]];
    for(int j=1;j<nnlist.size();j++) S1+=spins[nnlist[j]];
    for(int j=1;j<nnnlist.size();j++) S2+=spins[nnnlist[j]];
    return j1*(DS*S1)+j2*(DS*S2);
}

int MC_Machine::update(int isCount){
    // the i-th spin is to be modified
    int i=RNG.urn()*spins.size();
    //generating new spin for it
    H_Spin NS(3);
        double costheta=2*RNG.urn()-1;
        double sintheta=std::sqrt(1-costheta*costheta);
        double phi=RNG.urn()*2*pi;
        NS.s[0]=sintheta*std::cos(phi);
        NS.s[1]=sintheta*std::sin(phi);
        NS.s[2]=(costheta);
    //calculating accept ratio
    double R=std::exp(-beta*dE(i,NS));
    if(isCount==1) count++;
    if(RNG.urn()<R){
        //accept the change
        if(isCount==1){
            accept++;
            //count the corr func
            if(i==0){
                clear();
            }
            else{
                double x=spins[0]*spins[i];
                corr[i]+=(count-tempcounts[i])*x;
                tempcounts[i]=count;
            }
            //update the site
            spins[i]=NS;
        }
        else{
            //just update the site
            spins[i]=NS;
        }
    }
    return 1;
}

int MC_Machine::print(){
    clear();
    for(int i=0;i<spins.size();i++){
        std::cout<<lat.i2p(i)[0]<<"\t"<<lat.i2p(i)[1]<<"\t"<<corr[i]/count<<std::endl;//"\t"<<spins[i]<<std::endl;
    }
    std::cout<<"count:"<<count<<"\taccept:"<<accept<<std::endl;
    return 1;
}

int test(){
    MC_Machine MC1(BETA,J1,J2,L);
    for(long long int i=0;i<MT;i++) MC1.update(0);
    std::cout<<"therm finished"<<std::endl;
    for(long long int i=0;i<M;i++){
        if(i%(M/100)==0){
            std::cout<<(i*100)/M<<std::endl;
        }
        MC1.update(1);
    }
    MC1.print();
    return 1;
}

int main(){
    test();
    return 0;
}
