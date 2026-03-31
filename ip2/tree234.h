#ifndef TREE234_H
#define TREE234_H

namespace Tree234Namespace {
    template<typename T>
    class Node {
    private:
        T items[3];
        Node<T>* children[4];
        int count = 0;

    public:
        Node(T item);
        bool is_full();
        bool is_leaf();
    };

    template<typename T>
    class Tree234 {
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
    private:
        Node<T>* root;
    public:
        Tree234();
        ~Tree234();
        void insert_val(T item);
        void delete_val(T item);
        bool contains_val(T item);
    };
};

#include "tree234.ipp"
#endif
