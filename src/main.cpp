/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

#include <iostream>
#include <string>
#include <sstream>
#include "AVL.h"

using namespace std;

int main() {
    int numCommands;
    cin >> numCommands;
    cin.ignore(); // Ignore the newline character

    AVL tree;

    for (int i = 0; i < numCommands; i++) {
        string line;
        getline(cin, line);
        istringstream inStream(line);

        string command;
        inStream >> command;

        string name;
        int ufid;

        if (command == "insert") {
            inStream >> name;
            inStream >> ufid;
            tree.insert(name, ufid);
        }
        else if (command == "search") {
//            string searchTerm;
//            inStream >> searchTerm;
//            if (tree.search(searchTerm)) {
//                cout << searchTerm << " found in the AVL tree." << endl;
//            } else {
//                cout << searchTerm << " not found in the AVL tree." << endl;
//            }
        }
    }

    return 0;
}