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

        // Remove any leading and trailing whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        istringstream inStream(line);

        string command;
        inStream >> command;


        if (command == "insert") {
            string name;
            int ufid;
            inStream >> name;
            // Remove the quotation marks from the name
            name = name.substr(1, name.length() - 2);
            inStream >> ufid;
            tree.insert(name, ufid);
        }
        else if (command == "search") {
            string searchTerm;
            inStream >> searchTerm;

            // Try to parse the searchTerm as an integer (UFID)
            stringstream numStream(searchTerm);
            int ufid;
            if (numStream >> ufid) {
                // Successfully parsed as an integer, search by UFID
                tree.search(ufid);
            } else {
                // Failed to parse as an integer, search by name
                searchTerm = searchTerm.substr(1, searchTerm.length() - 2);
                tree.search(searchTerm);
            }
        }
        else if(command == "printLevelCount"){
            tree.printLevelCount();
        }
        else if(command == "printInorder"){
            tree.printInorder();
        }
    }

    return 0;
}