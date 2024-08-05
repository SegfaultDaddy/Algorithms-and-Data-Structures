//#include <gtest/gtest.h>
#include <vector>
#include <random>
#include "../source/red_black_tree.h"

/*TEST(red_black_tree_test_insert, insert)
{
    std::vector<int> keys{10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55};
    for(const auto& key : keys)
    {
        tree.insert(key, 0);
    }
}
TEST(red_black_tree_test_remove, remove)
{
    std::vector<int> keys{10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55};
    for(const auto& key : keys)
    {
        tree.insert(key, 0);
    }
    for(const auto& key : keys)
    {
        tree.remove(key);
    }
    
    algo::RedBlackTree<int, int> tree;
    std::vector<int> keys{12, 8, 15, 5, 9, 13, 19, 10, 23};
    for(const auto& key : keys)
    {
        tree.insert(key, 0);
    }
    tree.print();
    tree.remove(19);
    std::cout << "Delete\n";
    tree.print();
    algo::RedBlackTree<int, int> tree;
    std::vector<int> keys{12, 8, 15, 5, 9, 13, 23, 1, 10};
    for(const auto& key : keys)
    {
        tree.insert(key, 0);
    }
    tree.print();
    tree.remove(5);
    std::cout << "Delete\n";
    tree.print();
    std::vector<int> keys{12, 8, 15, 1, 9, 13, 23, 10};
    for(const auto& key : keys)
    {
        tree.insert(key, 0);
    }
    tree.print();
    tree.remove(12);
    std::cout << "Delete\n";
    
}*/

int main(int argc, char** argv)
{
    std::vector<int> keys{10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55};
    algo::RedBlackTree<int, int> tree;
    for(const auto& key : keys)
    {
        tree.insert(key, 0);
    }
    std::shuffle(std::begin(keys), std::end(keys), std::default_random_engine{});
    for(const auto& key : keys)
    {
        std::cout << key << '\n';
        tree.remove(key);
        tree.print();
    }
    tree.insert(10, 0);
    tree.walk();
    //testing::InitGoogleTest(&argc, argv);
    return 0;//RUN_ALL_TESTS();
}