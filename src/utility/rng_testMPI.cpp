#include "rng.h"
#if __has_include("mpi.h")
#   include "mpi.h"
#endif
#include <iostream>

int test(){
    int i=0;
    double x=0;
    int count=0;
#if __has_include("mpi.h")
    MPI::Init();
    int size=MPI::COMM_WORLD.Get_size();
    int rank=MPI::COMM_WORLD.Get_rank();
#endif
    RandomGenerator RNG;
    for(i=0;i<1000000;i++){
        x+=RNG.urn();
        count++;
    }
#if __has_include("mpi.h")
    std::cout<<x/count<<"\t"<<rank<<"\t"<<std::endl;
#endif
    
    int total;
    double sum;
#if __has_include("mpi.h")
    MPI::COMM_WORLD.Reduce(&x,&sum,1,MPI::DOUBLE,MPI::SUM,0);
    MPI::COMM_WORLD.Reduce(&count,&total,1,MPI::INT,MPI::SUM,0);
#else
    total=count;
    sum=x;
#endif

#if __has_include("mpi.h")
    if(rank==0) std::cout<<sum/total<<"\t"<<total<<"\t"<<std::endl;
    MPI::Finalize();
#else
    std::cout<<sum/total<<"\t"<<total<<"\t"<<std::endl;
#endif
    return 0;
}

int main(){
    test();
    return 0;
}
