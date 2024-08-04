//#include <gtest/gtest.h>
#include <vector>
#include "../source/red_black_tree.h"

/*TEST(red_black_tree_test, insert)
{
    std::vector<int> keys{10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55};
    for(const auto& key : keys)
    {
        tree.insert(key, 0);
    }
    tree.print();
}
TEST(red_black_tree_test, delete)
{
    std::vector<int> keys{10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55};
    for(const auto& key : keys)
    {
        tree.insert(key, 0);
    }
    tree.print();
}*/

int main(int argc, char** argv)
{
    algo::RedBlackTree<int, int> tree;
    std::vector<int> keys{10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55};
    for(const auto& key : keys)
    {
        tree.insert(key, 0);
    }
    tree.remove(80);
    tree.print();
    //testing::InitGoogleTest(&argc, argv);
    return 0;//RUN_ALL_TESTS();
}