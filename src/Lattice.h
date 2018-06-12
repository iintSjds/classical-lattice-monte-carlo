/********--Definitions of different lattice type--********/
/*
 * Copyright (C) 2018 Xiansheng Cai. All rights reserved.
 */
#include <iostream>
#include <vector>
#include <cmath>

// a generic definition of Bravais Lattice
// Site_Type is provided outside by the required system. TBD in Model.
// all the rest of lattice feature is defined in this file, include lattice type, nearest neighbor, etc.
// special types of lattices can be inheritance from Lattice, which could be defined here or whenever needed.
// Kagomi lattice will be defined here as an example.

//predefined types indicating how to initialize
enum Lattice_Type {KAGOMI,TRIANGLE};


template <class Site_Type>
class Primitive_Cell{
    //definition of primitive cell
    private:
        int dimension;//dimension of the system
        std::vector<std::vector<double>> cell_vectors;//cell vectors, dimension x dimension
        std::vector<Site_Type> sites;//sites of Site_Type, 
        int sites_number;//number of sites per primitive cell
        std::vector<std::vector<double>> site_coordinates;//location of each site in primitive cell
    public:
        Primitive_Cell(Lattice_Type l_type);
        int get_dimension() const {return dimension;}
        int get_sites_number() const {return sites_number;}
        std::vector<double> get_cell_vector(int index) const {return cell_vectors[index];}
        std::vector<double> get_site_coordinates(int nos) const {return site_coordinates[nos];}
        Site_Type& get_site(int nos) {return sites[nos];}
        int print();//print all informations,used for debug
};

template <class Site_Type>
Primitive_Cell<Site_Type>::Primitive_Cell(Lattice_Type l_type){
    if(l_type==KAGOMI){
        dimension=2;
        cell_vectors={{1,0},{0.5,std::sqrt(3)/2}};
        sites_number=3;
        site_coordinates={{0,0},{0.5,0},{0.25,std::sqrt(3)/4}};
        for(int i=0;i<sites_number;i++) sites.push_back(Site_Type());
    }
    if(l_type==TRIANGLE){
        //TBA
    }
}

template <class Site_Type>
int Primitive_Cell<Site_Type>::print(){
    std::cout<<"dimension="<<dimension<<std::endl;
    std::cout<<"sites_number="<<sites_number<<std::endl;
    for(int i=0;i<dimension;i++){
        std::cout<<"a"<<i<<"=(";
        for(int j=0;j<dimension;j++) std::cout<<cell_vectors[i][j]<<"\t";
        std::cout<<")"<<std::endl;
    }
    for(int i=0;i<sites_number;i++){
        std::cout<<"n"<<i<<"=(";
        for(int j=0;j<dimension;j++) std::cout<<site_coordinates[i][j]<<"\t";
        std::cout<<")"<<std::endl;
    }
    return 1;
}



//definition of Lattice
//all defined to be periodic boundary condition
template <class Site_Type>
class Lattice{
    private:
        int dimension;
        std::vector<int> Ls;
        int sub_number;
        std::vector<Primitive_Cell<Site_Type>> cells;
    public:
        Lattice(Lattice_Type l_type,int L);
        int get_dimension() const {return dimension;}
        int get_lengths(int i) const {return Ls[i];}
        int get_sub_number() const {return sub_number;}
        Site_Type& get_site(std::vector<int> r,int sub);
        Primitive_Cell<Site_Type>& get_cell(std::vector<int> r);
};

template <class Site_Type>
Lattice<Site_Type>::Lattice(Lattice_Type l_type,int L){
    if(l_type==KAGOMI){
        dimension=2;
        sub_number=3;
        for(int i=0;i<dimension;i++) Ls.push_back(L);
        for(int i=0;i<std::pow(L,dimension);i++) cells.push_back(Primitive_Cell<Site_Type>(KAGOMI));
    }
}

template <class Site_Type>
Primitive_Cell<Site_Type>& Lattice<Site_Type>::get_cell(std::vector<int> r){
    int p=0;
    //p=r1+r2*L1+r3*L1*L1+...
    for(int i=0;i<dimension-1;i++){
        p+=r[dimension-1-i];
        p*=Ls[dimension-2-i];
    }
    p+=r[0];
    return cells[p];
}

template <class Site_Type>
Site_Type& Lattice<Site_Type>::get_site(std::vector<int> r,int sub){
    int p=0;
    //p=r1+r2*L1+r3*L1*L1+...
    for(int i=0;i<dimension-1;i++){
        p+=r[dimension-1-i];
        p*=Ls[dimension-2-i];
    }
    p+=r[0];
    Primitive_Cell<Site_Type> &cell=cells[p];
    return cell.get_site(sub);
}

