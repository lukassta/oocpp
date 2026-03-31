#ifndef TREE234_H
#define TREE234_H

#include <string>

namespace Tree234Namespace {
    template<typename T>
    class Node {
    private:
        T items[3];
        Node* children[4];
        int itemCount;

    public:
        Node();

        bool contains(T item) const;
        void fixChild(int idx);
        void free();
        void insertNonFull(T item);
        bool isFull() const;
        bool isLeaf() const;
        void removeRec(T item);
        void splitChild(int childIdx);
        std::string toString() const;

    private:
        T findMax() const;
        T findMin() const;
        void mergeChildren(int idx);
        void rotateLeft(int idx);
        void rotateRight(int idx);

        template<typename U> friend class Tree234;
    };

    template<typename T>
    class Tree234 {
    private:
        Node<T>* root;
        int count;

    public:
        Tree234();
        ~Tree234();

        void clear();
        bool contains(T item) const;
        void insert(T item);
        void remove(T item);
        int size() const;
        std::string toString() const;
    };
}

#include "tree234.cpp"
#endif
