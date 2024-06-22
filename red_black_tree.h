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
        black,
        red,
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
        
        red_black_tree_node(red_black_tree_node* parent, red_black_tree_node* left, red_black_tree_node* right, const node_color color, const Key& key, const Type& value)
            : parent{parent}, left{left}
            , right{right}, color{color}
            , key{key}, value{value}
        {
        }
        
        red_black_tree_node* parent;
        red_black_tree_node* left;
        red_black_tree_node* right;
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
            node_type* parent{nullptr};
            while(*position) 
            {
                parent = *position;
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
                insert_and_fix(position, parent, key, value);
            }
        }

        void print()
        {
            std::queue<node_type*> tree{};
            tree.push(root);
            for(auto i{tree.front()}; !tree.empty(); i = tree.front())
            {
                print_node(i);
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
        
        void insert_and_fix(node_type** position, node_type* parent, const Key& key, const Type& value)
        {
            if(position == &root)
            {
                root = new node_type{nullptr, nullptr, nullptr, node_color::black, key, value};
            }
            else             
            {
                *position = new node_type{parent, nullptr, nullptr, node_color::red, key, value};
                if(parent->parent)
                {
                    node_type* uncle{find_uncle(parent)};
                    if(does_uncle_red(uncle))
                    {
                    }
                    else
                    {
                    }
                }
            }
        }
        
        node_type* find_uncle(node_type* parent)
        {
            if(parent->parent->left == parent)
            {
                return parent->parent->right;
            }
            else  
            {
                return parent->parent->left;   
            }
        }
        
        constexpr bool does_uncle_red(node_type* uncle)
        {
            if(uncle)
            {
                if(uncle->color == node_color::red)
                {
                     return true;
                }
            }
            return false;
        }
        
        void print_node(node_type* node)
        {
            std::cout << node << '|' << node->key << '~' << node->value << '|' << node->parent << '~' << node->left << '~' << node->right << '\n';
        }

        node_type* root;

    };
}

#endif // !RED_BLACK_TREE_H
