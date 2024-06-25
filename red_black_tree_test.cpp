#include "red_black_tree.h"
#include <cstddef>
#include <exception>
#include <random>

std::size_t generate_unsigned_int(std::size_t low_bound, std::size_t high_bound)
{
    std::random_device rd{};
    std::seed_seq ss{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
    std::default_random_engine dre{ss};
    std::uniform_int_distribution<std::size_t> uid{low_bound, high_bound};
    return uid(dre);
}

void random_test(std::size_t size, std::size_t low_bound, std::size_t high_bound)
{
    for(std::size_t index{0}; index < 10; ++index)
    {
        std::cout << generate_unsigned_int(low_bound, high_bound) << '\n';
    }
}

void fixed_test()
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

int main()
{
    try 
    {
        random_test(10, 10, 100);
    } 
    catch (const std::exception& exept)
    {
        std::cerr << "Error: " << exept.what() << '\n';
    }
    return 0;
}

