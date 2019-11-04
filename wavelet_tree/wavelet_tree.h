//
// Created by Bixuan Wang on 10/22/19.
//

#ifndef WAVELETTREE_WAVELET_TREE_H
#define WAVELETTREE_WAVELET_TREE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
using namespace std;

vector<string> split(const string&, const char&);

string bits(int,int);

//string bits(int,int,int);

class wavelet_tree {
private:
    string text;
    vector<char> text_elements;
    vector<vector<uint64_t>> tree_matrix;
    vector<vector<uint64_t>> tree_character_matrix;
    map<int,map<string,int>> tree_character_pos_map;
    map<uint64_t,string> character_bits_value;
    map<char,uint64_t> text_elements_to_int;
    map<uint64_t,char> text_int_to_elements;
    uint64_t tree_layer;
public:
    wavelet_tree();
    wavelet_tree(string s);
    wavelet_tree(ifstream &treein);
    ~wavelet_tree();
    void tree_build();
    void tree_build_save(ofstream &treefile);
    char tree_access(unsigned int idx_access);
    vector<char> tree_access_save(ifstream &accessfile);
    uint64_t tree_rank(char c,uint64_t idx);
    vector<int64_t> tree_rank_save(ifstream &rankfile);
    uint64_t tree_select(char c,uint64_t occr);
    vector<int64_t> tree_select_save(ifstream &selectfile);
    vector<uint64_t> get_text_size();
};


#endif //WAVELETTREE_WAVELET_TREE_H
