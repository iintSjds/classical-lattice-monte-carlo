#include <random>
#include "Model.h"
#include <iostream>

//random generator setup
std::mt19937_64 generator;
std::uniform_real_distribution<double> dist(0.0,1.0);

double rndm(){
    return dist(generator);
}

long long int Nr=100000;
long long int Nh=100000;

static const double J=-1.0;
static const int L=8;
static const int debug=0;

int clear(Heisenberg_Model<Kagomi_Lattice>& model,Kagomi_Lattice<Count>& chi,Kagomi_Lattice<Count>& last_change,long long int n){
    if (debug) std::cout<<"clearing\t"<<model.get_lattice().get_site({0,0},0)*model.get_lattice().get_site({0,0},0)<<std::endl;
    for(int i=0;i<L;i++){
        for(int j=0;j<L;j++){
            for(int k=0;k<chi.get_sub_number();k++){
                chi.get_site({i,j},k)
                    +=(n-last_change.get_site({i,j},k).get_n())
                    *(model.get_lattice().get_site({i,j},k)*model.get_lattice().get_site({0,0},0));
                last_change.get_site({i,j},k).set_n(n);
            }
        }
    }
    return 1;
}


int mc_loop(){
    Heisenberg_Model<Kagomi_Lattice> model(J,L);
    Kagomi_Lattice<Count> chi(L);
    Kagomi_Lattice<Count> last_change(L);
    long long int i;
    for(i=1;i<Nh+1;i++){
        model.suggest_update({rndm(),rndm(),rndm(),rndm(),rndm()});
        if(rndm()<model.acc_ratio()){
            model.update();
        }
    }
    for(i=0;i<Nr;i++){
        model.suggest_update({rndm(),rndm(),rndm(),rndm(),rndm()});
        if(rndm()<model.acc_ratio()){
            if(model.get_pos()[0]+model.get_pos()[1]+model.get_pos()[2]==0){
            //if(debug) std::cout<<model.get_pos()[0]<<model.get_pos()[1]<<model.get_pos()[2]<<std::endl;
            //if(debug) model.get_lattice().get_site(model.get_pos(),model.get_pos().back()).print();
                clear(model,chi,last_change,i);
            }
            else{
                //if(debug) std::cout<<model.get_lattice().get_site(model.get_pos(),model.get_pos().back())*model.get_lattice().get_site({0,0},0)<<std::endl;
                chi.get_site(model.get_pos(),model.get_pos().back())
                    +=(i-last_change.get_site(model.get_pos(),model.get_pos().back()).get_n())
                    *(model.get_lattice().get_site(model.get_pos(),model.get_pos().back())*model.get_lattice().get_site({0,0},0));
                last_change.get_site(model.get_pos(),model.get_pos().back()).set_n(i);
            }
            model.update();
            //if(debug) model.get_lattice().get_site(model.get_pos(),model.get_pos().back()).print();
        }
    }
    clear(model,chi,last_change,i);
    double chi0=chi.get_site({0,0},0).get_n();

    for(int n=0;n<L;n++){
        for(int j=0;j<L;j++){
            std::cout<<n<<"\t"<<j<<"\t";
            for(int k=0;k<3;k++)
                std::cout<<chi.get_site({n,j},k).get_n()/chi0<<"\t";
            std::cout<<std::endl;
        }
    }

    return 1;
}

int main(){
    mc_loop();
    return 1;
}
