// Student practice C++ searching disjoint sets
// Copyright 2025 AlexBurnes@gmail.com
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gtest/gtest.h>
#include "grouping.hpp"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class GroupingTest : public testing::Test {
    protected:
        GroupingTest() {}
        ~GroupingTest() override {}

        Grouping grouping{
            {
                {11, 21},
                {11, 22},
                {12, 22},
                {12, 23},
                {13, 23},
                {13, 24}
            }
        };

        bool compare(Grouping::group_files_t &result, const Grouping::group_files_t& expected) {
            if (result.size() != expected.size()) return false;
            for (auto [group_id, expected_list] : expected) {
                if (result.count(group_id) == 0) return false;
                auto found_list = result[group_id];
                if (not (expected_list.size() == found_list.size())) return false;
                std::sort(expected_list.begin(), expected_list.end());
                std::sort(found_list.begin(), found_list.end());
                if (not std::equal(found_list.begin(), found_list.end(), expected_list.begin())) return false;
            }
            return true;
        }
};

TEST_F(GroupingTest, group_1) {
    auto result = grouping.find({21});
    ASSERT_EQ(
        compare(
            result,
            {
                {1, {11}}
            }
        ),
        true
    );
}

TEST_F(GroupingTest, group_2) {
    auto result = grouping.find({22});
    ASSERT_EQ(
        compare(
            result,
            {
                {1, {11, 12}}
            }
        ),
        true
    );
}

TEST_F(GroupingTest, group_3) {
    auto result = grouping.find({21, 24});
    ASSERT_EQ(
        compare(
            result,
            {
                {2, {13}},
                {1, {11}}
            }
        ),
        true
    );
}

TEST_F(GroupingTest, group_4) {
    auto result = grouping.find({22, 23});
    ASSERT_EQ(
        compare(
            result,
            {
                {1, {11, 12, 13}}
    }
        ),
        true
    );
}

TEST_F(GroupingTest, group_5) {
    auto result = grouping.find({21, 22, 23, 24});
    ASSERT_EQ(
        compare(
            result,
            {
                {1, {11, 12, 13}}
            }
        ),
        true
    );
}

TEST_F(GroupingTest, group_6) {
    auto result = grouping.find({24});
    ASSERT_EQ(
        compare(
            result,
            {
                {1, {13}}
            }
        ),
        true
    );
}

TEST_F(GroupingTest, group_7) {
    auto result = grouping.find({23, 24});
    ASSERT_EQ(
        compare(
            result,
            {
                {1, {12, 13}}
            }
        ),
        true
    );
}
