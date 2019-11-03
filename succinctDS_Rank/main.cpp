#include <iostream>
#include "bit_vector.h"
#include "rank_support.h"

using namespace std;

int main(int argc, char* argv[]) {

    if(argc<4){// || argv[1]=="--h" || argv[1]=="-h"){
        cout<<"Usage:\n Get rank1:\t/path/to/SuccinctRank rank1 <bit-string> <index 0-based>\n Get rank0:\t/path/to/SuccinctRank rank0 <bit-string> <index>"<<endl;
        cout<<"Example:\n /path/to/SuccinctRank rank1 01010101 3"<<endl;
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
        cout<<"Usage:\n Get rank1:\t/path/to/SuccinctRank rank1 <bit-string> <index 0-based>\n Get rank0:\t/path/to/SuccinctRank rank0 <bit-string> <index 0-based>"<<endl;
        cout<<"Example:\n /path/to/SuccinctRank rank1 01010101 3"<<endl;
        cout<<"Please refer to readme for more information."<<endl;
        return 1;
    }else if(command!="rank1"&&command!="rank0"){
        cout<<"Error: command "<<command<<" not recognized"<<endl;
        cout<<"Usage:\n Get rank1:\t/path/to/SuccinctRank rank1 <bit-string> <index 0-based>\n Get rank0:\t/path/to/SuccinctRank rank0 <bit-string> <index 0-based>"<<endl;
        cout<<"Example:\n /path/to/SuccinctRank rank1 01010101 3"<<endl;
        cout<<"Please refer to readme for more information."<<endl;
        return 1;
    }else if(string_qualified==false){
        cout<<"Error: unqualified character in string."<<endl;
        return 1;
    }else if(index_>bitstring.size()-1){
        cout<<"Error: index provided exceeds limit of string."<<endl;
        return 1;
    }
    bit_vector the_bit_vector(bitstring);
    rank_support the_rank(the_bit_vector);
    uint64_t result=(command=="rank1")? the_rank.rank1(index_):the_rank.rank0(index_);
    cout<<"Result:\t"<<command<<" at "<<idx<<" is "<<result<<endl;

    return 0;
}