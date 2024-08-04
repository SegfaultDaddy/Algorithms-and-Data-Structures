#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

//remove
#include <iostream>
#include <print>
//remove
#include <cstdint>
#include <memory>
#include <functional>
#include <queue>

namespace algo
{
    enum class RedBlackColor : std::uint8_t
    {
        red = 0,
        black,
    };

    template<typename Key, typename Type>
    struct RedBlackNode
    {
        RedBlackNode()
            : parent{nullptr}, left{nullptr}
            , right{nullptr}, color{}
            , key{}, data{}
        {
        }

        RedBlackNode(RedBlackNode* parent, 
                     RedBlackNode* left, 
                     RedBlackNode* right, 
                     RedBlackColor color, 
                     Key key, Type data)
            : parent{parent}, left{left}
            , right{right}, color{color}
            , key{std::move(key)}, data{std::move(data)}
        {
        }

        RedBlackNode* parent;
        RedBlackNode* left;
        RedBlackNode* right;
        RedBlackColor color;
        const Key key;
        Type data;
    };

    template<typename Key, 
             typename Type, 
             typename Compare = std::less<Key>>
    class RedBlackTree
    {
    public:
        using key_type = Key;
        using value_type = Type;
        using size_type = std::size_t;
        using key_compare = Compare;
        using difference_type = std::ptrdiff_t;
        using node_type = RedBlackNode<Key, Type>;
        using allocator_type = std::allocator<node_type>;
        using reference = value_type&;
        using const_reference = const value_type&; 
        using pointer = value_type*;
        using const_pointer = const value_type*;
        
        RedBlackTree() 
            : root{nullptr}, alloc{}
        {
        }

        void remove(const key_type& key)
        {
            node_type* found{nullptr};
            lookup_position(key, &found);
            if(found == nullptr)
            {
                return;
            }
            delete_condition(found);
        }

        void insert(const key_type& key, const_reference value)
        {
            node_type* parent{nullptr};
            node_type** position{lookup_position(key, &parent)};
            if(*position == nullptr)
            {
                *position = std::allocator_traits<allocator_type>::allocate(alloc, 1);
                std::allocator_traits<allocator_type>::construct(alloc, *position, parent, nullptr, nullptr, RedBlackColor::red, key, value);
                insert_fixup(*position);
            }
        }

        //remove 
        void print()
        {
            std::queue<node_type*> tree{};
            tree.push(root);
            for(auto i{tree.front()}; true; )
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
                if(!tree.empty())
                {
                    i = tree.front();
                }
                else 
                {
                    break;
                }
            }
        }
        //remove
    private:
        node_type** lookup_position(const key_type& key, node_type** parent)
        {
            node_type** pos{&root};
            while(*pos) 
            {
                *parent = *pos;
                if(key_compare{}(key, (*pos)->key))
                {
                    pos = &(*pos)->left;
                }
                else if(key_compare{}((*pos)->key, key))
                {
                    pos = &(*pos)->right;
                }
                else 
                {
                    break;
                }
            }
            return pos;
        }

        void delete_condition(node_type* target)
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
            //delete_fixup(fixup_start);
        }
        
        void delete_transplant(node_type* target, node_type* replacement)
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

        node_type* find_maximum(node_type* position)
        {
            while(position->right) 
            {
                position = position->right;
            }
            return position;
        }
        
        void delete_condition_case3(node_type* target, node_type* replacement)
        {   
            delete_transplant(replacement, replacement->left);
            target->left->parent = replacement;
            replacement->left = target->left;
            delete_transplant(target, replacement);
            target->right->parent = replacement;
            replacement->right = target->right;
        }

        void insert_fixup(node_type* position)
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
                root->color = RedBlackColor::black;
            }
        }
        
        void insert_fixup_black_uncle(node_type** position)
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
        
        void insert_fixup_case1(node_type* parent, node_type* uncle)
        {
            recolor(parent);
            recolor(uncle);
            recolor(parent->parent);
            if(is_node_red(root))
            {
                recolor(root);
            }
        }
        
        void insert_fixup_case2(node_type* node)
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

        void insert_fixup_case3(node_type* node)
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
        
        void recolor(node_type* node)
        {
            switch(node->color)
            {
            case RedBlackColor::red:
                node->color = RedBlackColor::black;
                break;
            case RedBlackColor::black:
                node->color = RedBlackColor::red;
                break;
            default:
                break;
            }
        }
        
        node_type* find_uncle(node_type* node)
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
        
        void left_rotation(node_type* node)
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
    
        void right_rotation(node_type* node)
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

        bool is_node_red(node_type* node)
        {
            if(node)
            {
                return node->color == RedBlackColor::red;
            }
            return false;
        }

        bool is_left_child(node_type* node)
        {
            return node->parent->left == node;
        }
        //remove
        void print_node(node_type* node)
        {
            std::cout << node << '|' << node->key << '~' << node->data << '~' << static_cast<std::uint32_t>(node->color) << '|' << node->parent << '~' << node->left << '~' << node->right << '\n';
        }
        //remove
        node_type* root;
        allocator_type alloc;
    };
}   
#endif