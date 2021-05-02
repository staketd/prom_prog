//
// Created by akhtyamovpavel on 5/1/20.
//

#include "LeapTestCase.h"

#include <Functions.h>

TEST_F(LeapTestCase, CheckInvalidYear) {
    ASSERT_THROW(IsLeap(-40), std::invalid_argument);
    ASSERT_ANY_THROW(IsLeap(-10));
    ASSERT_ANY_THROW(IsLeap(0));
}

TEST_F(LeapTestCase, CheckNotLeap) {
    ASSERT_FALSE(IsLeap(2));
    ASSERT_FALSE(IsLeap(100));
    ASSERT_FALSE(IsLeap(200));
    ASSERT_FALSE(IsLeap(1000));
    ASSERT_FALSE(IsLeap(123));
}

TEST_F(LeapTestCase, CheckLeap) {
    ASSERT_TRUE(IsLeap(4));
    ASSERT_TRUE(IsLeap(20));
    ASSERT_TRUE(IsLeap(400));
    ASSERT_TRUE(IsLeap(1200));
    ASSERT_TRUE(IsLeap(904));
}

TEST_F(LeapTestCase, CheckCorrect) {
    ASSERT_EQ(GetMonthDays(2021, 2), 28);
    ASSERT_EQ(GetMonthDays(2021, 1), 31);
    ASSERT_EQ(GetMonthDays(2020, 2), 29);
    ASSERT_EQ(GetMonthDays(2021, 4), 30);
    ASSERT_EQ(GetMonthDays(2021, 6), 30);
    ASSERT_EQ(GetMonthDays(1600, 2), 29);
    ASSERT_EQ(GetMonthDays(1600, 9), 30);
    ASSERT_EQ(GetMonthDays(2007, 11), 30);
}

TEST_F(LeapTestCase, CheckInvalid) {
    ASSERT_ANY_THROW(GetMonthDays(-1, 2));
    ASSERT_ANY_THROW(GetMonthDays(4, -10));
    ASSERT_ANY_THROW(GetMonthDays(-1, -1));
    ASSERT_ANY_THROW(GetMonthDays(42, -1));
    ASSERT_ANY_THROW(GetMonthDays(-1, 42));
    ASSERT_ANY_THROW(GetMonthDays(10, 42));
    ASSERT_ANY_THROW(GetMonthDays(10, 0));
}