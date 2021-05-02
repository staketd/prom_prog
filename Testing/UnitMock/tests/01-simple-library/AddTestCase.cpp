//
// Created by akhtyamovpavel on 5/1/20.
//

#include "AddTestCase.h"
#include "Functions.h"

void AddTestCase::SetUp() {
    Test::SetUp();
}

void AddTestCase::TearDown() {
    Test::TearDown();
}

TEST_F(AddTestCase, MultipleTest) {
    for (int i = -10; i <= 10; ++i) {
        for (int j = -10; j <= 10; ++j) {
            ASSERT_EQ(Add(i, j), i + j);
        }
    }
}

TEST_F(AddTestCase, CheckMinInt) {
    ASSERT_EQ(Add(INT32_MAX, 1), INT32_MIN);
}

TEST_F(AddTestCase, ZerosTest) {
    ASSERT_EQ(Add(0, 0), 0);
}