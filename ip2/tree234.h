#ifndef TREE234_H
#define TREE234_H

namespace Tree234Namespace {
    template<typename T>
    class Tree234 {
        public:
            using value_type = T;
            using reference = T &;
            using const_reference = const T &;
        private:
            T temp_val;
        public:
            Tree234();
            ~Tree234();
            void insert_val(T item);
            void delete_val(T item);
            bool contains_val(T item);
    };
}

#include "tree234.ipp"
#endif
