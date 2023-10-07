/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

#include <iostream>
#include <string>
#include <sstream>
#include "AVL.h"

using namespace std;


bool isValidUFID(int ufid) {
    if (ufid < 0) {
        return false; // UFID cannot be negative
    }

    int countDigits = 0;
    while (ufid > 0) {
        ufid /= 10;
        countDigits++;
    }

    return countDigits == 8; // UFID must have exactly 8 digits
}

bool isValidName(const string& name) {
    for (char c : name) {
        if (!isalpha(c)) {
            return false; // Name should only contain alphabet letters
        }
    }

    return true;
}


int main() {
    int numCommands=0;
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
            int ufid=0;
            inStream >> name;
            // Remove the quotation marks from the name
            name = name.substr(1, name.length() - 2);
            inStream >> ufid;

            if(isValidName(name) && isValidUFID(ufid))
                tree.insert(name, ufid);
            else
                cout << "unsuccessful" << endl;
        }
        else if (command == "search") {
            string searchTerm;
            inStream >> searchTerm;

            // Try to parse the searchTerm as an integer (UFID)
            stringstream numStream(searchTerm);
            int ufid=0;
            if (numStream >> ufid) {
                // Successfully parsed as an integer, search by UFID
                if(isValidUFID(ufid))
                    tree.search(ufid);
                else
                    cout << "unsuccessful" << endl;
            } else {
                // Failed to parse as an integer, search by name
                searchTerm = searchTerm.substr(1, searchTerm.length() - 2);
                if(isValidName(searchTerm))
                    tree.search(searchTerm);
                else
                    cout << "unsuccessful" << endl;
            }
        }
        else if(command == "printLevelCount"){
            tree.printLevelCount();
        }
        else if(command == "printInorder"){
            tree.printInorder();
        }
        else if(command == "remove"){
            // gotta make sure that the id length is strictly 8 characters
            int ufid=0;
            inStream >> ufid;
            if(isValidUFID(ufid))
                tree.remove(ufid);
            else
                cout << "unsuccessful" << endl;
        }
        else if(command == "removeInorder"){
            // index is the displacement 0-based
            // ie. abc, def, ghi, jkl
            // removeInorder(2) will remove ghi
            int index=0;
            inStream >> index;
            tree.removeInorder(index);
        }
        else if(command == "printPreorder"){
            tree.printPreorder();
        }
        else if(command == "printPostorder"){
            tree.printPostorder();
        }
    }

    return 0;
}