#include <gtest/gtest.h>
#include <exception>
#include "../source/red_black_tree.h"

TEST(REDBLACKTREE, INSERT)
{   
    algo::red_black_tree<int, char> tree{};
    tree.insert(10, 'A');
    tree.insert(85, 'A');
    tree.insert(15, 'A');
    tree.insert(70, 'A');
    tree.insert(20, 'A');
    tree.insert(60, 'A');
    tree.insert(30, 'A');
    tree.insert(50, 'A');
    tree.insert(65, 'A');
    tree.insert(80, 'A');
    tree.insert(90, 'A');
    tree.insert(40, 'A');
    tree.insert(5, 'A');
    tree.insert(55, 'A');
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

