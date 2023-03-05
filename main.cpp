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

void Print(const vector<vector<string>> &_vector){
    unsigned int count = 0;
    for(auto ip = _vector.cbegin(); ip != _vector.cend(); ++ip){
        for_each(ip->cbegin(), ip->cend(), [count, ip] (string val) mutable {
            cout << val;
            if (count++ < ip->size()-1) cout << ".";
        });
        cout << endl;
    }
}

auto FindCase(const vector<vector<string>> &_vector, const tuple<unsigned int, unsigned int> *_filter, const int tuple_len) {
    vector<vector<string>> result_ip;
    for (unsigned int j = 0; j < _vector.size(); j++) {
        int flag = tuple_len;
        for (int i = 0; i < tuple_len; i++) {
            unsigned int index = get<0>(_filter[i]);
            unsigned int val = get<1>(_filter[i]);
            if ((unsigned int) stoi(_vector[j][index]) == val) flag--;
        }
        if (!flag) result_ip.push_back(_vector[j]);
    }
    return result_ip;
}

vector<vector<string>> FindCase(const vector<vector<string>> &_vector, unsigned int val) {
    vector<vector<string>> result_ip;
    for (unsigned int i = 0; i < _vector.size(); i++) {
        for (unsigned int j = 0; j<_vector[i].size(); j++) {
            if ((unsigned int) stoi(_vector[i][j]) == val) {
                result_ip.push_back(_vector[i]);
                break;
            }
        }
    }
    return result_ip;
}

void Sort(vector<vector<string>> &_vector){
    sort(_vector.begin(), _vector.end(), [](vector<string> &l1, vector<string> &l2) {
        for(unsigned int i=0;i < l1.size();i++){
            if (stoi(l1[i]) > stoi(l2[i])) return true;
            else if (stoi(l1[i]) == stoi(l2[i])) continue;
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
        vector<vector<string>> ip_pool;
        for(string line; getline(cin, line);){
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        Sort(ip_pool);
        Print(ip_pool);

        // TODO filter by first byte and output
        auto tup = make_tuple(0,1);
        Print(FindCase(ip_pool, (const tuple<unsigned int, unsigned int> *) &tup, 1));

        // TODO filter by first and second bytes and output
        tuple<unsigned int, unsigned int> tup2[2] = {{0,46}, {1, 70}};
        Print(FindCase(ip_pool, (const tuple<unsigned int, unsigned int> *) &tup2, 2));

        // TODO filter by any byte and output
        Print(FindCase(ip_pool, 46));
    }
    catch(const exception &e){
        cerr << e.what() << endl;
    }

    return 0;
}