//
// Created by akhtyamovpavel on 5/1/20.
//


#pragma once

#include <gtest/gtest.h>
#include <boost/filesystem/path.hpp>

class TreeTestCase : public ::testing::Test {
public:
    void SetUp() override;

    void TearDown() override;

private:
    static void CreateFile(const std::string& path);
};


