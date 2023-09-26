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

//  for debugging purposes
void Node::print() {
    cout << "\nName: " << name << endl;
    cout << "ufid: " << ufid << endl;
    cout << "height: " << height << endl;
    if(!left)
        cout << "left: nullptr"<< endl;
    else
        cout << "left: " << left->name << endl;
    if(!right)
        cout << "right: nullptr"<< endl;
    else
        cout << "right: " << right->name << endl;

}

void AVL::insert(string name, int ufid) {
    insertNode(nodeZero, name, ufid);
}

Node *AVL::insertNode(Node *root, string name, int ufid) {
    if (!root){
        Node* node = new Node(name, ufid);
        lookForBugs.push_back(node);

        if(!nodeZero){
            // keep a reference to the root of the tree
            nodeZero = node;
        }

        cout << "successful" << endl;
        return node;
    }
    if (ufid < root->ufid){
        root->left = insertNode(root->left, name, ufid);
    }
    else if (ufid > root->ufid){
        root->right = insertNode(root->right, name, ufid);
    }
    else {
        // the id is not unique
        // must return the pointer to the element that already had the duplicate id
        cout << "unsuccessful" << endl;
        return root;
    }

    // set the root's height
    int heightL=0, heightR = 0;
    if(root->left)
        heightL = root->left->height;
    if(root->right)
        heightR = root->right->height;
    root->height = 1+max(heightL, heightR);

    // perform AVL balancing operations
    // balance factor = heightL - heightR
    // a node is imbalanced if -1 > bf > 1
    int bf = heightL - heightR;
    if(-1 > bf || bf > 1){

    }



    return root;
}

void AVL::debug() {
    for(auto nodes : lookForBugs){
        nodes->print();
    }
}

void AVL::rotateLeft(Node *root) {

}
