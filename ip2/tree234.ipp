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
    void Tree234<T>::insert_val(T item) {
        //TODO
    }

    template<typename T>
    void Tree234<T>::delete_val(T item) {
        //TODO
    }

    template<typename T>
    bool Tree234<T>::contains_val(T item) {
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
    bool Node<T>::is_full() {
        return count == 3;
    }

    template<typename T>
    bool Node<T>::is_leaf() {
        return children[0] == nullptr;
    }
}
