#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <tuple>

using namespace std;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
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
    for(auto ip = _vector.cbegin(); ip != _vector.cend(); ++ip){
        for_each(ip->cbegin(), ip->cend(), [count=0, ip] (string val) mutable {
            cout << val;
            if (count++ < ip->size()-1) cout << ".";
        });
        cout << endl;
    }
}

void PrintCase(const vector<vector<string>> &_vector, const tuple<unsigned int, unsigned int> *_filter, const int tuple_len){
    for (int j=0; j<_vector.size(); j++){
        int flag = tuple_len;
        for(int i=0; i<tuple_len; i++){
            unsigned int index = get<0>(_filter[i]);
            unsigned int val = get<1>(_filter[i]);
            if (stoi(_vector[j][index]) == val) flag--;
        }
        if (!flag) {
            int count = 0;
            for (int k=0; k<_vector[j].size(); k++) {
                cout << _vector[j][k];
                if (count++ < _vector[j].size()-1) cout << ".";
            }
            cout << endl;
        }
    }
}

auto FindCase(const vector<vector<string>> &_vector, const tuple<unsigned int, unsigned int> *_filter, const int tuple_len){
    vector<vector<string>> result_vec;
    for (int j=0; j<_vector.size(); j++){
        int flag = tuple_len;
        for(int i=0; i<tuple_len; i++){
            unsigned int index = get<0>(_filter[i]);
            unsigned int val = get<1>(_filter[i]);
            if (stoi(_vector[j][index]) == val) flag--;
        }
        if (!flag) {
            result_vec.push_back(_vector[j]);
        }
    }
    return result_vec;
}

void Sort(vector<vector<string>> &_vector){
    sort(_vector.begin(), _vector.end(), [](vector<string> &l1, vector<string> &l2) {
        for(int i=0;i<l1.size();i++){
            if (stoi(l1[i]) > stoi(l2[i])) return true;
            else if (stoi(l1[i]) == stoi(l2[i])) continue;
            else return false;
        }
        return false;
    });
}

int main(int argc, char const *argv[]){
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

        tuple<unsigned int, unsigned int> tup[1];
        tup[0] = make_tuple(0, 1);
        PrintCase(ip_pool, (const tuple<unsigned int, unsigned int> *) &tup, 1);

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        tuple<unsigned int, unsigned int> tup2[2];
        tup2[0] = make_tuple(0, 46);
        tup2[1] = make_tuple(1, 70);
        PrintCase(ip_pool, (const tuple<unsigned int, unsigned int> *) &tup2, 2);

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const exception &e){
        cerr << e.what() << endl;
    }

    return 0;
}
