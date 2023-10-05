/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

#include <iostream>
#include <string>
#include "AVL.h"

using namespace std;

int main() {
    AVL tree;

    tree.insert("4", 4);
    tree.insert("7", 7);
    tree.insert("10", 10);
    tree.insert("12", 12);
    tree.insert("11", 11);
    tree.insert("15", 15);
    tree.insert("13", 13);
    tree.insert("8", 8);
    tree.insert("9", 9);
    tree.insert("2", 2);
    tree.insert("1", 1);
    tree.insert("18", 18);
    tree.insert("20", 20);
    tree.insert("30", 30);
    tree.insert("19", 19);
    tree.insert("50", 50);
    tree.insert("50", 51);
    tree.insert("50", 52);
    tree.insert("50", 53);
    tree.insert("50", 54);
    tree.insert("50", 55);
    tree.insert("50", 56);
    tree.insert("50", 57);
    tree.insert("50", 58);
    tree.insert("50", 59);
    tree.insert("50", 60);

    tree.debug();

    return 0;
}
