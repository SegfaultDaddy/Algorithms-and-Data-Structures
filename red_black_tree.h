#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <cmath>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <ranges>

namespace algo
{
    enum class node_color : std::uint8_t
    {
        red,
        black,
        max_colors,
    };
    
    template<typename Key, typename Type>
    struct red_black_tree_node
    {   
        red_black_tree_node(const node_color color, const Key& key, const Type& value)
            : color{color}, key{key}
            , value{value}
        {
        }
        red_black_tree_node(red_black_tree_node* left, red_black_tree_node* right, red_black_tree_node* parent, const node_color color, const Key& key, const Type& value)
            : left{left}, right{right}
            , parent{parent}, color{color}
            , key{key}, value{value}
        {
        }
        red_black_tree_node* left;
        red_black_tree_node* right;
        red_black_tree_node* parent;
        node_color color;
        const Key key;
        Type value;
    };

    template<typename Key, typename Type, typename Compare = std::less<Key>>
    class red_black_tree
    {
    public:
        
        using node_type = red_black_tree_node<Key, Type>;
        using key_compare = Compare;

        red_black_tree()
            : root{nullptr}
        {
        }

        red_black_tree(const red_black_tree& that) = delete;
    
        red_black_tree(red_black_tree&& that) = delete;

        red_black_tree& operator=(const red_black_tree&& that) = delete;

        red_black_tree& operator=(red_black_tree&& that) = delete;

        void insert(const Key& key, const Type& value)
        {
            node_type** position{&root};
            while(*position) 
            {
                if(key_compare{}(key, (*position)->value))
                {
                    position = &(*position)->left;
                }
                else if(key_compare{}((*position)->value, key))
                {
                    position = &(*position)->right;
                }
                else 
                {
                    break;
                }
            }
            if(*position == nullptr)
            {
                insert_cases(position, key, value);
            }
        }

        void print()
        {
            std::queue<node_type*> tree{};
            tree.push(root);
            for(auto i{tree.front()}; !tree.empty(); ++i)
            {
                print_node(*tree.front());
                if(i->left)
                {
                    tree.push(i->left);
                }
                if(i->right)
                {
                    tree.push(i->right);
                }
                tree.pop();
            }
        }

    private:    
        
        void insert_cases(node_type** position, const Key& key, const Type& value)
        {
            if(position == &root)
            {
                root = new node_type{nullptr, nullptr, nullptr, node_color::red, key, value};
            }
        }
        
        void print_node(const node_type& node)
        {
            std::cout << "Node: " << &node << '\n';
            std::cout << "Key: " << node.key << '\n';
            std::cout << "Value: " << node.value << '\n';
            std::cout << "Color: " << static_cast<std::uint32_t>(node.color) << '\n';
            std::cout << "Parent: " << node.parent << '\n';
            std::cout << "Left: " << node.left << '\n';
            std::cout << "Right: " << node.right << '\n';
        }

        node_type* root;

    };
}

#endif // !RED_BLACK_TREE_H
