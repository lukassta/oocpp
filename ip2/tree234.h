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

        bool isFull() const;
        bool isLeaf() const;

        void splitChild(int childIdx);
        void insertNonFull(T item);
        bool contains(T item) const;
        void removeRec(T item);
        void fixChild(int idx);

        std::string toString() const;
        void free();

    private:
        void rotateRight(int idx);
        void rotateLeft(int idx);
        void mergeChildren(int idx);
        T findMax() const;
        T findMin() const;

        template<typename U> friend class Tree234;
    };

    template<typename T>
    class Tree234 {
    public:
        Tree234();
        ~Tree234();

        void insert(T item);
        void remove(T item);
        bool contains(T item) const;
        void clear();
        int size() const;
        std::string toString() const;

    private:
        Node<T>* root;
        int count;
    };
}

#include "tree234.cpp"
#endif
