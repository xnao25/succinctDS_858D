//
// Created by Bixuan Wang on 10/20/19.
//

#ifndef SUCCINCTDATASTRUCTURE_RANK_SUPPORT_H
#define SUCCINCTDATASTRUCTURE_RANK_SUPPORT_H

#include <iostream>
#include <vector>
#include "bit_vector.h"
#include <map>

using namespace std;

//uint64_t raw_rank(vector<bool>,uint64_t);
vector<string> bit_string_combination(uint);

class rank_support {
private:
    vector<bool> bv;
    vector<uint64_t> Rs_vec;
    vector<vector<uint64_t>> Rb_vec;
    //vector<vector<vector<uint64_t>>> Rp_vec;
    vector<vector<uint64_t>> Rp_matrix;
    map<string,vector<uint64_t>> Rp_vec_matrix;
    uint64_t S_value;
    uint64_t B_value;
    //uint64_t P_value;
    uint64_t N_value;
public:
    rank_support();
    rank_support(bit_vector&);
    ~rank_support();
    uint64_t rank1(uint64_t i);
    uint64_t rank0(uint64_t i);
    uint64_t overhead();

    uint64_t get_S_value();
    uint64_t get_B_value();
    uint64_t get_N_value();
    vector<uint64_t> get_Rs_vec();
    vector<vector<uint64_t>> get_Rb_vec();
    vector<vector<uint64_t>> get_Rp_matrix();
};


#endif //SUCCINCTDATASTRUCTURE_RANK_SUPPORT_H
