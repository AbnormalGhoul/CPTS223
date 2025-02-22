//MA2 BSTs
#include <iostream>
#include "BST.h"

int main() {
    // Creates a BST string tree (bst_test)
    BST<string> bst_test;
    bst_test.add("C");
    bst_test.add("p");
    bst_test.add("t");
    bst_test.add("s");
    bst_test.add("2");
    bst_test.add("3");
    bst_test.add("B");
    bst_test.add("S");
    bst_test.add("T");

    // Test1: Tests printLevelOrder()
    cout << "In-order print: ";
    bst_test.printInOrder();
    cout << endl;

    cout << "Level-order print: ";
    bst_test.printLevelOrder();
    cout << endl;

    cout << "Post-order print: ";
    bst_test.printPostOrder();
    cout << endl;

    cout << "Pre-order print: ";
    bst_test.printPreOrder();
    cout << endl;

    // Test2: Tests copy constructor -1
    BST<string> bst_copy1(bst_test);
    if (bst_copy1.size() == bst_test.size() && bst_copy1.contains("B") && bst_copy1.contains("S") && bst_copy1.contains("T")) {
        cout << "Copy constructor test-1 passed!" << endl;
    } else {
        cout << "Copy constructor test-1 failed!" << endl;
        cout << "bst_test: ";
        bst_test.printLevelOrder();
        cout << "bst_copy1: ";
        bst_copy1.printLevelOrder();
    }

    // Test3: Tests copy constructor - 2
    bst_copy1.getNode("B")->setValue("A");
    if (bst_test.contains("B") && !bst_test.contains("A")) {
        cout << "Copy constructor test-2 passed!" << endl;
    } else {
        cout << "Copy constructor test-2 failed!" << endl;
        cout << "bst_test: ";
        bst_test.printLevelOrder();
    }

    // Test4: Tests copy assignment
    BST<string> bst_copy2;
    bst_copy2 = bst_test;
    if (bst_copy2.size() == bst_test.size() && bst_copy2.contains("B") && bst_copy2.contains("S") && bst_copy2.contains("T")) {
        cout << "Copy assignment operator test passed!" << endl;
    } else {
        cout << "Copy assignment operator test failed!" << endl;
        cout << "bst_test: ";
        bst_test.printLevelOrder();
        cout << "bst_copy2: ";
        bst_copy2.printLevelOrder();
    }

    // Test5: Tests move constructor
    BST<string> bst_move1(std::move(bst_test));
    if (bst_move1.size() == 9 && bst_move1.contains("B") && bst_move1.contains("S") && bst_move1.contains("T") && bst_test.empty()) {
        cout << "Move constructor test passed!" << endl;
    } else {
        cout << "Move constructor test failed!" << endl;
        cout << "bst_move1: ";
        bst_move1.printLevelOrder();
    }

    // Test6: Tests move assignment
    BST<string> bst_move2;
    bst_move2 = BST<string>({"B", "S", "T"});
    if (bst_move2.size() == 3 && bst_move2.contains("B") && bst_move2.contains("S") && bst_move2.contains("T")) {
        cout << "Move assignment operator test passed!" << endl;
    } else {
        cout << "Move assignment operator test failed!" << endl;
        cout << "bst_move2: ";
        bst_move2.printLevelOrder();
    }

    return 0;
}