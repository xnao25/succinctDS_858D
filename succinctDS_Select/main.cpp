#include <iostream>
#include "bit_vector.h"
#include "rank_support.h"
#include "select_support.h"

using namespace std;

int main(int argc, char* argv[]) {

    if(argc<4){// || argv[1]=="--h" || argv[1]=="-h"){
        cout<<"Usage:\n Get select1:\t/path/to/SuccinctSelect select1 <bit-string> <occurance>\n Get select0:\t/path/to/SuccinctSelect select0 <bit-string> <occurance>"<<endl;
        cout<<"Example:\n /path/to/SuccinctSelect select1 01010101 3"<<endl;
        cout<<"Please refer to readme for more information."<<endl;
        return 1;
    }
    string command(argv[1]);
    string bitstring(argv[2]);
    string idx(argv[3]);
    uint64_t index_=stoi(idx);
    bool string_qualified=true;
    for(int i=0;i<bitstring.size();i++){
        if(bitstring[i]!='1'&&bitstring[i]!='0'){
            string_qualified=false;
            break;
        }
    }
    if(command=="--h"||command=="-h"){
        cout<<"Usage:\n Get select1:\t/path/to/SuccinctSelect select1 <bit-string> <occurance>\n Get select0:\t/path/to/SuccinctSelect select0 <bit-string> <occurance>"<<endl;
        cout<<"Example:\n /path/to/SuccinctSelect select1 01010101 3"<<endl;
        cout<<"Please refer to readme for more information."<<endl;
        return 1;
    }else if(command!="select1"&&command!="select0"){
        cout<<"Error: command "<<command<<" not recognized"<<endl;
        cout<<"Usage:\n Get select1:\t/path/to/SuccinctSelect select1 <bit-string> <occurance>\n Get select0:\t/path/to/SuccinctSelect select0 <bit-string> <occurance>"<<endl;
        cout<<"Example:\n /path/to/SuccinctSelect select1 01010101 3"<<endl;
        cout<<"Please refer to readme for more information."<<endl;
        return 1;
    }else if(string_qualified==false){
        cout<<"Error: unqualified character in string."<<endl;
        return 1;
    }
    bit_vector the_bit_vector(bitstring);
    rank_support the_rank(the_bit_vector);
    select_support the_select(the_rank);
    uint64_t max_select=(command=="select1")? the_rank.rank1(bitstring.size()-1):the_rank.rank0(bitstring.size()-1);
    if(index_>max_select){
        cout<<"Error: occurrence provided exceed the real occurrence of bit existed in your string."<<endl;
        return 1;
    }
    uint64_t result=(command=="select1")? the_select.select1(index_):the_select.select0(index_);
    cout<<"Result:\t"<<command<<" at "<<idx<<" is "<<result<<endl;

    return 0;
}