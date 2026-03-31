namespace Tree234Namespace { // Tree
    template<typename T>
    Tree234<T>::Tree234()
    {
        root = nullptr;
    }

    template<typename T>
    Tree234<T>::~Tree234()
    {
    }

    template<typename T>
    void Tree234<T>::insertVal(T item) {
        //TODO
    }

    template<typename T>
    void Tree234<T>::deleteVal(T item) {
        //TODO
    }

    template<typename T>
    bool Tree234<T>::containsVal(T item) {
        return true;
        //TODO
    }

    // Node
    template<typename T>
    Node<T>::Node(T item) {
        items = {item, 0, 0};
        children = {nullptr, nullptr, nullptr, nullptr};
        count = 0;
    }

    template<typename T>
    bool Node<T>::isFull() {
        return count == 3;
    }

    template<typename T>
    bool Node<T>::isLeaf() {
        return children[0] == nullptr;
    }
}
