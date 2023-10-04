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

//    tree.insert("ish", 10);
//    tree.insert("charlie", 15);
//    tree.insert("Stevie", 12);
//    tree.insert("adele", 7);
//    tree.insert("laurie",3);
//    tree.insert("blue",4);
//    tree.insert("adkins",5);


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

    cout << "hello";
//    tree.insert("a", 1);
//    tree.insert("b", 8);
//    tree.insert("c", 6);

    tree.debug();

    return 0;
}
