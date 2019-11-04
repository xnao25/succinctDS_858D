//
// Created by Bixuan Wang on 10/20/19.
//

#include "bit_vector.h"
#include <sstream>

bit_vector::bit_vector() {
    bits="";
    bvec={};
}

bit_vector::bit_vector(string input_bits) {
    bits=input_bits;
    for(auto &i:bits){
        bool bl=(i=='1') ? 1:0;
        bvec.push_back(bl);
    }
}

bit_vector::bit_vector(vector<uint64_t> invec) {
    for(auto &i:invec){
        bool bl=(i==1)? 1:0;
        bvec.push_back(bl);
    }
}

bit_vector::~bit_vector() {

}

string bit_vector::get_string() {
    return bits;
}

vector<bool> bit_vector::get_vec() {
    return bvec;
}