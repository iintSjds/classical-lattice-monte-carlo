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
enum Lattice_Type {kagomi,triangle};

template <class Site_Type>
class Primitive_Cell{
    //definition of primitive cell
    private:
        int dimension;
        std::vector<std::vector<double>> cell_vectors;
        std::vector<Site_Type> sites;
        int sites_number;
        std::vector<std::vector<double>> site_coordinates;
    public:
        Primitive_Cell(Lattice_Type l_type);
        ~Primitive_Cell();
        int get_dimension() const {return dimension;}
        int get_sites_number() const {return sites_number;}
        std::vector<double> get_cell_vector(int index) const {return cell_vectors[index];}
        std::vector<double> get_site_coordinates(int nos) const {return site_coordinates[nos];}
        int print();//print all informations,used for debug
};

template <class Site_Type>
Primitive_Cell<Site_Type>::Primitive_Cell(Lattice_Type l_type){
    dimension=2;
    cell_vectors={{1,0},{0.5,std::sqrt(3)/2}};
    sites_number=3;
    site_coordinates={{0,0},{0.5,0},{0.25,std::sqrt(3)/4}};
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

template <class Site_Type>
class Lattice{
    private:
    public:
        Lattice();
        ~Lattice();
};

class Ising_Site{
    private:
        int s;
    public:
        Ising_Site();
        ~Ising_Site();
        int get_s() const {return s;}
        int set_s(int new_s) {s=new_s;return s;}
};

int main(){
    //mainly for test
    Primitive_Cell<Ising_Site> cell1(kagomi);
    cell1.print();
    return 0;
}
