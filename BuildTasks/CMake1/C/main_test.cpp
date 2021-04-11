#include <gtest/gtest.h>
#include "main.hpp"

TEST(LibTests, Test1) {
    for (int i = 0; i < 100; ++i) {
        ASSERT_EQ(B::boo(i), i);
    }
}

TEST(MainTest, Test1) {
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            ASSERT_EQ(C::sum(i, j), i + j);
        }
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}