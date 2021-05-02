//
// Created by akhtyamovpavel on 5/1/20.
//


#include "TreeTestCase.h"
#include "Tree.h"

void TreeTestCase::SetUp() {
    Test::SetUp();
    boost::filesystem::create_directories("test_dir/inner_dir");
    CreateFile("test_dir/inner_file");
    CreateFile("test_dir/inner_dir/inner_inner_file");

    boost::filesystem::create_directories("empty_nodes/dir1/dir2");
    boost::filesystem::create_directories("empty_nodes/dir3/dir4");
    CreateFile("empty_nodes/some_file");
    CreateFile("empty_nodes/dir3/some_file");

    boost::filesystem::create_directories("some_dir/empty_nodes");

    boost::filesystem::create_directories("some_dir2");
    CreateFile("some_dir2/empty_nodes");
}

void TreeTestCase::TearDown() {
    Test::TearDown();
    boost::filesystem::remove_all("test_dir");
    boost::filesystem::remove_all("empty_nodes");
}

void TreeTestCase::CreateFile(const std::string& path) {
    std::fstream fs;
    fs.open(path, std::ios::out);
    fs.close();
}


TEST_F(TreeTestCase, CheckNotExistent) {
    ASSERT_ANY_THROW(GetTree("some_nonexistent_dir", false));
    ASSERT_ANY_THROW(GetTree("", false));

    ASSERT_ANY_THROW(GetTree("some_nonexistent_dir2", true));
}

TEST_F(TreeTestCase, CheckNotDirectory) {
    ASSERT_ANY_THROW(GetTree("test_dir/inner_file", false));
    ASSERT_ANY_THROW(GetTree("test_dir/inner_file", true));
}

TEST_F(TreeTestCase, CheckOnlyDirectory) {
    auto nodes = GetTree("test_dir", true);
    ASSERT_TRUE(nodes.is_dir);
    ASSERT_EQ(nodes.name, "test_dir");
    ASSERT_EQ(nodes.children.size(), 1);
    auto ch = nodes.children.front();
    ASSERT_EQ(ch.name, "inner_dir");
    ASSERT_EQ(ch.children.size(), 0);
}

TEST_F(TreeTestCase, CheckDirectory) {
    auto nodes = GetTree("test_dir", false);
    ASSERT_TRUE(nodes.is_dir);
    ASSERT_EQ(nodes.name, "test_dir");
    ASSERT_EQ(nodes.children.size(), 2);
    for (auto& child : nodes.children) {
        if (child.name == "inner_dir") {
            ASSERT_TRUE(child.is_dir);
            ASSERT_EQ(child.children.size(), 1);
            auto& inner_child = child.children.front();
            ASSERT_EQ(inner_child.name, "inner_inner_file");
            ASSERT_FALSE(inner_child.is_dir);
        } else {
            ASSERT_EQ(child.name, "inner_file");
            ASSERT_FALSE(child.is_dir);
        }
    }
}

TEST_F(TreeTestCase, FilterTest) {
    auto empty_nodes = GetTree("empty_nodes", false);
    FilterEmptyNodes(empty_nodes, "empty_nodes");
    auto filtered_nodes = GetTree("empty_nodes", false);
    ASSERT_EQ(filtered_nodes.name, "empty_nodes");
    ASSERT_EQ(filtered_nodes.children.size(), 3);
    for (auto& children : filtered_nodes.children) {
        if (children.name == "some_file") {
            ASSERT_FALSE(children.is_dir);
        } else if (children.name == "dir3") {
            ASSERT_EQ(children.children.size(), 1);
        } else if (children.name == "dir1") {
            ASSERT_TRUE(children.children.empty());
        } else {
            ASSERT_FALSE(true);
        }
    }
}

TEST_F(TreeTestCase, EqualTest) {
    auto empty_nodes = GetTree("empty_nodes", false);
    auto test_nodes = GetTree("test_dir", false);
    auto other_empty_nodes = GetTree("some_dir/empty_nodes", false);
    auto some_dir2 = GetTree("some_dir2", false);

    ASSERT_FALSE(empty_nodes == test_nodes);
    ASSERT_TRUE(empty_nodes == empty_nodes);
    ASSERT_FALSE(other_empty_nodes == empty_nodes);
    ASSERT_FALSE(some_dir2.children.front() == empty_nodes);

}
