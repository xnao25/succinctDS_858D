//
// Created by Bixuan Wang on 10/21/19.
//

#include <iostream>
#include "select_support.h"
#include <cmath>

select_support::select_support() {

}

select_support::select_support(rank_support &r) {
    r_ref=r;
    r_N_value=r.get_N_value();
}

select_support::~select_support() {

}

uint64_t select_support::select0(uint64_t i) {
    if(i>r_ref.rank0(r_N_value-1)){return -1;}
    uint64_t upper=r_N_value-1;
    uint64_t lower=0;
    uint64_t realpos=ceil((upper+lower)/2);
    uint64_t realrank=r_ref.rank0(realpos);
    uint64_t realrank_left=(realpos!=0) ? r_ref.rank0(realpos-1):-1;

    while((realrank!=i)||((realrank==i)&&(realrank==realrank_left))){

        if(realrank>i){
            upper=realpos;
        }else if(realrank<i){
            lower=realpos;
            if(lower==r_N_value-2){
                realpos=r_N_value-1;
                break;
            }
        }else{
            upper=realpos;
            if(upper==1){
                realpos=0;
                break;
            }
        }

        realpos=ceil((upper+lower)/2);
        realrank=r_ref.rank0(realpos);
        realrank_left=(realpos!=0) ? r_ref.rank0(realpos-1):-1;
    }
    return realpos;
}

uint64_t select_support::select1(uint64_t i) {
    if(i>r_ref.rank1(r_N_value-1)){return -1;}
    uint64_t upper=r_N_value-1;
    uint64_t lower=0;
    uint64_t realpos=ceil((upper+lower)/2);
    uint64_t realrank=r_ref.rank1(realpos);
    uint64_t realrank_left=(realpos!=0)? r_ref.rank1(realpos-1):-1;
    while((realrank!=i)||((realrank==i)&&(realrank==realrank_left))){
        if(realrank>i){
            upper=realpos;
        }else if(realrank<i){
            lower=realpos;
            if(lower==r_N_value-2){
                realpos=r_N_value-1;
                break;
            }
        }else{
            upper=realpos;
            if(upper==1){
                realpos=0;
                break;
            }
        }
        realpos=ceil((upper+lower)/2);
        realrank=r_ref.rank1(realpos);
        realrank_left=(realpos!=0)? r_ref.rank1(realpos-1):-1;
    }
    return realpos;
}

uint64_t select_support::overhead() {
    uint64_t size=0;
    uint64_t size_S=0;
    uint64_t size_B=0;
    uint64_t size_P=0;
    for(auto &a:r_ref.get_Rs_vec()){
        size_S=(a>1)? size_S+floor(log2(a))+1:size_S+1;
    }
    for(auto &b:r_ref.get_Rb_vec()){
        for(auto &c:b){
            size_B=(c>1)? size_B+floor(log2(c))+1:size_B+1;
        }
    }

    for(auto &a:r_ref.get_Rp_matrix()){
        for(auto &b:a){
            size_P=(b>1)? size_P+floor(log2(b))+1:size_P+1;
        }
    }
    size=size_B+size_S+size_P;
    return size;
}
