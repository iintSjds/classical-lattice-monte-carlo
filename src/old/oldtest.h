#include "Model.h"



class Ising_Site{
    private:
        int s;
    public:
        int get_s() const {return s;}
        int set_s(int new_s) {s=new_s;return s;}
        int print() {std::cout<<"In Ising Site,s="<<s<<std::endl;return 1;}
};
int test_primitive_cell(){
    Primitive_Cell<Ising_Site> cell1(KAGOMI);
    cell1.print();
    std::cout<<cell1.get_site(0).get_s()<<std::endl;
    cell1.get_site(0).set_s(1);
    std::cout<<cell1.get_site(0).get_s()<<std::endl;
    return 1;
}

int test_lattice(){
    Lattice<Ising_Site> lattice1(KAGOMI,4);
    for(int i=0;i<lattice1.get_lengths(0);i++)
        for(int j=0;j<lattice1.get_lengths(1);j++){
            for(int k=0;k<lattice1.get_sub_number();k++){
                lattice1.get_cell({i,j}).get_site(k).set_s(1);
                std::cout<<i<<"\t"<<j<<"\t"<<k<<"\t"<<lattice1.get_site({i,j},k).get_s()<<std::endl;
                lattice1.get_site({i,j},k).set_s(1);
                std::cout<<i<<"\t"<<j<<"\t"<<k<<"\t"<<lattice1.get_site({i,j},k).get_s()<<std::endl;
            }
        }
    return 1;
}

int test_kagomi(){
    Kagomi_Lattice<Ising_Site> lattice1(4);
    for(int i=0;i<lattice1.get_lengths(0);i++)
        for(int j=0;j<lattice1.get_lengths(1);j++){
            for(int k=0;k<lattice1.get_sub_number();k++){
                lattice1.get_cell({i,j}).get_site(k).set_s(1);
                std::cout<<i<<"\t"<<j<<"\t"<<k<<"\t"<<lattice1.get_site({i,j},k).get_s()<<std::endl;
                lattice1.get_site({i,j},k).set_s(1);
                std::cout<<i<<"\t"<<j<<"\t"<<k<<"\t"<<lattice1.get_site({i,j},k).get_s()<<std::endl;
            }
        }
    std::vector<Ising_Site> nn=lattice1.get_nn_sites({0,0},0);
    for(int i=0;i<4;i++) nn[i].print();
    return 1;
}

int test_heisenberg(){
    Heisenberg_Model<Kagomi_Lattice> model(1,16);
    model.suggest_update({0,0,0,0.2,0.3});
    model.get_lattice().get_site({0,0},0).print();
    std::cout<<"R="<<model.acc_ratio()<<std::endl;
    model.update();
    model.get_lattice().get_site({0,0},0).print();
    return 1;
}

int main(){
    test_primitive_cell();
    test_lattice();
    test_kagomi();
    test_heisenberg();
    return 0;
}
