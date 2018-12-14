#ifndef _GENERAL_PURPOSE_LATTICE_
#define _GENERAL_PURPOSE_LATTICE_

//
// general purpose lattice head
// dealing with conversion between position parameters and index.
// position parameters include d dimension index {x_d} 
//     and sublattice x_sub
// index is where the position stored in the 1-d list
//
// does not deal with specific content within the list
//

#include <vector>

class Lattice{
private:
    int dimension;
    std::vector<int> length;
    int subnum;
    int N;
public:
    //initializer
    void initialize(std::vector<int> l,int sub);
    Lattice(std::vector<int> l,int sub);
    Lattice(int dim,int sub,int L);
    //converter between index and position
    std::vector<int> i2p(int n);//index to position,return d+1 vector
    int p2i(std::vector<int> p);//positon to index,return index
    //get quantities
    inline int get_d(){return dimension;}
    inline int get_L(int i){return length[i];}
    inline int get_sub(){return subnum;}
    inline int get_N(){return N;}
};

class Square_Lattice:public Lattice{
public:
    Square_Lattice(int dim,int L);
};

class Square_2D:public Square_Lattice{
    private:
        std::vector<std::vector<int>> nnchart;
        std::vector<std::vector<int>> nnnchart;
    public:
        Square_2D(int L);
        std::vector<int> nn(int);//return nearest neightbor index
        std::vector<int> nnn(int);//return nearest neightbor index
};

class Triangle_J1J2:public Lattice{
private:
    std::vector<std::vector<int>> nnchart;
    std::vector<std::vector<int>> nnnchart;
public:
    Triangle_J1J2(int L);
    std::vector<int> nn(int);
    std::vector<int> nnn(int);

};
#endif
