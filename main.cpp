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

void Print(const vector<vector<unsigned short int>> &_vector){
    unsigned int count = 0;
    for(auto ip = _vector.cbegin(); ip != _vector.cend(); ++ip){
        for_each(ip->cbegin(), ip->cend(), [count, ip] (unsigned short int val) mutable {
            cout << val;
            if (count++ < ip->size()-1) cout << ".";
        });
        cout << endl;
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

        vector<vector<unsigned short int>> result;
        vector<vector<unsigned short int>> result_1;
        vector<vector<unsigned short int>> result_2;

        auto check = [&result](const vector<unsigned short int> vector) {if (vector[0] == 1) result.push_back(vector);};
        auto check_2 = [&result_1](const vector<unsigned short int> vector) {if (vector[0] == 46 && vector[1] == 70) result_1.push_back(vector);};
        auto check_3 = [&result_2](const vector<unsigned short int> vector) {
            if ( any_of(vector.cbegin(), vector.cend(), [](unsigned short int val) {return val == 46;}))
                result_2.push_back(vector);
        };

        for_each(ip_pool.cbegin(), ip_pool.cend(), check);
        for_each(ip_pool.cbegin(), ip_pool.cend(), check_2);
        for_each(ip_pool.cbegin(), ip_pool.cend(), check_3);

        Print(result);
        Print(result_1);
        Print(result_2);
    }
    catch(const exception &e){
        cerr << e.what() << endl;
    }

    return 0;
}