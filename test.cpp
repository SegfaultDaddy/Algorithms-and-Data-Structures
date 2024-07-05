#include "red_black_tree.h"
#include <cstddef>
#include <exception>
#include <ios>
#include <random>

void fixed_insert_test()
{   algo::red_black_tree<int, char> tree{};
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
    tree.print();
}

void fixed_delete_test()
{

}

int main()
{
    try 
    {
        fixed_insert_test();
    } 
    catch (const std::exception& exept)
    {
        std::cerr << "Error: " << exept.what() << '\n';
    }
    return 0;
}

