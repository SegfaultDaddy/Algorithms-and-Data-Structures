#include "red_black_tree.h"
#include <ranges>

int main()
{
    algo::red_black_tree<int, char> tree{};
    for(const auto& [index, letter] : std::views::iota('a', 'z' + 1) | std::views::enumerate)
    {
        tree.insert(index, letter);
    }
    tree.print();
    return 0;
}
