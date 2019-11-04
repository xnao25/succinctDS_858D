//
// Created by Bixuan Wang on 10/21/19.
//

#ifndef SUCCINCTDATASTRUCTURE_SELECT_SUPPORT_H
#define SUCCINCTDATASTRUCTURE_SELECT_SUPPORT_H

#include <iostream>
#include "rank_support.h"

class select_support {
private:
    rank_support r_ref;
    uint64_t r_N_value;
    /*
    uint64_t r_S_value;
    vector<uint64_t> r_Rs_vec;
    uint64_t size_Rs;
    uint64_t r_B_value;
    vector<vector<uint64_t >> r_Rb_vec;
    vector<vector<vector<uint64_t>>> r_Rp_vec;

     */
public:
    select_support();
    select_support(rank_support &r);
    ~select_support();
    uint64_t select1(uint64_t i);
    uint64_t select0(uint64_t i);
    uint64_t overhead();
};


#endif //SUCCINCTDATASTRUCTURE_SELECT_SUPPORT_H
