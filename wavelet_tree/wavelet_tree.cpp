//
// Created by Bixuan Wang on 10/22/19.
//

#include "wavelet_tree.h"
#include "rank_support.h"
#include "select_support.h"
#include <map>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <string>

vector<string> split(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

string bits(int x,int log_sigma){
    //unsigned int bits_num=log2(sigma);
    bitset<sizeof(x) * CHAR_BIT> bs(x);
    vector<unsigned int> outvec;
    string binarys=bs.to_string();
    //cout<<binarys<<endl;
    //cout<<binarys.size()-bits_num<<endl;
    //cout<<bits_num<<endl;
    string subinary=binarys.substr(binarys.size()-log_sigma,log_sigma);
    //cout<<subinary<<endl;
    /*
    for(auto &item:subinary){
        outvec.push_back((int)item);
    }
    return outvec;*/
    return subinary;
}



wavelet_tree::wavelet_tree() {

}

wavelet_tree::wavelet_tree(string s) {
    text=s;
}

wavelet_tree::wavelet_tree(ifstream &treein) {
    vector<char> elements;
    vector<uint64_t> int_elements;
    map<char,uint64_t> elements_to_int;
    map<uint64_t,char> int_to_element;
    vector<vector<uint64_t >> BV;
    map<int,map<string,int>> SPos_start;
    uint64_t log_sigma;
    string lineread;
    string part="";
    int pos_layer=1;
    while(getline(treein,lineread)){
        if(lineread[0]=='#'){
            part=lineread;
            continue;
        }
        if(lineread==""){
            part="";
            continue;
        }
        /*
        if(part=="#Original String:"){
            text=lineread;
            continue;
        }
         */
        if(part=="#Elements & Corresponding integers:"){
            vector<string> pairs=split(lineread,'\t');
            for(auto &substr:pairs){
                vector<string> char_int=split(substr,':');
                char thechar=char_int[0][0];
                uint64_t theint=stoi(char_int[1]);
                elements.push_back(thechar);
                int_elements.push_back(theint);
                elements_to_int[thechar]=theint;
                int_to_element[theint]=thechar;
            }
            log_sigma=ceil(log2(int_elements.size()));
        }
        if(part=="#Wavelet Tree Structure:"){
            vector<uint64_t> treelayer;
            vector<string> ints=split(lineread,'\t');
            for(auto &s:ints){
                treelayer.push_back(stoi(s));
            }
            BV.push_back(treelayer);
        }
        if(part=="#Wavelet Tree Position:"){
            map<string,int> subpos;
            vector<string> pairs=split(lineread,'\t');
            for(auto &p:pairs){
                vector<string> key_value=split(p,':');
                string thestr=key_value[0];
                int theint=stoi(key_value[1]);
                subpos[thestr]=theint;
            }
            SPos_start[pos_layer]=subpos;
            pos_layer++;
        }
    }

    map<uint64_t,string> bits_value;
    for(auto &character:elements_to_int){
        uint64_t t=character.second;//elements_to_int[character];
        //Text.push_back(t);
        string bits_of_t=bits(t,log_sigma);
        bits_value[t]=bits_of_t;
    }


    tree_matrix=BV;
    //tree_character_matrix=CV;
    tree_character_pos_map=SPos_start;
    character_bits_value=bits_value;
    text_elements_to_int=elements_to_int;
    text_int_to_elements=int_to_element;
    tree_layer=log_sigma;
    text_elements=elements;

}

wavelet_tree::~wavelet_tree() {

}

void wavelet_tree::tree_build() {
    vector<char> elements;
    for(auto &character:text){
        if(find(elements.begin(),elements.end(),character)==elements.end()){
            elements.push_back(character);
        }
    }
    sort(elements.begin(),elements.end());
    vector<uint64_t> int_elements;//sigma
    for(int i=0;i<elements.size();i++){int_elements.push_back(i);}
    map<char,uint64_t> elements_to_int;
    map<uint64_t,char> int_to_element;
    for(int i=0;i<elements.size();i++){
        elements_to_int[elements[i]]=i;
        int_to_element[i]=elements[i];
    }
    int log_sigma=ceil(log2(int_elements.size()));
    vector<uint64_t> Text;//T
    map<uint64_t,string> bits_value;//store the value of bits(x),bits(k,x)=bits_value[x][k],prefix(k,x)=bits_value[x][0~k-1]
    map<string,uint64_t> Hist;//Hist
    for(auto &character:text){
        uint64_t t=elements_to_int[character];
        Text.push_back(t);
        string bits_of_t=bits(t,log_sigma);
        bits_value[t]=bits_of_t;
    }
    //pcWT?
    vector<vector<uint64_t >> BV(log_sigma);
    vector<vector<uint64_t>> CV(log_sigma);//characters layers
    for(int i=0;i<log_sigma;i++){
        vector<uint64_t> initvec(Text.size());
        vector<uint64_t> initvecc(Text.size());
        BV[i]=initvec;
        CV[i]=initvecc;
    }
    uint64_t size_of_text=Text.size();//n
    for(int i=0;i<size_of_text;i++){
        Hist[bits_value[Text[i]]]++;
        BV[0][i]=(int)bits_value[Text[i]][0]-48;
        CV[0][i]=Text[i];
    }
    map<int,map<string,int>> SPos;
    map<int,map<string,int>> SPos_start;
    for(int l=log_sigma-1;l>0;l--){
        for(int i=0;i<pow(2,l);i++){
            Hist[bits(i,l)]=Hist[bits(i,l)+'1']+Hist[bits(i,l)+'0'];
        }
        map<string,int> posl;
        posl[bits(0,l)]=0;
        SPos[l]=posl;
        SPos_start[l]=posl;
        for(int i=1;i<pow(2,l);i++){
            SPos[l][bits(i,l)]=SPos[l][bits(i-1,l)]+Hist[bits(i-1,l)];
            SPos_start[l][bits(i,l)]=SPos_start[l][bits(i-1,l)]+Hist[bits(i-1,l)];
        }
        for(int i=0;i<size_of_text;i++){
            int pos=SPos[l][bits_value[Text[i]].substr(0,l)]++;
            BV[l][pos]=(int)bits_value[Text[i]][l]-48;
            CV[l][pos]=Text[i];
        }
    }

    tree_matrix=BV;
    //tree_character_matrix=CV;
    tree_character_pos_map=SPos_start;
    character_bits_value=bits_value;
    text_elements_to_int=elements_to_int;
    text_int_to_elements=int_to_element;
    tree_layer=log_sigma;
    text_elements=elements;
    return;
}

void wavelet_tree::tree_build_save(ofstream &treefile) {
    //line1&2: original string
    //removed original string
    //treefile<<"#Original String:\n"<<text<<"\n\n";
    //line3&4&5: elements and corresponding ints
    treefile<<"#Elements & Corresponding integers:\n";
    for(auto &e:text_elements){
        treefile<<e<<":"<<text_elements_to_int[e]<<"\t";
    }
    treefile<<"\n";
    treefile<<"\n";
    //line 6~log(sigma)-1+6: tree matrix
    treefile<<"#Wavelet Tree Structure:\n";
    for(int i=0;i<tree_layer;i++){
        for(int j=0;j<tree_matrix[0].size();j++){
            char the_char=(tree_matrix[i][j]==0)? '0':'1';
            treefile<<the_char<<"\t";
        }
        treefile<<"\n";
    }
    treefile<<"\n";
    //line ~~~: position matrix
    treefile<<"#Wavelet Tree Position:\n";
    for(int i=1;i<tree_layer;i++){
        for(auto &el:tree_character_pos_map[i]){
            treefile<<el.first<<":"<<el.second<<"\t";
        }
        treefile<<"\n";
    }
    return;
}

char wavelet_tree::tree_access(unsigned int idx_access) {
    if(idx_access>=tree_matrix[0].size()){
        char nonchar;
        return nonchar;
    }
    uint64_t tree_idx;//=idx_access;
    uint64_t rank_count;
    vector<uint64_t> the_vector;//=tree_matrix[0];
    uint64_t the_int;//=the_vector[tree_idx];
    string bit_char="";
    for(int i=0;i<tree_layer;i++){
        if(i==0){
            the_vector=tree_matrix[0];
            tree_idx=idx_access;
            the_int=the_vector[tree_idx];
            bit_vector layer_vector(the_vector);
            rank_support layer_succinct(layer_vector);
            rank_count=(the_int==1)? layer_succinct.rank1(tree_idx):layer_succinct.rank0(tree_idx);
            tree_idx=rank_count-1;
            bit_char=(the_int==1)? bit_char+'1':bit_char+'0';
        }else{
            int start_site=tree_character_pos_map[i][bit_char];
            if(bit_char!=string(i,'1')){
                int end_site=tree_character_pos_map[i][bits(stoi(bit_char,nullptr,2)+1,i)];
                vector<uint64_t> newvec(tree_matrix[i].begin()+start_site,tree_matrix[i].begin()+end_site);
                the_vector=newvec;
            }else{
                vector<uint64_t> newvec(tree_matrix[i].begin()+start_site,tree_matrix[i].end());
                the_vector=newvec;
            }
            the_int=the_vector[tree_idx];
            bit_vector layer_vector(the_vector);
            rank_support layer_succinct(layer_vector);
            rank_count=(the_int==1)? layer_succinct.rank1(tree_idx):layer_succinct.rank0(tree_idx);
            tree_idx=rank_count-1;
            bit_char=(the_int==1)? bit_char+'1':bit_char+'0';
        }
    }
    uint64_t element_int=stoi(bit_char, nullptr,2);
    return text_int_to_elements[element_int];
}

vector<char> wavelet_tree::tree_access_save(ifstream &accessfile) {
    vector<char> output_access;
    string readline;
    while(getline(accessfile,readline)){
        int idx=stoi(readline);
        output_access.push_back(tree_access(idx));
    }
    return output_access;
}

uint64_t wavelet_tree::tree_rank(char c, uint64_t idx) {
    string c_bits_value=character_bits_value[text_elements_to_int[c]];
    uint64_t tree_idx=idx;
    uint64_t rank_count;
    for(int i=0;i<tree_layer;i++){
        uint64_t bits_current=(int)c_bits_value[i]-48;
        vector<uint64_t> init_vector;
        if(i==0){
            init_vector=tree_matrix[0];
        }else{
            string bits_prefix=c_bits_value.substr(0,i);
            int start_site=tree_character_pos_map[i][bits_prefix];
            if(bits_prefix!=string(i,'1')){
                int end_site=tree_character_pos_map[i][bits(stoi(bits_prefix,nullptr,2)+1,i)];
                vector<uint64_t> newvec(tree_matrix[i].begin()+start_site,tree_matrix[i].begin()+end_site);
                init_vector=newvec;
            }else{
                vector<uint64_t> newvec(tree_matrix[i].begin()+start_site,tree_matrix[i].end());
                init_vector=newvec;
            }
        }
        bit_vector layer_vector(init_vector);
        rank_support layer_succinct(layer_vector);
        rank_count=(bits_current==1) ? layer_succinct.rank1(tree_idx):layer_succinct.rank0(tree_idx);
        bool current=bits_current==1;
        if((find(init_vector.begin(),init_vector.end(),1)==init_vector.end())||(find(init_vector.begin(),init_vector.end(),0)==init_vector.end())){
            break;
        }
        if(rank_count==0){return 0;}
        tree_idx=rank_count-1;
    }
    return rank_count;
}

vector<int64_t> wavelet_tree::tree_rank_save(ifstream &rankfile) {
    vector<int64_t> output_ranks;
    string readline;
    while(getline(rankfile,readline)){
        vector<string> info=split(readline,'\t');
        char the_char=info[0][0];
        uint64_t the_idx=stoi(info[1]);
        if(the_idx>=tree_matrix[0].size()||find(text_elements.begin(),text_elements.end(),the_char)==text_elements.end()){
            output_ranks.push_back(-1);
        }else{
            output_ranks.push_back(tree_rank(the_char,the_idx));
        }
    }
    return output_ranks;
}

uint64_t wavelet_tree::tree_select(char c, uint64_t occr) {
    string c_bits_value=character_bits_value[text_elements_to_int[c]];
    uint64_t tree_occr=occr;
    uint64_t occr_count;
    for(int i=tree_layer-1;i>=0;i--){
        uint64_t bits_current=(int)c_bits_value[i]-48;
        vector<uint64_t> init_vector;
        if(i!=0){
            string bits_prefix=c_bits_value.substr(0,i);
            int start_site=tree_character_pos_map[i][bits_prefix];
            if(bits_prefix!=string(i,'1')){
                int end_site=tree_character_pos_map[i][bits(stoi(bits_prefix,nullptr,2)+1,i)];
                vector<uint64_t> newvec(tree_matrix[i].begin()+start_site,tree_matrix[i].begin()+end_site);
                init_vector=newvec;
            }else{
                vector<uint64_t> newvec(tree_matrix[i].begin()+start_site,tree_matrix[i].end());
                init_vector=newvec;
            }
        }else{
            init_vector=tree_matrix[0];
        }

        bit_vector layer_vector(init_vector);
        rank_support layer_succinct(layer_vector);
        select_support layer_select(layer_succinct);
        uint64_t select_num=(bits_current==1) ? layer_select.select1(tree_occr):layer_select.select0(tree_occr);
        tree_occr=select_num+1;
    }
    return tree_occr-1;
}

vector<int64_t> wavelet_tree::tree_select_save(ifstream &selectfile) {
    vector<int64_t> output_selects;
    string readline;
    while(getline(selectfile,readline)){
        vector<string> info=split(readline,'\t');
        char the_char=info[0][0];
        uint64_t the_slt=stoi(info[1]);
        if(find(text_elements.begin(),text_elements.end(),the_char)==text_elements.end()||the_slt>tree_rank(the_char,tree_matrix[0].size()-1)){
            output_selects.push_back(-1);
        }else{
            output_selects.push_back(tree_select(the_char,the_slt));
        }
    }
    return output_selects;
}

vector<uint64_t> wavelet_tree::get_text_size() {
    vector<uint64_t> sizes={text_elements.size(),tree_matrix[0].size()};
    return sizes;
}