#include "red_black_tree.h"
#include <exception>
#include <ranges>

int main()
{
    try 
    {   
        algo::red_black_tree<int, char> tree{};
        for(const auto& [index, letter] : std::views::iota('a', 'z' + 1) | std::views::enumerate)
        {
            tree.insert(index, letter);
        }
        tree.print();
    } 
    catch (const std::exception& exept)
    {
        std::cerr << "Error: " << exept.what() << '\n';
    }
    return 0;
}
