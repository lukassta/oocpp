#ifndef TREE234_H
#define TREE234_H

#include <string>

namespace Tree234Namespace {
    template<typename T>
    class Node {
    private:
        T items[3];
        Node<T>* children[4];
        int count = 0;

    public:
        Node(T item);
        bool isFull();
        bool isLeaf();
        std::string toString();
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
        void insertVal(T item);
        void deleteVal(T item);
        bool containsVal(T item);
        std::string toString();
    };
};

#include "tree234.ipp"
#endif
