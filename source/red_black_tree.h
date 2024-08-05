#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

//remove
#include <iostream>
#include <print>
#include <queue>
//remove
#include <cstdint>
#include <memory>
#include <functional>
#include <utility>

namespace algo
{
    enum class RedBlackColor : std::uint8_t
    {
        red = 0,
        black,
        max_red_black_color,
    };

    template<typename Key, 
             typename Type>
    struct RedBlackNode
    {
        RedBlackNode()
            : parent{nullptr}, left{nullptr}
            , right{nullptr}, color{}
            , key{}, data{}
        {
        }

        template<typename... Args>
        RedBlackNode(RedBlackNode* parent, 
                     RedBlackNode* left, 
                     RedBlackNode* right, 
                     RedBlackColor color, 
                     Key key, Args&&... args)
            : parent{parent}, left{left}
            , right{right}, color{color}
            , key{std::move(key)}, data{std::forward<Args>(args)...}
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
        using iterator = node_type*;

        RedBlackTree() 
            : root{nullptr}, alloc{}
            , compare{}
        {
        }
        
        ~RedBlackTree() 
        {
            clear();
        }
        
        template<typename... Args>
        iterator emplace(const key_type& key, Args&&... args)
        {
            node_type* parent{nullptr};
            node_type** position{lookup_position(key, &parent, &root)};
            if(*position == nullptr)
            {
                *position = std::allocator_traits<allocator_type>::allocate(alloc, 1);
                std::allocator_traits<allocator_type>::construct(alloc, *position, parent, nullptr, nullptr, 
                                                                 RedBlackColor::red, key, std::forward<Args>(args)...);
                insert_fixup(*position);
            }
            return iterator{*position};
        }

        iterator insert(const key_type& key, const value_type& value)
        {
            return emplace(key, value);
        }
        
        void remove(const key_type& key)
        {
            node_type* found{nullptr};
            lookup_position(key, &found, &root);
            if(found == nullptr)
            {
                return;
            }
            delete_condition(found);
            std::allocator_traits<allocator_type>::destroy(alloc, found);
            std::allocator_traits<allocator_type>::deallocate(alloc, found, 1);
        }

        reference operator[](const key_type& ref)
        {
            return *insert(ref, value_type{});
        }

        void clear()
        {
        }
        
        //remove 
        void print() const
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

        void walk() const
        {
            walk(root);
        }
        //remove
    private:
        //remove
        void walk(const node_type* pos) const
        {
            if(pos == nullptr)
            {
                return;
            }
            walk(pos->left);
            std::cout << pos->key << '\n';
            walk(pos->right);
        }
        //remove

        node_type** lookup_position(const key_type& key, node_type** parent, node_type** pos) const
        {
            while(*pos) 
            {
                *parent = *pos;
                if(compare(key, (*pos)->key))
                {
                    pos = &(*pos)->left;
                }
                else if(compare((*pos)->key, key))
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
        }
        
        void delete_fixup(node_type* start, node_type* parent)
        {
            print_node(parent);
            node_type* sibling{nullptr};
            while(start != root && !is_node_red(start))
            {
                sibling = lookup_sibling(start, parent);
                if(is_node_red(sibling))
                {
                    sibling = delete_fixup_case1(sibling, parent);
                }
                if(sibling != nullptr)
                {
                    if(!is_node_red(sibling->left) 
                       && !is_node_red(sibling->right))
                    {
                        sibling->color = RedBlackColor::red;
                        start = parent;
                        parent = start->parent;
                    }
                    else
                    {
                        if((!is_node_red(sibling->left) && is_left_child(sibling))
                           || (!is_node_red(sibling->right) && !is_left_child(sibling)))
                        {
                            sibling = delete_fixup_case3(sibling, parent);
                        }
                        start = delete_fixup_case4(start, sibling, parent);
                    }
                }
                if(start)
                {
                    start->color = RedBlackColor::black;
                }
            }
        }

        node_type* delete_fixup_case1(node_type* sibling, node_type* parent)
        {
            sibling->color = RedBlackColor::black;
            parent->color = RedBlackColor::red;
            if(!is_left_child(sibling))
            {
                left_rotation(parent);
                return parent->right;
            }
            right_rotation(parent);
            return parent->left;
        }
        
        node_type* delete_fixup_case3(node_type* sibling, node_type* parent)
        {
            sibling->color = RedBlackColor::red;
            if(is_left_child(sibling))
            {
                sibling->right->color = RedBlackColor::black;
                left_rotation(sibling);
                return parent->left;
            }
            sibling->left->color = RedBlackColor::black;
            right_rotation(sibling);
            return parent->right;
        }
        
        node_type* delete_fixup_case4(node_type* node, node_type* sibling, node_type* parent)
        {
            sibling->color = parent->color;
            parent->color = RedBlackColor::black;
            if(parent->right == sibling)
            {
                sibling->right->color = RedBlackColor::black;
                left_rotation(parent);
            }
            else
            {
                sibling->left->color = RedBlackColor::black;
                right_rotation(parent);
            }
            return root;
        }

        node_type* lookup_sibling(node_type* node, node_type* parent) const
        {
            if(parent->left == node)
            {
                return parent->right;
            }
            return parent->left;
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

        node_type* lookup_maximum(node_type* position) const
        {
            while(position->right) 
            {
                position = position->right;
            }
            return position;
        }

        void insert_fixup(node_type* position)
        {
            while(is_node_red(position->parent)) 
            {
                node_type* uncle{lookup_uncle(position)};
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
            root->color = RedBlackColor::black;
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
        
        node_type* lookup_uncle(node_type* node)
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

        bool is_node_red(node_type* node) const noexcept
        {
            if(node == nullptr)
            {
                return false;    
            }
            return node->color == RedBlackColor::red;;
        }

        bool is_left_child(node_type* node) const noexcept
        {
            return node->parent->left == node;
        }

        //remove
        void print_node(node_type* node) const
        {   
            std::println("{}|{}~{}~{}|{}~{}~{}",
                         static_cast<void*>(node), node->key, node->data, 
                         static_cast<size_type>(node->color), static_cast<void*>(node->parent), 
                         static_cast<void*>(node->left), static_cast<void*>(node->right));
        }
        //remove

        node_type* root;
        allocator_type alloc;
        key_compare compare;
    };
}   
#endif