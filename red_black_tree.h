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
                if(key_compare{}(key, (*position)->key))
                {
                    position = &(*position)->left;
                }
                else if(key_compare{}((*position)->key, key))
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
                *position = new node_type{parent, nullptr, nullptr, node_color::red, key, value};
                insert_fixup(*position);
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
        
        void insert_fixup(node_type* position)
        {
            while(is_node_red(position->parent)) 
            {
                if(position->parent->parent)
                {
                    node_type* uncle{find_uncle(position)};
                    if(is_node_red(uncle))
                    {
                        case1_insert(position->parent, uncle);
                        position = position->parent->parent;
                    }
                    else
                    {
                        if(is_left_child(position) != is_left_child(position->parent))
                        {
                            node_type* remember{position->parent};
                            case2_insert(position);
                            position = remember;
                        }
                        else 
                        {
                            case3_insert(position);
                        }
                    }
                }
            }
            if(is_node_red(root))
            {
                root->color = node_color::black;
            }
        }

        constexpr void case1_insert(node_type* parent, node_type* uncle)
        {
            recolor(parent);
            recolor(uncle);
            recolor(parent->parent);
            if(root->color == node_color::red)
            {
                recolor(root);
            }
        }
        
        constexpr void case2_insert(node_type* node)
        {
            if(is_left_child(node))
            {
                right_rotation(node->parent);
            }
            else 
            {
                left_rotation(node->parent);
            }
        }

        constexpr void case3_insert(node_type* node)
        {
            recolor(node->parent);
            recolor(node->parent->parent);
            if(is_left_child(node->parent))
            {
                right_rotation(node->parent->parent);
            }
            else 
            {
                left_rotation(node->parent->parent);
            }
        }
        
        constexpr void left_rotation(node_type* node)
        {   
            node_type* right_child{node->right};
            right_child->parent = node->parent;
            if(right_child->parent)
            {
                if(is_left_child(node))
                {
                    right_child->parent->left = right_child;
                }
                else               
                {
                    right_child->parent->right = right_child;
                }
            }
            node->right = right_child->left;
            node->parent = right_child;
            right_child->left = node;
            if(node->right)
            {
                node->right->parent = node;
            }
            if(node == root)
            {
                root = right_child;
            }
        }
    
        constexpr void right_rotation(node_type* node)
        {   
            node_type* left_child{node->left};
            left_child->parent = node->parent;
            if(left_child->parent)
            {
                if(is_left_child(node))
                {
                    left_child->parent->left = left_child;
                }
                else               
                {
                    left_child->parent->right = left_child;
                }
            }
            node->left = left_child->right;
            node->parent = left_child;
            left_child->right = node;
            if(node->left)
            {
                node->left->parent = node;
            }
            if(node == root)
            {
                root = left_child;
            }
        }

        constexpr void recolor(node_type* node)
        {
            switch(node->color)
            {
            case node_color::red:
                node->color = node_color::black;
                break;
            case node_color::black:
                node->color = node_color::red;
                break;
            default:
                break;
            }
        }
        
        constexpr node_type* find_uncle(node_type* node)
        {
            if(is_left_child(node->parent))
            {
                return node->parent->parent->right;
            }
            else  
            {
                return node->parent->parent->left;   
            }
        }
        
        constexpr bool is_left_child(node_type* node)
        {
            return node->parent->left == node;
        }
        
        constexpr bool is_node_red(node_type* node)
        {
            if(node)
            {
                if(node->color == node_color::red)
                {
                     return true;
                }
            }
            return false;
        }
        
        void print_node(node_type* node)
        {
            std::cout << node << '|' << node->key << '~' << node->value << '~' << static_cast<std::uint32_t>(node->color) << '|' << node->parent << '~' << node->left << '~' << node->right << '\n';
        }

        node_type* root;

    };
}

#endif // !RED_BLACK_TREE_H
