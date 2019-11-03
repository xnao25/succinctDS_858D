//
// Created by Bixuan Wang on 10/20/19.
//

#ifndef SUCCINCTDATASTRUCTURE_BIT_VECTOR_H
#define SUCCINCTDATASTRUCTURE_BIT_VECTOR_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class bit_vector {
private:
    string bits;
    vector<bool> bvec;
public:
    bit_vector();
    bit_vector(string);
    bit_vector(vector<uint64_t >);
    //bit_vector(uint64_t);
    ~bit_vector();
    string get_string();
    vector<bool> get_vec();
};


#endif //SUCCINCTDATASTRUCTURE_BIT_VECTOR_H
