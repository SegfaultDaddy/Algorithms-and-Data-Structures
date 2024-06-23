#include "red_black_tree.h"
#include <algorithm>
#include <exception>
#include <ranges>

int main()
{
    try 
    {   
        algo::red_black_tree<int, char> tree{};
        tree.insert(10, 'A');
        tree.insert(85, 'A');
        tree.insert(15, 'A');
        std::cout << "CHECKPOINT#0\n";
        tree.print();
        tree.insert(70, 'A');
        tree.insert(20, 'A');
        std::cout << "CHECKPOINT#1\n";
        tree.print();
        tree.insert(60, 'A');
        tree.insert(30, 'A');
        tree.insert(50, 'A');
        tree.insert(65, 'A');
        tree.insert(80, 'A');
        std::cout << "CHECKPOINT #2\n";
        tree.print();
        tree.insert(90, 'A');
        tree.insert(40, 'A');
        tree.insert(5, 'A');
        tree.insert(55, 'A');
        std::cout << "CHECKPOINT #3\n";
        tree.print();
    } 
    catch (const std::exception& exept)
    {
        std::cerr << "Error: " << exept.what() << '\n';
    }
    return 0;
}

/*tree. tree.insert(10, 'A');
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
        for(const auto& [index, letter] : std::views::iota('a', 'z' + 1) | std::views::enumerate)
        {
            std::cout << index << '\n';
            tree.insert(index, letter);
        }
*/
