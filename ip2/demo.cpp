#include "tree234.h"
#include <iostream>

using namespace Tree234Namespace;

int main() {
    Tree234<int> intTree;
    Tree234<std::string> stringTree;

    // Demo with integers
    for (int v : {50, 20, 80, 10, 30, 70, 90, 5, 60, 40}) {
        intTree.insert(v);
    }

    std::cout << "After inserts:  " << intTree.toString() << "\n";
    std::cout << "Size: " << intTree.size() << "\n";

    std::cout << "contains(30): " << std::boolalpha << intTree.contains(30) << "\n";
    std::cout << "contains(99): " << intTree.contains(99) << "\n";

    intTree.remove(50);
    intTree.remove(10);
    std::cout << "After remove 50,10: " << intTree.toString() << "\n";
    std::cout << "Size: " << intTree.size() << "\n";

    try { intTree.insert(30); }
    catch (const std::invalid_argument& e) { std::cout << "Caught: " << e.what() << "\n"; }

    try { intTree.remove(999); }
    catch (const std::out_of_range& e) { std::cout << "Caught: " << e.what() << "\n"; }

    intTree.clear();
    std::cout << "After clear: " << intTree.toString() << ", size=" << intTree.size() << "\n";

    // Demo with Strings
    stringTree.insert("banana");
    stringTree.insert("apple");
    stringTree.insert("cherry");
    std::cout << "String tree: " << stringTree.toString() << "\n";


    return 0;
}
