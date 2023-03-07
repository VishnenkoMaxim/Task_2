#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

#include <gtest/gtest.h>

using namespace std;

void Sort(vector<vector<string>> &_vector);
vector<vector<string>> FindCase(const vector<vector<string>> &_vector, unsigned int val);

TEST(BasicTests, Test_1){
    vector<vector<string>> test_case_1 {{"113", "162", "145", "156"}, {"157", "39", "22", "224"}, { "79", "180", "73", "190"},
                                        {"179", "210", "145", "4"}, {"219", "102", "120", "135"}, {"67", "232", "81", "208"}};

    vector<vector<string>> test_case_1_result {{"219", "102", "120", "135"}, {"179", "210", "145", "4"}, {"157", "39", "22", "224"} ,
                                               {"113", "162", "145", "156"}, { "79", "180", "73", "190"}, {"67", "232", "81", "208"}};
    Sort(test_case_1);
    EXPECT_EQ(test_case_1, test_case_1_result);
}

TEST(BasicTests, Test_2){
    vector<vector<string>> test_case_1 {{"113", "162", "145", "156"}, {"157", "39", "22", "224"}, { "79", "180", "73", "190"},
                                        {"179", "210", "145", "4"}, {"219", "102", "120", "135"}, {"67", "232", "81", "208"}};
    vector<vector<string>> test_case_2 {{"67", "232", "81", "208"}};
    auto result = FindCase(test_case_1, 67);
    EXPECT_EQ(result, test_case_2);
}

