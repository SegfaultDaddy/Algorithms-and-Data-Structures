#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <algorithm>
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
        
        constexpr red_black_tree_node(const node_color color, const Key& key, const Type& value)
            : color{color}, key{key}
            , value{value}
        {
        }
        
        constexpr red_black_tree_node(red_black_tree_node* parent, red_black_tree_node* left, red_black_tree_node* right, const node_color color, const Key& key, const Type& value)
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

        void remove(const Key& key)
        {
            node_type* found{find(key)};
            if(found == nullptr)
            {
                return;
            }
            delete_condition(found);
        }
        
        node_type* find(const Key& key)
        {
            node_type* position{root};
            while(position) 
            {
                if(key_compare{}(key, position->key))
                {
                    position = position->left;
                }
                else if(key_compare{}(position->key, key))
                {
                    position = position->right;
                }
                else 
                {
                    break;
                }
            }
            return position;
        }
        
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
        
        constexpr void delete_condition(node_type* target)
        {
            node_type* fixup_start{nullptr};
            if(target->left == nullptr)
            {
                fixup_start = target->right;
                delete_transplant(target, target->right);
            }
            else if(target->right == nullptr)
            {
                fixup_start = target->left;
                delete_transplant(target, target->left);
            }
            else 
            {
                node_type* replacement{find_maximum(target->left)};
                fixup_start = replacement->left;
                delete_condition_case3(target, replacement);
            }
            delete_fixup(fixup_start);
        }
        
        constexpr void delete_fixup(node_type* position)
        {
            while (position != root && !is_node_red(position)) 
            {
                if(is_left_child(position))
                {
                }
                else 
                {
                }
            }
        }
        
        constexpr void delete_fixup_case1()
        {
        }
        
        constexpr void delete_fixup_case2()
        {
        }
        
        constexpr void delete_fixup_case3()
        {
        }
        
        constexpr void delete_fixup_case4()
        {
        }
        
        constexpr void delete_condition_case3(node_type* target, node_type* replacement)
        {   
            delete_transplant(replacement, replacement->left);
            target->left->parent = replacement;
            replacement->left = target->left;
            delete_transplant(target, replacement);
            target->right->parent = replacement;
            replacement->right = target->right;
        }
        
        constexpr node_type find_maximum(node_type* position)
        {
            while(position->right) 
            {
                position = position->right;
            }
            return position;
        }
        
        constexpr void delete_transplant(node_type* target, node_type* replacement)
        {
            if(target == root)
            {
                root = replacement;
            }
            else if(is_left_child(target))
            {
                target->parent->left = replacement;
            }
            else 
            {
                target->parent->right = replacement;
            }
            if(replacement)
            {
                replacement->parent = target->parent;
            }
        }
        
        constexpr void insert_fixup(node_type* position)
        {
            while(is_node_red(position->parent)) 
            {
                node_type* uncle{find_uncle(position)};
                if(is_node_red(uncle))
                {
                    insert_fixup_case1(position->parent, uncle);
                    position = position->parent->parent;
                }
                else
                {
                    insert_fixup_black_uncle(&position);
                }
            }
            if(is_node_red(root))
            {
                root->color = node_color::black;
            }
        }
        
        constexpr void insert_fixup_black_uncle(node_type** position)
        {
            if(is_left_child(*position) != is_left_child((*position)->parent))
            {
                node_type* remember{(*position)->parent};
                insert_fixup_case2(*position);
                *position = remember;
            }
            else 
            {
                insert_fixup_case3(*position);
            }
        }

        constexpr void insert_fixup_case1(node_type* parent, node_type* uncle)
        {
            recolor(parent);
            recolor(uncle);
            recolor(parent->parent);
            if(root->color == node_color::red)
            {
                recolor(root);
            }
        }
        
        constexpr void insert_fixup_case2(node_type* node)
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

        constexpr void insert_fixup_case3(node_type* node)
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
            node_type* rightChild{node->right};
            rightChild->parent = node->parent;
            if(rightChild->parent)
            {
                if(is_left_child(node))
                {
                    rightChild->parent->left = rightChild;
                }
                else               
                {
                    rightChild->parent->right = rightChild;
                }
            }
            node->right = rightChild->left;
            node->parent = rightChild;
            rightChild->left = node;
            if(node->right)
            {
                node->right->parent = node;
            }
            if(node == root)
            {
                root = rightChild;
            }
        }
    
        constexpr void right_rotation(node_type* node)
        {   
            node_type* leftChild{node->left};
            leftChild->parent = node->parent;
            if(leftChild->parent)
            {
                if(is_left_child(node))
                {
                    leftChild->parent->left = leftChild;
                }
                else               
                {
                    leftChild->parent->right = leftChild;
                }
            }
            node->left = leftChild->right;
            node->parent = leftChild;
            leftChild->right = node;
            if(node->left)
            {
                node->left->parent = node;
            }
            if(node == root)
            {
                root = leftChild;
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

#endif
