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

    inline std::ostream & operator<<(std::ostream & out, RedBlackColor color) 
    {
        switch(color) 
        {
            case RedBlackColor::red: return out << "red";
            case RedBlackColor::black: return out << "black";
            default: return out << "Unimplemented enum: " << static_cast<std::uint64_t>(color);
        }
    }

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
            if(root == nullptr)
            {
                std::cout << "NULLPTR\n";
                return;
            }
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
            node_type* start{nullptr};
            node_type* parent{nullptr};
            RedBlackColor color{target->color};
            if(target->left == nullptr)
            {
                start = target->right;
                parent = target->parent;
                delete_transplant(target, target->right);
            }
            else if(target->right == nullptr)
            {
                start = target->left;
                parent = target->parent;
                delete_transplant(target, target->left);
            }
            else
            {
                color = delete_condition_case3(target, &start, &parent);
            }
            if(color == RedBlackColor::black)
            {
                delete_fixup(start, parent);
            }
        }
        
        RedBlackColor delete_condition_case3(node_type* target, node_type** start, node_type** parent)
        {
            auto found{lookup_maximum(target->left)};
            auto color{found->color};
            *start = found->left;
            *parent = found;
            if(found != target->left)
            {
                *parent = found->parent;
                delete_transplant(found, found->left);
                found->left = target->left;
                found->left->parent = found;
            }
            delete_transplant(target, found);
            found->right = target->right;
            found->right->parent = found;
            found->color = target->color;
            return color;
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
        
        void delete_fixup(node_type* start, node_type* parent)
        {
            if(parent == nullptr)
            {
                return;
            }
            bool isSiblingRight{parent->left == start};
            node_type* sibling{isSiblingRight? parent->right : parent->left};
            while(start != root 
                  && !is_node_red(start))
            {
                isSiblingRight = parent->left == start;
                sibling = isSiblingRight? parent->right : parent->left;
                if(is_node_red(sibling))
                {
                    sibling->color = RedBlackColor::black;
                    parent->color = RedBlackColor::red;
                    if(isSiblingRight)
                    {
                        left_rotation(parent);
                        sibling = parent->right;
                    }
                    else
                    {
                        right_rotation(parent);
                        sibling = parent->left;
                    }
                }
                if(sibling == nullptr)
                {
                    break;
                }
                if(!is_node_red(sibling->left)
                   && !is_node_red(sibling->right))
                {
                    sibling->color = RedBlackColor::red;
                    start = parent;
                    parent = start->parent;
                }
                else
                {
                    if((!is_node_red(sibling->right) && isSiblingRight)
                       || (!is_node_red(sibling->left) && !isSiblingRight))
                    {
                        sibling->color = RedBlackColor::red;
                        if(isSiblingRight)
                        {
                            sibling->left->color = RedBlackColor::black;
                            right_rotation(sibling);
                            sibling = parent->right;
                        }
                        else
                        {
                            sibling->right->color = RedBlackColor::black;
                            left_rotation(sibling);
                            sibling = parent->left;
                        }
                    }
                    sibling->color = parent->color;
                    parent->color = RedBlackColor::black;
                    if(isSiblingRight)
                    {
                        sibling->right->color = RedBlackColor::black;
                        left_rotation(parent);
                    }
                    else
                    {
                        sibling->left->color = RedBlackColor::black;
                        right_rotation(parent);
                    }
                    start = root;
                }
                start->color = RedBlackColor::black;
            }
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
            if(node == nullptr)
            {
                std::println("node is nullptr");
                return;
            }
            std::cout << node << "|key: " << node->key << " ~val: " << node->data << " ~color: " << node->color 
                      << "|" << node->parent << "~" << node->left << "~" << node->right << '\n';
        }
        //remove

        node_type* root;
        allocator_type alloc;
        key_compare compare;
    };
}   
#endif