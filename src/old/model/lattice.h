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

enum Lattice_Type {
    //pre-defined lattice type
    _KAGOMI_,
    _SQUARE_,
    _TRIANGLE_,
    _CUSTOM_
};

class Lattice{
private:
    Lattice_Type type;
    int dimension;
    std::vector<int> length;
    int subnum;
    int N;
public:
    //initializer
    void initialize(std::vector<int> l,int sub);
    Lattice(std::vector<int> l,int sub);
    Lattice(Lattice_Type t,std::vector<int> l);
    Lattice(Lattice_Type t,int L);
    //converter between index and position
    std::vector<int> i2p(int n);//index to position,return d+1 vector
    int p2i(std::vector<int> p);//positon to index,return index
    //get quantities
    Lattice_Type get_type();
    inline int get_d(){return dimension;}
    inline int get_L(int i){return length[i];}
    inline int get_sub(){return subnum;}
    inline int get_N(){return N;}
};



#endif
