#include "red_black_tree.h"
#include <exception>
#include <ranges>

int main()
{
    try 
    {   
        algo::red_black_tree<int, char> tree{};
        for(const auto& [index, letter] : std::views::iota(0, 255 + 1) | std::views::enumerate)
        {
            std::cout << index << '\n';
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
