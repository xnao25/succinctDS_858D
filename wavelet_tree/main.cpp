#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include "bit_vector.h"
#include "rank_support.h"
#include "select_support.h"
#include "wavelet_tree.h"

#include <time.h>
#include <random>

using namespace std;
using namespace chrono;

/* test performance
string gen_random2( const int len) {
    string tt="";
    string alls="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string substring=alls.substr(0,len);
    for (int i = 0; i < 10000; ++i) {
        tt=tt+ substring[rand() % (substring.size() - 1)];
    }

    tt[len] = 0;
    return tt;
}

string gen_random( const int len) {
    string tt="";
    static const char alphanum[] ="0123456789";

    for (int i = 0; i < len; ++i) {
        tt=tt+ alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    tt[len] = 0;
    return tt;
}

string gen_random3( const int len) {
    string tt="";
    static const char alphanum[] ="01";

    for (int i = 0; i < len; ++i) {
        tt=tt+ alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    tt[len] = 0;
    return tt;
}
*/

int main(int argc, char* argv[]) {
    /* test bit-vector rank and select performance
    ofstream outfile;
    outfile.open("tree_bitvec2.txt");
    outfile<<"length,rank_time,select_time,overhead\n";
    //vector<string> strings={};
    //int count=1;
    for(int i=0;i<300;i++) {
        //cout << "Round:" << i << endl;
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<> distr(10, 100000);
        uint64_t theint=distr(eng);
        string thestring=gen_random3(theint);

        bit_vector testvector(thestring);

        //time_t time1;
        //time_t time2;
        rank_support testsupport(testvector);
        //time(&time1);
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        uint64_t testout1 = testsupport.rank1(thestring.size()/4);
        //time(&time2);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> seconds = duration_cast<duration<double>>(t2 - t1);
        //double seconds=difftime(time2,time1);
        //cout << "answer:" << testout1 << endl;
        //cout << "time-rank:" << seconds.count() << endl;
        //cout << "size-rank:" << testsupport.overhead() << endl;

        select_support testselect(testsupport);
        //time_t time3;
        //time_t time4;
        //time(&time3);
        high_resolution_clock::time_point t3 = high_resolution_clock::now();
        uint64_t testout2 = testselect.select1(thestring.size()/4);
        //time(&time4);
        high_resolution_clock::time_point t4 = high_resolution_clock::now();
        //double seconds2=difftime(time4,time3);
        duration<double> seconds2 = duration_cast<duration<double>>(t4 - t3);
        //cout << "answer:" << testout2 << endl;
        //cout << "time-select:" << seconds2.count() << endl;
        //cout << "size-select:" << testselect.overhead() << endl;
        outfile<<thestring.size()<<","<<seconds.count()<<","<<seconds2.count()<<","<<testsupport.overhead()<<endl;
        //cout<<"--------------"<<endl;
    }
    */

    if(argc<4){
        cout<<"WVLTREE is a program that can build a wavelet tree based on a given string and perform rank and select calculations."<<endl;
        cout<<"Usage:"<<endl;
        cout<<"\t/path/to/WVLTREE build <input_string> <output_tree_file>"<<endl;
        cout<<"\t\t- Build a wavelet tree."<<endl;
        cout<<"\t\t- Input: <input_string> A string."<<endl;
        cout<<"\t\t- Output: <output_tree_file> A text file containing the structure of the wavelet tree built."<<endl;
        cout<<endl;
        cout<<"\t/path/to/WVLTREE access <input_tree_file> <access indices>"<<endl;
        cout<<"\t\t- Get the character(s) at the given index(es)."<<endl;
        cout<<"\t\t- Input: <input_tree_file> A text file containing the structure of the wavelet tree. It is usually the output of the command build."<<endl;
        cout<<"\t\t- Input: <access indices> A text file containing a \"\\n\"-separated list of indices (0-based) to access."<<endl;
        cout<<endl;
        cout<<"\t/path/to/WVLTREE rank <input_tree_files> <access indices>"<<endl;
        cout<<"\t\t- Get the rank(s) of the character(s) provided."<<endl;
        cout<<"\t\t- Input: <input_tree_file> A text file containing the structure of the wavelet tree."<<endl;
        cout<<"\t\t- Input: <access indices> A text file containing a \"\\n\"-separated list of indices to access. The format of each line should be <c>\\t<i>, where <c> is the character and <i> is the 0-based index."<<endl;
        cout<<endl;
        cout<<"\t/path/to/WVLTREE select <input_tree_files> <access indices>"<<endl;
        cout<<"\t\t- Get the select(s) of the character(s) at the given index(es)."<<endl;
        cout<<"\t\t- Input: <input_tree_file> A text file containing the structure of the wavelet tree."<<endl;
        cout<<"\t\t- Input: <access indices> A text file containing a \"\\n\"-separated list of indices to access. The format of each line should be <c>\\t<i>, where <c> is the character and <i> is the 0-based index."<<endl;
        return 0;

    }

    string command(argv[1]);

    vector<string> command_list={"build","access","rank","select","--h"};
    if(find(command_list.begin(),command_list.end(),command)==command_list.end()){
        cout<<"Error: Unrecognized command: "<<command<<"\nPlease get more information by using --h"<<endl;
    }
    if(command=="--h"){
        cout<<"WVLTREE is a program that can build a wavelet tree based on a given string and perform rank and select calculations."<<endl;
        cout<<"Usage:"<<endl;
        cout<<"\t/path/to/WVLTREE build <input_string> <output_tree_file>"<<endl;
        cout<<"\t\t- Build a wavelet tree."<<endl;
        cout<<"\t\t- Input: <input_string> A string."<<endl;
        cout<<"\t\t- Output: <output_tree_file> A text file containing the structure of the wavelet tree built."<<endl;
        cout<<endl;
        cout<<"\t/path/to/WVLTREE access <input_tree_file> <access indices>"<<endl;
        cout<<"\t\t- Get the character(s) at the given index(es)."<<endl;
        cout<<"\t\t- Input: <input_tree_file> A text file containing the structure of the wavelet tree. It is usually the output of the command build."<<endl;
        cout<<"\t\t- Input: <access indices> A text file containing a \"\\n\"-separated list of indices (0-based) to access."<<endl;
        cout<<endl;
        cout<<"\t/path/to/WVLTREE rank <input_tree_files> <access indices>"<<endl;
        cout<<"\t\t- Get the rank(s) of the character(s) provided."<<endl;
        cout<<"\t\t- Input: <input_tree_file> A text file containing the structure of the wavelet tree."<<endl;
        cout<<"\t\t- Input: <access indices> A text file containing a \"\\n\"-separated list of indices to access. The format of each line should be <c>\\t<i>, where <c> is the character and <i> is the 0-based index."<<endl;
        cout<<endl;
        cout<<"\t/path/to/WVLTREE select <input_tree_files> <access indices>"<<endl;
        cout<<"\t\t- Get the select(s) of the character(s) at the given index(es)."<<endl;
        cout<<"\t\t- Input: <input_tree_file> A text file containing the structure of the wavelet tree."<<endl;
        cout<<"\t\t- Input: <access indices> A text file containing a \"\\n\"-separated list of indices to access. The format of each line should be <c>\\t<i>, where <c> is the character and <i> is the 0-based index."<<endl;
        return 0;
    }

    if(command=="build"){
        ofstream outfile;
        outfile.open(argv[3]);
        string input_string(argv[2]);

        wavelet_tree wt(input_string);
        wt.tree_build();
        wt.tree_build_save(outfile);
        vector<uint64_t> outsize=wt.get_text_size();
        cout<<"Messages: "<<endl;
        cout<<"Your wavelet tree is built, please see more information in your output file."<<endl;
        cout<<"There are "<<outsize[0]<<" unique characters in your string."<<endl;
        cout<<"The total number of characters in your string is "<<outsize[1]<<"."<<endl;
    }else if(command=="access"||command=="rank"||command=="select"){
        ifstream infile(argv[2]);
        ifstream input_info(argv[3]);
        wavelet_tree wt(infile);
        if(command=="access"){
            vector<char> char_accessed=wt.tree_access_save(input_info);
            //cout<<"Messages: "<<endl;
            for(auto &c:char_accessed){
                cout<<c<<endl;
            }
        }else if(command=="rank"){
            vector<int64_t> rank_calculated=wt.tree_rank_save(input_info);

            for(auto &ir:rank_calculated){
                cout<<ir<<endl;
            }
        }else{
            vector<int64_t> select_calculated=wt.tree_select_save(input_info);
            for(auto &is:select_calculated){
                cout<<is<<endl;
            }
        }
    }

    /* test wavelet tree performance
    ofstream outfile;
    outfile.open("tree_fixtotal2.txt");
    outfile<<"string_size_lg,rank_time,select_time,unique_length\n";
    //outfile.open("tree_fixunique3.txt");
    //outfile<<"idx,rank_time,select_time,total_length\n";

    for(int i=0;i<300;i++) {
        //cout<<i<<endl;
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<> distr(4, 62);
        //uniform_int_distribution<> distr(10, 10000);
        uint64_t theint=distr(eng);
        string thestring=gen_random2(theint);
        //string thestring=gen_random(theint);
        wavelet_tree treetest(thestring);
        treetest.tree_build();
        vector<uint64_t> sizes = treetest.get_text_size();
        uint64_t unique = sizes[0];
        uint64_t total = sizes[1];
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        treetest.tree_rank('2', thestring.size()/8);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> seconds = duration_cast<duration<double>>(t2 - t1);
        high_resolution_clock::time_point t3 = high_resolution_clock::now();
        treetest.tree_select('2', thestring.size()/80);
        high_resolution_clock::time_point t4 = high_resolution_clock::now();
        duration<double> seconds2 = duration_cast<duration<double>>(t4 - t3);
        outfile<<i<<","<<seconds.count()<<","<<seconds2.count()<<","<<unique<<"\n";
        cout<<i<<","<<seconds.count()<<","<<seconds2.count()<<","<<unique<<"\n";
    }

     */

    return 0;
}