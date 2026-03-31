#include "tree234.h"
#include <cassert>
#include <sstream>
#include <stdexcept>

namespace Tree234Namespace {

    template<typename T>
    Node<T>::Node() {
        itemCount = 0;

        for (int i = 0; i < 3; ++i) {
            items[i] = T{};
        }

        for (int i = 0; i < 4; ++i) {
            children[i] = nullptr;
        }
    }

    template<typename T>
    bool Node<T>::contains(T item) const {
        int i = 0;

        while (i < itemCount && items[i] <= item) {
            if (items[i] == item) {
                return true;
            }

            ++i;
        }

        if (isLeaf()) {
            return false;
        }

        return children[i]->contains(item);
    }

    template<typename T>
    T Node<T>::findMax() const {
        const Node<T>* node = this;

        while (!node->isLeaf()) {
            node = node->children[node->itemCount];
        }

        return node->items[node->itemCount - 1];
    }

    template<typename T>
    T Node<T>::findMin() const {
        const Node<T>* node = this;

        while (!node->isLeaf()) {
            node = node->children[0];
        }

        return node->items[0];
    }

    template<typename T>
    void Node<T>::fixChild(int idx) {
        bool hasLeft;
        bool hasRight;

        hasLeft = idx > 0;
        hasRight = idx < itemCount;

        if (hasLeft && children[idx - 1]->itemCount > 1) {
            rotateRight(idx);
        }
        else if (hasRight && children[idx + 1]->itemCount > 1) {
            rotateLeft(idx);
        }
        else if (hasRight) {
            mergeChildren(idx);
        }
        else {
            mergeChildren(idx - 1);
        }
    }

    template<typename T>
    void Node<T>::free() {
        if (!isLeaf()) {
            for (int i = 0; i <= itemCount; ++i) {
                children[i]->free();
            }
        }

        delete this;
    }

    template<typename T>
    void Node<T>::insertNonFull(T item) {
        if (isLeaf()) {
            int i = itemCount - 1;

            while (i >= 0 && item < items[i]) {
                items[i + 1] = items[i];
                --i;
            }

            items[i + 1] = item;
            itemCount++;
        } else {
            int i = itemCount - 1;

            while (i >= 0 && item < items[i]) {
                --i;
            }

            int childIdx = i + 1;

            if (children[childIdx]->isFull()) {
                splitChild(childIdx);

                if (item > items[childIdx]) {
                    childIdx++;
                }
            }

            children[childIdx]->insertNonFull(item);
        }
    }

    template<typename T>
    bool Node<T>::isFull() const {
        return itemCount == 3;
    }

    template<typename T>
    bool Node<T>::isLeaf() const {
        return children[0] == nullptr;
    }

    template<typename T>
    void Node<T>::mergeChildren(int idx) {
        Node<T>* left;
        Node<T>* right;
        int base;

        left = children[idx];
        right = children[idx + 1];

        left->items[left->itemCount] = items[idx];
        base = left->itemCount + 1;

        for (int k = 0; k < right->itemCount; ++k) {
            left->items[base + k] = right->items[k];
        }

        if (!right->isLeaf()) {
            for (int k = 0; k <= right->itemCount; ++k) {
                left->children[base + k] = right->children[k];
            }
        }

        left->itemCount = base + right->itemCount;

        for (int k = idx; k < itemCount - 1; ++k) {
            items[k] = items[k + 1];
            children[k + 1] = children[k + 2];
        }

        children[itemCount] = nullptr;
        itemCount--;

        delete right;
    }

    template<typename T>
    void Node<T>::removeRec(T item) {
        int i = 0;

        while (i < itemCount && item > items[i]) {
            i++;
        }

        if (i < itemCount && items[i] == item) {
            if (isLeaf()) {
                for (int k = i; k < itemCount - 1; ++k) {
                    items[k] = items[k + 1];
                }

                itemCount--;
            }
            else if (children[i]->itemCount > 1) {
                T pred = children[i]->findMax();
                items[i] = pred;
                children[i]->removeRec(pred);
            }
            else if (children[i + 1]->itemCount > 1) {
                T succ = children[i + 1]->findMin();
                items[i] = succ;
                children[i + 1]->removeRec(succ);
            }
            else {
                mergeChildren(i);
                children[i]->removeRec(item);
            }
        } else {
            if (isLeaf()) {
                return;
            }

            if (children[i]->itemCount == 1) {
                fixChild(i);

                i = 0;
                while (i < itemCount && item > items[i]) {
                    i++;
                }

                if (i < itemCount && items[i] == item) {
                    removeRec(item);
                    return;
                }
            }

            children[i]->removeRec(item);
        }
    }

    template<typename T>
    void Node<T>::rotateRight(int idx) {
        Node<T>* child;
        Node<T>* leftSib;

        child   = children[idx];
        leftSib = children[idx - 1];

        for (int k = child->itemCount - 1; k >= 0; --k) {
            child->items[k + 1] = child->items[k];
        }

        if (!child->isLeaf()) {
            for (int k = child->itemCount; k >= 0; --k) {
                child->children[k + 1] = child->children[k];
            }
        }

        child->items[0] = items[idx - 1];
        child->children[0] = leftSib->children[leftSib->itemCount];
        child->itemCount++;

        items[idx - 1] = leftSib->items[leftSib->itemCount - 1];
        leftSib->children[leftSib->itemCount] = nullptr;
        leftSib->itemCount--;
    }

    template<typename T>
    void Node<T>::rotateLeft(int idx) {
        Node<T>* child;
        Node<T>* rightSib;

        child = children[idx];
        rightSib = children[idx + 1];

        child->items[child->itemCount] = items[idx];
        child->children[child->itemCount + 1] = rightSib->children[0];
        child->itemCount++;

        items[idx] = rightSib->items[0];

        for (int k = 0; k < rightSib->itemCount - 1; ++k) {
            rightSib->items[k] = rightSib->items[k + 1];
            rightSib->children[k] = rightSib->children[k + 1];
        }

        rightSib->children[rightSib->itemCount - 1] = rightSib->children[rightSib->itemCount];
        rightSib->children[rightSib->itemCount] = nullptr;
        rightSib->itemCount--;
    }

    template<typename T>
    void Node<T>::splitChild(int childIdx) {
        Node<T>* child;
        Node<T>* right;
        T midKey;

        child = children[childIdx];
        right = new Node<T>();

        right->itemCount = 1;
        right->items[0] = child->items[2];

        if (!child->isLeaf()) {
            right->children[0] = child->children[2];
            right->children[1] = child->children[3];
            child->children[2] = nullptr;
            child->children[3] = nullptr;
        }

        midKey = child->items[1];
        child->itemCount = 1;

        for (int i = itemCount - 1; i >= childIdx; --i) {
            items[i + 1] = items[i];
        }

        for (int i = itemCount; i > childIdx; --i) {
            children[i + 1] = children[i];
        }

        items[childIdx] = midKey;
        children[childIdx + 1] = right;
        itemCount++;
    }

    template<typename T>
    std::string Node<T>::toString() const {
        std::ostringstream oss;

        oss << "(";

        for (int i = 0; i < itemCount - 1; ++i) {
            oss << items[i] << " " ;
        }
        oss << items[itemCount - 1];

        if (!isLeaf()) {
            for (int i = 0; i < itemCount; ++i) {
                    oss << " " << children[i]->toString();
            }
            oss << " " << children[itemCount]->toString();
        }

        oss << ")";

        return oss.str();
    }

    template<typename T>
    Tree234<T>::Tree234() : root(nullptr), count(0) {}

    template<typename T>
    Tree234<T>::~Tree234() {
        if (root != nullptr) {
            root->free();
        }
    }

    template<typename T>
    void Tree234<T>::clear() {
        if (root != nullptr) {
            root->free();
        }

        root  = nullptr;
        count = 0;
    }

    template<typename T>
    bool Tree234<T>::contains(T item) const {
        if (root == nullptr) {
            return false;
        }

        return root->contains(item);
    }

    template<typename T>
    void Tree234<T>::insert(T item) {
        if (contains(item)) {
            throw std::invalid_argument("Duplicate item");
        }

        if (root == nullptr) {
            root = new Node<T>();
            root->items[0] = item;
            root->itemCount = 1;
            count++;
            return;
        }

        if (root->isFull()) {
            Node<T>* newRoot     = new Node<T>();
            newRoot->children[0] = root;
            root = newRoot;
            root->splitChild(0);
        }

        root->insertNonFull(item);
        count++;
    }

    template<typename T>
    void Tree234<T>::remove(T item) {
        if (!contains(item)) {
            throw std::out_of_range("Key not found");
        }

        root->removeRec(item);
        --count;

        if (root->itemCount == 0) {
            Node<T>* oldRoot = root;

            if (!root->isLeaf()) {
                root = root->children[0];
                oldRoot->children[0] = nullptr;
            }
            else {
                root = nullptr;
            }

            delete oldRoot;
        }
    }

    template<typename T>
    int Tree234<T>::size() const {
        return count;
    }

    template<typename T>
    std::string Tree234<T>::toString() const {
        if (root == nullptr) {
            return "()";
        }

        return root->toString();
    }
}
