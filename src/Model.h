/********--Definition of different models--********/
/* 
 * Copyright (C) 2018 Xiansheng Cai. All rights reserved.
 */

#include "Lattice.h"
#include <cmath>
#include <assert.h>

class Count{
    private:
        double n;
    public:
        double get_n() const {return n;}
        double set_n(double a) {n=a;return n;}
        Count(){n=0;}
        Count(double i){n=i;}
        void operator += (double i){
            n+=i;
        }
};

class Heisenberg_Spin{
    private:
        int dimension;
        std::vector<double> s;
    public:
        Heisenberg_Spin();
        Heisenberg_Spin(int d);
        Heisenberg_Spin(double theta,double phi);
        int get_dimension() const {return dimension;}
        double get_s(int i) const {return s[i];}
        int set_s(std::vector<double> s0) {s=s0;return 1;}
        int print() const {std::cout<<"In Heisenberg_Spin,x="<<get_s(0)<<"\ty="<<get_s(1)<<"\tz="<<get_s(2)<<std::endl;return 1;}
};

double operator * (Heisenberg_Spin spin1,Heisenberg_Spin spin2){
    double result=0;
    //std::cout<<spin1.get_dimension()<<spin2.get_dimension()<<std::endl;
    assert(spin1.get_dimension()==spin2.get_dimension());
    for(int i=0;i<spin1.get_dimension();i++) result+=spin1.get_s(i)*spin2.get_s(i);
    return result;
}


Heisenberg_Spin::Heisenberg_Spin(double theta,double phi):
dimension(3)
{
    s.push_back(std::sin(theta)*std::sin(phi));
    s.push_back(std::sin(theta)*std::cos(phi));
    s.push_back(std::cos(theta));
}

Heisenberg_Spin::Heisenberg_Spin():
dimension(3)
{
    for(int i=0;i<dimension-1;i++) s.push_back(0);
    s.push_back(1);
}
Heisenberg_Spin::Heisenberg_Spin(int d):
dimension(d)
{
    for(int i=0;i<dimension;i++) s.push_back(0);
}

template <template<class> class Lat>
class Heisenberg_Model{
    private:
        Lat<Heisenberg_Spin> lattice;
        double J;
        double beta=1;
        int rand_requirement=lattice.get_dimension()+1+2;//require rand number to decide all dimension(d) & sublattice(1) & spin(2)
        std::vector<int> sug_pos;
        Heisenberg_Spin sug_site;
    public:
        std::vector<int> get_pos() const {return sug_pos;}
        Lat<Heisenberg_Spin>& get_lattice() {return lattice;}
        Heisenberg_Model(double J0,int L0);
        double get_J() const {return J;}
        double get_beta() const {return beta;}
        double set_J(double newJ) {J=newJ;return J;}
        double set_beta(double newbeta) {beta=newbeta;return beta;}
        int suggest_update(std::vector<double> randn);//suggest
        double acc_ratio();
        int update();
};

template<template<class> class Lat>
int Heisenberg_Model<Lat>::update(){
    //Heisenberg_Spin& oldspin=lattice.get_site(sug_pos,sug_pos.back());
    lattice.get_site(sug_pos,sug_pos.back())=sug_site;
    //std::vector<double> ns;
    //for(int i=0;i<oldspin.get_dimension();i++) ns.push_back(sug_site.get_s(i));
    //oldspin.set_s(ns);
    return 1;
}


template<template<class> class Lat>
double Heisenberg_Model<Lat>::acc_ratio(){
    Heisenberg_Spin oldspin=lattice.get_site(sug_pos,sug_pos.back());
    std::vector<Heisenberg_Spin> nn=lattice.get_nn_sites(sug_pos,sug_pos.back());
    double oldE=0,newE=0;
    for(int i=0;i<nn.size();i++) {
        oldE+=J*(nn[i]*oldspin);
        newE+=J*(nn[i]*sug_site);
    }
    return std::exp((newE-oldE)*beta);
}


template<template<class> class Lat>
int Heisenberg_Model<Lat>::suggest_update(std::vector<double> randn){
    int i;
    for(i=0;i<lattice.get_dimension();i++) sug_pos[i]=int(lattice.get_Ls(i)*randn[i]);
    sug_pos[i]=int(lattice.get_sub_number()*randn[i]);
    sug_site=Heisenberg_Spin(std::acos(randn[i+1]),2*M_PI*randn[i+2]);
    return 1;
}

template <template<class> class Lat>
Heisenberg_Model<Lat>::Heisenberg_Model(double J0,int L0):
lattice(L0)
{
    J=J0;
    for(int i=0;i<lattice.get_dimension()+1;i++) sug_pos.push_back(0);
}
