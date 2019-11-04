//
// Created by Bixuan Wang on 10/20/19.
//

#include "rank_support.h"
#include <cmath>
#include <map>
#include <string>
/*
uint64_t raw_rank(vector<bool> invector,uint64_t position){
    vector<bool> sub_invector(invector.begin(),invector.begin()+position);
    uint64_t rank=0;
    for(auto item:sub_invector){
        int x=item;
        rank+=x;
    }
    return rank;
}
*/

vector<string> bit_string_combination(uint length){
    vector<string> combinations={""};
    vector<char> bit_c={'0','1'};
    uint i=0;
    vector<string> newcomb;
    while(i<length){
        for(auto &a:combinations){
            for(auto &b:bit_c){
                string c=a+b;
                newcomb.push_back(c);
            }
        }
        combinations=newcomb;
        newcomb={};
        i++;
    }
    return combinations;
}

rank_support::rank_support() {

}

rank_support::rank_support(bit_vector& bv1) {
    bv=bv1.get_vec();//get bit_vector of bool
    uint64_t N=bv.size();//original vector size
    N_value=N;
    uint64_t S=ceil(pow(log2(N),2)/2);//value of S, the length of each superblock
    if(S==0){S=1;}
    vector<uint64_t> raw_rank(N);
    uint64_t init_rank=0;
    for(int pos=0;pos<N;pos++){
        raw_rank[pos]=init_rank;
        if(bv[pos]==1){
            init_rank++;
        }
    }
    uint64_t j=ceil(N*1.0/S);//value of j, the number of superblocks
    vector<uint64_t> Rs;//create vector for 1st layer -- of superblocks
    //cout<<"N:"<<N<<endl;
    //cout<<"S:"<<S<<endl;
    //for(auto &A:raw_rank){cout<<A<<endl;}
    //cout<<"j:"<<j<<endl;
    for(uint64_t first_layer=0;first_layer<j;first_layer++){
        //cout<<"first_layer:"<<first_layer<<endl;
        //cout<<"value:"<<raw_rank[first_layer*S]<<endl;
        Rs.push_back(raw_rank[first_layer*S]);
    }
    uint64_t b=ceil((log2(N))/2);//value of b, the length of each block
    if(b==0){b=1;}
    uint64_t k=ceil(S*1.0/b);//value of k, the number of blocks in each superblock
    //cout<<"K:"<<k<<endl;
    //cout<<"b:"<<b<<endl;
    vector<vector<uint64_t>> Rb(j);//create vector for 2nd layer -- of blocks within each superblock
    //vector<vector<vector<uint64_t>>> Rp(j);//create vector for 3rd layer
    map<string,vector<uint64_t>> Rp_map;

    vector<string> Rp_key=bit_string_combination(b);
    vector<vector<uint64_t>> Rp_Matrix;
    for(auto &comb:Rp_key){
        vector<uint64_t> Rp_value(b);
        uint64_t count_1=0;
        for(int char_i=0;char_i<b;char_i++){
            if(comb[char_i]=='1'){
                count_1++;
            }
            //cout<<count_1<<endl;
            Rp_value[char_i]=count_1;
        }
        Rp_map[comb]=Rp_value;
        Rp_Matrix.push_back(Rp_value);
    }
    for(uint64_t first_layer=0;first_layer<j;first_layer++){
        //vector<vector<uint64_t>> Rp_layer2(k);
        vector<uint64_t> block;
        for(uint64_t second_layer=0;second_layer<k;second_layer++){
            /*
            cout<<"first_layer:"<<first_layer<<endl;
            cout<<"second_layer:"<<second_layer<<endl;
            cout<<"value:"<<raw_rank[second_layer*b+first_layer*S]-raw_rank[first_layer*S]<<endl;
            cout<<"position:"<<second_layer*b+first_layer*S<<endl;
             */
            if(second_layer*b+first_layer*S>=N){
                break;
            }
            block.push_back(raw_rank[second_layer*b+first_layer*S]-raw_rank[first_layer*S]);//raw_rank(for_this_superblock,second_layer*b);
            /*
            string sub_Rp="";
            uint64_t real_len=0;
            for(uint64_t sub_p=first_layer*S+second_layer*b;sub_p<first_layer*S+(second_layer+1)*b;sub_p++){
                char add_char;
                //cout<<"3rdidx:"<<sub_p<<endl;
                //cout<<"edge:"<<first_layer*S<<endl;
                //cout<<sub_p<<endl;
                if(sub_p>N-1){
                    add_char='0';
                }else{
                    add_char=(bv[sub_p]==1)? '1':'0';
                    real_len++;
                }

                sub_Rp+=add_char;
            }
            //cout<<sub_Rp<<endl;
            vector<uint64_t> realvec(Rp_map[sub_Rp].begin(),Rp_map[sub_Rp].begin()+real_len);
            //for(auto&A:realvec){cout<<A;}
            //cout<<endl;
            Rp_layer2[second_layer]=realvec;
            */
        }
        Rb[first_layer]=block;
        //Rp[first_layer]=Rp_layer2;
    }
    Rs_vec=Rs;
    Rb_vec=Rb;
    //Rp_vec=Rp;
    Rp_vec_matrix=Rp_map;
    S_value=S;
    B_value=b;
    Rp_matrix=Rp_Matrix;
}

rank_support::~rank_support() {

}

uint64_t rank_support::rank0(uint64_t i) {
    if(i>N_value-1){return -1;}
    return i+1-rank1(i);
}

uint64_t rank_support::rank1(uint64_t i) {
    if(i>N_value-1){return -1;}
    uint64_t j=i;
    uint64_t first_layer=floor(j/S_value);
    uint64_t first_value=Rs_vec[first_layer];
    uint64_t second_layer=floor(j%S_value/B_value);
    uint64_t second_value=Rb_vec[first_layer][second_layer];
    uint64_t third_layer=j%S_value%B_value;
    string sub_str="";
    for(int pos=first_layer*S_value+second_layer*B_value;pos<=j;pos++){
        char sub_add=(bv[pos]==0)? '0':'1';
        sub_str=sub_str+sub_add;
    }
    for(int add_n=0;add_n<B_value-third_layer-1;add_n++){
        sub_str=sub_str+'0';
    }
    uint64_t third_idx=stoi(sub_str, nullptr, 2);
    uint64_t third_value=Rp_matrix[third_idx][third_layer];//Rp_vec_matrix[sub_str][third_layer];//Rp_vec[first_layer][second_layer][third_layer];
    return first_value+second_value+third_value;
}

uint64_t rank_support::overhead() {
    uint64_t size=0;
    uint64_t size_S=0;
    uint64_t size_B=0;
    uint64_t size_P=0;
    for(auto &a:Rs_vec){
        size_S=(a>1)? size_S+floor(log2(a))+1:size_S+1;
    }
    for(auto &b:Rb_vec){
        for(auto &c:b){
            size_B=(c>1)? size_B+floor(log2(c))+1:size_B+1;
        }
    }

    for(auto &a:Rp_matrix){
        for(auto &b:a){
            size_P=(b>1)? size_P+floor(log2(b))+1:size_P+1;
        }
    }
    size=size_B+size_S+size_P;
    return size;
}

uint64_t rank_support::get_S_value() {
    return S_value;
}

uint64_t rank_support::get_B_value() {
    return B_value;
}

uint64_t rank_support::get_N_value() {
    return N_value;
}

vector<uint64_t> rank_support::get_Rs_vec() {
    return Rs_vec;
}

vector<vector<uint64_t>> rank_support::get_Rb_vec() {
    return Rb_vec;
}

vector<vector<uint64_t>> rank_support::get_Rp_matrix() {
    return Rp_matrix;
}