//
// Created by Ismael Maura on 9/18/23.
//

#include "AVL.h"

Node::Node(string name, int ufid) {
    this->name = name;
    this->ufid = ufid;
    height = 0;
    this->left = nullptr;
    this->right = nullptr;
}

void AVL::insert(string name, int ufid) {
    // input validation
    insertNode(nodeZero, name, ufid);
}

Node *AVL::insertNode(Node *root, const string& name, int ufid) {
    if (!root){
        Node* node = new Node(name, ufid);
        //lookForBugs.push_back(node);

        if(!nodeZero){
            // keep a pointer to the root of the tree
            nodeZero = node;
        }
        cout << "successful" << endl;
        return node;
    }
    if (ufid < root->ufid){
        root->left = insertNode(root->left, name, ufid);
        if(newRootNodeAfterBalance){
            // point to the new parent node after rotation
            root->left = newRootNodeAfterBalance;
            newRootNodeAfterBalance = nullptr;
        }
    }
    else if (ufid > root->ufid){
        root->right = insertNode(root->right, name, ufid);
        if(newRootNodeAfterBalance){
            // point to the new parent node after rotation
            root->right = newRootNodeAfterBalance;
            newRootNodeAfterBalance = nullptr;
        }
    }
    else {
        // the id is not unique
        cout << "unsuccessful" << endl;
        return root;
    }

    updateHeight(root);
    // balance the tree if it is imbalanced
    int bf = balanceFactor(root);
    if (bf > 1 || bf < -1) {
        balanceTree(root);
    }
    return root;
}

void AVL::balanceTree(Node* root) {
    int bf = balanceFactor(root);
    // right heavy
    if(bf<-1){
        // if tree's right subtree is left heavy
        if(balanceFactor(root->right) > 0){
            // perform right-left rotation, update height
            rotateRightLeft(root);
            updateHeight(root);
        }
        // right subtree is right heavy
        else{
            rotateLeft(root);
            updateHeight(root);
        }
    }
    // left heavy
    else if(bf>1){
        // if tree's left subtree is right heavy
        if(balanceFactor(root->left) < 0){
            // perform left-right rotation, update height
            rotateLeftRight(root);
            updateHeight(root);
        }
        // left subtree is left heavy
        else{
            rotateRight(root);
            updateHeight(root);
        }
    }
}

int AVL::balanceFactor(Node *root) {
    // calculate root's height
    int heightL=0, heightR = 0;
    if(root->left)
        heightL = root->left->height+1;
    if(root->right)
        heightR = root->right->height+1;
    return (heightL - heightR);
}

void AVL::updateHeight(Node *root) {
    int heightL=0, heightR = 0;
    if(root->left)
        heightL = root->left->height;
    if(root->right)
        heightR = root->right->height;
    root->height = 1+max(heightL, heightR);
    // leaf node's height
    if(!root->left && !root->right){
        root->height = 0;
    }
}

// right-right case (right heavy)
// left rotation
Node* AVL::rotateLeft(Node *root) {
    Node* grandchild  = root->right->left;
    Node* newParent = root->right;
    newParent->left = root;
    root->right = grandchild;

    if(root == nodeZero){
        nodeZero = newParent;
//        cout << "nodeZero = " << nodeZero->name << endl;
    }
    else{
        updateHeight(newParent->left);
        updateHeight(newParent->right);
        updateHeight(newParent);
        newRootNodeAfterBalance = newParent;
    }
    return newParent;
}

Node *AVL::rotateRight(Node *root) {
    Node* grandchild = root->left->right;
    Node* newParent = root->left;
    newParent->right = root;
    root->left = grandchild;

    if(root == nodeZero){
        nodeZero = newParent;
//        cout << "nodeZero = " << nodeZero->name << endl;
    }
    else{
        // edge case if we are at the root, we dont need to
        // point previous node to the new node, (there is no previous node)
        updateHeight(newParent->left);
        updateHeight(newParent->right);
        updateHeight(newParent);
        newRootNodeAfterBalance = newParent;
    }
    return newParent;
}

Node *AVL::rotateRightLeft(Node *root) {
    Node* newParent = root->right->left;
    Node* rootRightChild = root->right;
    root->right = newParent->left;
    rootRightChild->left = newParent->right;
    newParent->left = root;
    newParent->right = rootRightChild;
    if(root == nodeZero){
        nodeZero = newParent;
//        cout << "nodeZero = " << nodeZero->name << endl;
    }
    else{
        updateHeight(newParent->right);
        updateHeight(newParent->left);
        updateHeight(newParent);
        newRootNodeAfterBalance = newParent;
    }
    return newParent;
}

Node *AVL::rotateLeftRight(Node *root) {
    Node* newParent = root->left->right;
    Node* rootLeftChild = root->left;
    root->left = newParent->right;
    rootLeftChild->right = newParent->left;
    newParent->right = root;
    newParent->left = rootLeftChild;
    if(root == nodeZero){
        nodeZero = newParent;
//        cout << "nodeZero = " << nodeZero->name << endl;
    }
    else{
        updateHeight(newParent->left);
        updateHeight(newParent->right);
        updateHeight(newParent);
        newRootNodeAfterBalance = newParent;
    }
    return newParent;
}

void AVL::test() {

}

// searches for a matching name and prints UFID
void AVL::search(const string &name) {
    bool notFound = true;
    queue<Node*> queue;
    if (nodeZero == nullptr){
        cout << "unsuccessful" << endl;
        return;
    }

    queue.push(nodeZero);
    while (!queue.empty()) {
        int size = queue.size();
        for (int i = 0; i < size; i++) {
            Node* node = queue.front();
            if (node->name == name){
                cout << node->ufid << endl;
                notFound = false;
            }
            queue.pop();
            if(node->left)
                queue.push(node->left);
            if(node->right)
                queue.push(node->right);
        }
    }
    if(notFound)
        cout << "unsuccessful" << endl;
}

// searches for a matching UFID and prints name
void AVL::search(const int ufid) {
    queue<Node*> queue;
    if (nodeZero == nullptr){
        cout << "unsuccessful" << endl;
        return;
    }

    queue.push(nodeZero);
    while (!queue.empty()) {
        int size = queue.size();
        for (int i = 0; i < size; i++) {
            Node* node = queue.front();
            if (node->ufid == ufid){
                cout << node->name << endl;
                return;
            }
            queue.pop();
            if(node->left)
                queue.push(node->left);
            if(node->right)
                queue.push(node->right);
        }
    }
    cout << "unsuccessful" << endl;
}

void AVL::printLevelCount() {
    cout << nodeZero->height+1 << endl;
}

// Wrapper function to start the traversal from the root
void AVL::printInorder() {
    vector<string> inorder;
    printInorder(nodeZero, inorder);
    for(int i=0; i<inorder.size(); i++){
        cout << inorder[i];
        if(i < inorder.size()-1){
            cout << ", ";
        }
    }
    cout << endl;
}

void AVL::printInorder(Node* node, vector<string>& inorder) {
    if (node == nullptr) {
        return;
    }
    printInorder(node->left, inorder);
    inorder.push_back(node->name);
    printInorder(node->right, inorder);
}

void AVL::remove(Node *root,Node* parent, const int ufid) {
    // search for node with matching UFID
    if(!root)
        return;

    if(ufid < root->ufid)
        remove(root->left, root, ufid);
    else if(ufid > root->ufid)
        remove(root->right, root, ufid);
    // found node with matching ufid
    else{
        // has two children
        if(root->left && root->right){
            // replace root with right child's leftmost node.

            // edge case (has no parent, is the root node or nodeZero)
            if(!parent){
                // find successor
                Node* successor = root->right;
                Node* successorParent = root;
                while(successor->left != nullptr){
                    if(successor->left->left == nullptr)
                        successorParent = successor;
                    successor = successor->left;
                }
                if(root->right->left == nullptr){
                    // successor is immediately to the right of root
                    nodeZero = root->right;
                    nodeZero->left = root->left;
                    delete root;
                }
                else{
                    root->ufid = successor->ufid;
                    root->name = successor->name;
                    delete successor;
                    // successor's parent should point to nullptr after
                    // it's child has been deleted.
                    successorParent->left = nullptr;
                }
                cout << "successful" << endl;
            }
            else if(parent->left == root){
                // find successor
                Node* successor = root->right;
                Node* successorParent = nullptr;
                while(successor->left != nullptr){
                    if(successor->left->left == nullptr)
                        successorParent = successor;
                    successor = successor->left;
                }
                root->ufid = successor->ufid;
                root->name = successor->name;
                delete successor;
                // successor's parent should point to nullptr after
                // it's child has been deleted.
                successorParent->left = nullptr;
                cout << "successful" << endl;
            }
            // replace root with left child's rightmost node
            else{
                // find successor
                Node* successor = root->left;
                Node* successorParent = nullptr;
                while(successor->right != nullptr){
                    if(successor->right->right == nullptr)
                        successorParent = successor;
                    successor = successor->right;
                }
                root->ufid = successor->ufid;
                root->name = successor->name;
                delete successor;
                // successor's parent should point to nullptr after
                // it's child has been deleted.
                successorParent->right = nullptr;
                cout << "successful" << endl;
            }
        }
        // has only one child
        else if((!root->left && root->right) || (root->left && !root->right)){
            if(parent->left == root){
                // find successor
                Node* successor = root->right;
                Node* successorParent = nullptr;
                while(successor->left != nullptr){
                    if(successor->left->left == nullptr)
                        successorParent = successor;
                    successor = successor->left;
                }
                root->ufid = successor->ufid;
                root->name = successor->name;
                delete successor;
                // successor's parent should point to nullptr after
                // it's child has been deleted.
                successorParent->left = nullptr;
                cout << "successful" << endl;
            }
            else if(parent->right == root){
                // find successor
                Node* successor = root->left;
                Node* successorParent = nullptr;
                while(successor->right != nullptr){
                    if(successor->right->right == nullptr)
                        successorParent = successor;
                    successor = successor->right;
                }
                root->ufid = successor->ufid;
                root->name = successor->name;
                delete successor;
                // successor's parent should point to nullptr after
                // it's child has been deleted.
                successorParent->right = nullptr;
                cout << "successful" << endl;
            }
        }
        // is a leaf node
        else if (!root->left && !root->right){
            // remove pointer to the node to be deleted
            if(parent->left == root)
                parent->left = nullptr;
            else if(parent->right == root)
                parent->right = nullptr;
            delete root;
            cout << "successful" << endl;
        }
    }
}

void AVL::remove(int ufid) {
    if(!nodeZero) {
        // empty tree edge case
        cout << "unsuccessful\n";
    }
    else
        remove(nodeZero, nullptr, ufid);
}

void AVL::removeInorder(const int index) {
    if(!nodeZero) {
        cout << "unsuccessful\n";
    }
    else{
        vector<Node*> inorder;
        removeInorder(nodeZero,inorder);
        remove(inorder[index]->ufid);
    }
}

// put all the nodes into a vector inorder traversal
void AVL::removeInorder(Node *root, vector<Node*>& inorder) {
    if (root == nullptr) {
        return;
    }
    removeInorder(root->left, inorder);
    inorder.push_back(root);
    removeInorder(root->right, inorder);
}

void AVL::printPreorder() {
    vector<string> preorder;
    printPreorder(nodeZero, preorder);
    for(int i=0; i<preorder.size(); i++){
        cout << preorder[i];
        if(i < preorder.size()-1){
            cout << ", ";
        }
    }
    cout << endl;  // Add a newline character at the end for formatting
}

void AVL::printPreorder(Node* node, vector<string>& preorder) {
    if (node == nullptr) {
        return;
    }

    preorder.push_back(node->name);
    // Recursively traverse the left subtree
    printPreorder(node->left, preorder);
    // Recursively traverse the right subtree
    printPreorder(node->right, preorder);
}


void AVL::printPostorder() {
    vector<string> postorder;
    printPostorder(nodeZero, postorder);
    for(int i=0; i<postorder.size(); i++){
        cout << postorder[i];
        if(i < postorder.size()-1){
            cout << ", ";
        }
    }
    cout << endl;  // Add a newline character at the end for formatting
}

// Post-order traversal of the AVL tree
void AVL::printPostorder(Node* node, vector<string>& postorder) {
    if (node == nullptr) {
        return;
    }

    // Recursively traverse the left subtree
    printPostorder(node->left, postorder);
    // Recursively traverse the right subtree
    printPostorder(node->right, postorder);
    // Print the current node's data
    postorder.push_back(node->name);
}

//void AVL::debug() const {
//    for(auto nodes : lookForBugs){
//        nodes->print();
//    }
//}

//  for debugging purposes
//void Node::print() const{
//    cout << "\nufid: " << ufid << endl;
//    cout << "height: " << height << endl;
//    if(!left)
//        cout << "left: nullptr"<< endl;
//    else
//        cout << "left: " << left->ufid << endl;
//    if(!right)
//        cout << "right: nullptr"<< endl;
//    else
//        cout << "right: " << right->ufid << endl;
//
//}
