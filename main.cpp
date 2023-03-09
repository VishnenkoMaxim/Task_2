#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

#include "main.h"

#ifdef TEST_BUILD
#include <gtest/gtest.h>
#endif

using namespace std;

vector<string> split(const string &str, char d){
    vector<string> r;
    string::size_type start = 0;
    string::size_type stop = str.find_first_of(d);
    while(stop != string::npos){
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    r.push_back(str.substr(start));
    return r;
}

void PrintIP(const vector<unsigned short int> &_vector){
    unsigned int count = 0;
    for_each(_vector.cbegin(), _vector.cend(), [count, &_vector] (unsigned short int val) mutable {
        cout << val;
        if (count++ < _vector.size()-1) cout << ".";
    });
    cout << endl;

}

void Print(const vector<vector<unsigned short int>> &_vector){
    for(auto ip = _vector.cbegin(); ip != _vector.cend(); ++ip){
        PrintIP(*ip);
    }
}

void Sort(vector<vector<unsigned short int>> &_vector){
    sort(_vector.begin(), _vector.end(), [](vector<unsigned short int> &l1, vector<unsigned short int> &l2) {
        for(unsigned int i=0;i < l1.size(); i++){
            if (l1[i] > l2[i]) return true;
            else if (l1[i] == l2[i]) continue;
            else return false;
        }
        return false;
    });
}

template <class Operation>
void FindCase(const vector<vector<unsigned short int>> &_vector, Operation oper){
    for(auto ip = _vector.cbegin(); ip != _vector.cend(); ++ip){
        if (oper(*ip)) PrintIP(*ip);
    }
}

int main(){
#ifdef TEST_BUILD
    testing::InitGoogleTest();
    int test_stat = RUN_ALL_TESTS();
    (void) test_stat;
#endif

    try{
        vector<vector<unsigned short int>> ip_pool;
        for(string line; getline(cin, line);){
            auto v = split(line, '\t');
            vector<string> tmp_vec = split(v.at(0), '.');
            vector<unsigned short int> int_vec;
            for(auto ip = tmp_vec.cbegin(); ip != tmp_vec.cend(); ++ip){
                int_vec.push_back(stoi(*ip));
            }
            ip_pool.push_back(int_vec);
        }

        // TODO reverse lexicographically sort
        Sort(ip_pool);
        Print(ip_pool);

        FindCase(ip_pool, [](const vector<unsigned short int> vector) {return vector[0] == 1;});
        FindCase(ip_pool, [](const vector<unsigned short int> vector) {return (vector[0] == 46) && (vector[1] == 70);});
        FindCase(ip_pool, [](const vector<unsigned short int> vector) {return any_of(vector.cbegin(), vector.cend(), [](unsigned short int val) {return val == 46;});});
    }
    catch(const exception &e){
        cerr << e.what() << endl;
    }

    return 0;
}