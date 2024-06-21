#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <cstdint>
#include <iostream>
#include <queue>

namespace algo
{
    enum class node_color : std::uint8_t
    {
        red,
        black,
        max_colors,
    };
    
    template<typename Type, typename Key>
    struct red_black_tree_node
    {   
        red_black_tree_node(const node_color color, const Key& key, const Type& value)
            : color{color}, key{key}
            , value{value}
        {
        }
        red_black_tree_node* left;
        red_black_tree_node* right;
        red_black_tree_node* parent;
        node_color color;
        const Key key;
        Type value;
    };

    template<typename Type, typename Key, typename Compare>
    class red_black_tree
    {
    public:
        
        using node_type = red_black_tree_node<Type, Key>;
        using key_compare = Compare;

        red_black_tree()
            : root{nullptr}
        {
        }

        red_black_tree(const red_black_tree& that) = delete;
    
        red_black_tree(red_black_tree&& that) = delete;

        red_black_tree& operator=(const red_black_tree&& that) = delete;

        red_black_tree& operator=(red_black_tree&& that) = delete;

        node_type** find(const Key& key)
        {
            for(node_type* element{root}; element != nullptr; )
            {
                if(key_compare{}(key, element->key))
                {
                }
                else if(key_compare{}(element->key, key))
                {
                }
                else
                {
                    return &element;
                }
            }
        }

        void insert(const Key& key, const Type& value)
        {

        }

        void print()
        {
            std::queue<node_type*> tree{root};
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
