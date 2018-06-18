#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <ctime>
#include <omp.h>
#include <string>
#include <cstdlib>
#include <fstream>

#define PI 3.1415926535897932384626

#define PAR_LEN 16
#define PAR_DIM 3
#define N 16

#define PAR_NT 10000000
#define PAR_NR 1000000000

double J=1.0;

int debug=0;
long long int acc=0;
long long int tot=0;
long long int test_count=0;

//random generator setup
std::mt19937_64 generator;

std::uniform_real_distribution<double> dist(0.0,1.0);

double rndm(){
    return dist(generator);
}


int print(double corr[PAR_LEN][PAR_LEN][3]){
    //print corr
    for(int i=0;i<PAR_LEN;i++){
        for(int j=0;j<PAR_LEN;j++){
            std::cout<<i<<"\t"<<j<<"\t";
            for(int k=0;k<3;k++){
                std::cout<<corr[i][j][k]/corr[0][0][0]<<((k==2)?"\n":"\t");
            }
        }
    }
    std::cout<<std::endl;
    return 1;
}

int init(int isFirst,double lattice[PAR_LEN][PAR_LEN][3][3],double corr[PAR_LEN][PAR_LEN][3],double lastChange[PAR_LEN][PAR_LEN][3]){
    // initialize the lattice
    for(int i=0;i<PAR_LEN;i++){
        for(int j=0;j<PAR_LEN;j++){
            for(int k=0;k<3;k++){
                if(isFirst){
                    double theta=std::acos(2*rndm()-1);
                    double phi=rndm()*2*PI;
                    lattice[i][j][k][0]=std::sin(theta)*std::cos(phi);
                    lattice[i][j][k][1]=std::sin(theta)*std::sin(phi);
                    lattice[i][j][k][2]=std::cos(theta);
                }
                corr[i][j][k]=0;
                lastChange[i][j][k]=-1;
            }
        }
    }
    return 1;
}

double dE(int i,int j,int k,double x,double y,double z,double lattice[PAR_LEN][PAR_LEN][3][3]){
    //calculate energy change for given update suggestion
    int nSites[4][3];
    double site[3]={x,y,z};
    if(k==0){
        nSites[0][0]=i;nSites[0][1]=j;nSites[0][2]=1;
        nSites[1][0]=i;nSites[1][1]=j;nSites[1][2]=2;
        nSites[2][0]=(i+1)%PAR_LEN;nSites[2][1]=(j-1+PAR_LEN)%PAR_LEN;nSites[2][2]=1;
        nSites[3][0]=i;nSites[3][1]=(j-1+PAR_LEN)%PAR_LEN;nSites[3][2]=2;
    }
    if(k==1){
        nSites[0][0]=(i-1+PAR_LEN)%PAR_LEN;nSites[0][1]=j;nSites[0][2]=2;
        nSites[1][0]=i;nSites[1][1]=j;nSites[1][2]=2;
        nSites[2][0]=i;nSites[2][1]=j;nSites[2][2]=0;
        nSites[3][0]=(i-1+PAR_LEN)%PAR_LEN;nSites[3][1]=(j+1)%PAR_LEN;nSites[3][2]=0;
    }
    if(k==2){
        nSites[0][0]=i;nSites[0][1]=j;nSites[0][2]=0;
        nSites[1][0]=i;nSites[1][1]=j;nSites[1][2]=1;
        nSites[2][0]=i;nSites[2][1]=(j+1)%PAR_LEN;nSites[2][2]=0;
        nSites[3][0]=(i+1)%PAR_LEN;nSites[3][1]=j;nSites[3][2]=1;
    }
    double result=0;
    for(int s=0;s<4;s++){
        for(int t=0;t<3;t++)
            result+=J*(site[t]-lattice[i][j][k][t])*lattice[nSites[s][0]][nSites[s][1]][nSites[s][2]][t];
    }
    return result;
}

int clear(double lattice[PAR_LEN][PAR_LEN][3][3],double corr[PAR_LEN][PAR_LEN][3],double lastChange[PAR_LEN][PAR_LEN][3],long long int globaln){
    //clear all updates restored for corr
    for(int i=0;i<PAR_LEN;i++){
        for(int j=0;j<PAR_LEN;j++){
            for(int k=0;k<3;k++){
                if(debug&&((i+j)==0)&&k==1) test_count+=globaln-lastChange[0][0][1];
                double x=0;
                for(int d=0;d<3;d++) x+=lattice[0][0][0][d]*lattice[i][j][k][d];
                corr[i][j][k]+=(globaln-lastChange[i][j][k])*x;
                lastChange[i][j][k]=globaln;
            }
        }
    }
    return 1;
}

int update(int isCount,double lattice[PAR_LEN][PAR_LEN][3][3],double corr[PAR_LEN][PAR_LEN][3], double lastChange[PAR_LEN][PAR_LEN][3],long long int globaln){
    //update the config for one flip
    //if isCount=1 then count the update, else just update for thermalization

    //choose the site to flip
    double rd1=rndm();
    int i=rd1*PAR_LEN;//cell label i
    rd1=rd1*PAR_LEN-i;
    int j=rd1*PAR_LEN;//cell label j
    rd1=rd1*PAR_LEN-j;
    int k=rd1*3;// k-th site in the cell

    //give suggestion of new value
    double theta=std::acos(2*rndm()-1);
    double phi=rndm()*2*PI;
    double x=std::sin(theta)*std::cos(phi);
    double y=std::sin(theta)*std::sin(phi);
    double z=std::cos(theta);

    //calculate the accept ratio
    double R=std::exp(-dE(i,j,k,x,y,z,lattice));
    tot++;
    if(rndm()<R){
        //accept the change
        acc++;
        if(isCount==1){
            //count the corr func
            if(i+j+k==0){
                clear(lattice,corr,lastChange,globaln);
            }
            else{
                if(debug&&((i+j)==0)&&k==1) test_count+=globaln-lastChange[0][0][1];
                double x=0;
                for(int d=0;d<3;d++) x+=lattice[0][0][0][d]*lattice[i][j][k][d];
                corr[i][j][k]+=(globaln-lastChange[i][j][k])*x;
                lastChange[i][j][k]=globaln;
            }
            //update the site
            lattice[i][j][k][0]=x;
            lattice[i][j][k][1]=y;
            lattice[i][j][k][2]=z;
        }
        else{
            //just update the site
            lattice[i][j][k][0]=x;
            lattice[i][j][k][1]=y;
            lattice[i][j][k][2]=z;
        }
    }
    return 1;
}

int test(int nTherm,long long int nRun,double corr[PAR_LEN][PAR_LEN][3]){
    long long int globaln;
    double lattice[PAR_LEN][PAR_LEN][3][3];
    double lastChange[PAR_LEN][PAR_LEN][3];
    init(1,lattice,corr,lastChange);
    for(long long int n=0;n<nTherm;n++){
        update(0,lattice,corr,lastChange,0);
    }
    for(globaln=0;globaln<nRun;globaln++){
        if((globaln*10)%nRun==0) std::cout<<"\t"<<(globaln*10)/nRun<<std::endl;
        update(1,lattice,corr,lastChange,globaln);
    }
    //std::cout<<std::endl;
    clear(lattice,corr,lastChange,globaln-1);
    if(debug) std::cout<<globaln<<"\t"<<corr[0][0][0]<<std::endl;
    return 1;
}

int main(int argc,char* argv[]){
    std::ofstream file;
    if(argc>=2){
        std::string s=argv[1];
        J=std::atof(s.c_str());
	std::cout<<"J="<<J<<std::endl;
        if(argc==3){
            std::string filename=argv[2];
            file.open(filename);
        }
    }
    double each[N][PAR_LEN][PAR_LEN][3];
    double avg[PAR_LEN][PAR_LEN][3];
    double sd[PAR_LEN][PAR_LEN][3];


    for(int i=0;i<PAR_LEN;i++){
        for(int j=0;j<PAR_LEN;j++){
            for(int k=0;k<3;k++){
                avg[i][j][k]=0;
                sd[i][j][k]=0;
            }
        }
    }
    {
        //#pragma omp parallel
        //#pragma omp for
        for(int n=0;n<N;n++){
            std::cout<<n<<std::endl;
            test(PAR_NT,PAR_NR,each[n]);
        }
    }


    for(int i=0;i<PAR_LEN;i++){
        for(int j=0;j<PAR_LEN;j++){
            for(int k=0;k<3;k++){
                for(int n=0;n<N;n++){
                    avg[i][j][k]+=each[n][i][j][k];
                }
                for(int n=0;n<N;n++){
                    sd[i][j][k]+=(each[n][i][j][k]-avg[i][j][k]/N)*(each[n][i][j][k]-avg[i][j][k]/N);
                }
            }
        }
    }
    for(int i=0;i<PAR_LEN;i++){
        for(int j=0;j<PAR_LEN;j++){
            if(argc==3) file<<i<<"\t"<<j<<"\t";
            else std::cout<<i<<"\t"<<j<<"\t";
            for(int k=0;k<3;k++){
                if(argc==3) file<<avg[i][j][k]/avg[0][0][0]<<"\t"<<std::sqrt(sd[i][j][k]*N/(N-1))/avg[0][0][0]<<((k==2)?"\n":"\t");
                else std::cout<<avg[i][j][k]/avg[0][0][0]<<"\t"<<std::sqrt(sd[i][j][k]*N/(N-1))/avg[0][0][0]<<((k==2)?"\n":"\t");
            }
        }
    }
    if(debug) std::cout<<acc*1.0/tot<<"\t"<<test_count<<std::endl;
    file.close();
    return 0;
}
