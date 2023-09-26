//
// Created by Ismael Maura on 9/18/23.
//

#include "AVL.h"

Node::Node(string name, int ufid) {
    this->name = name;
    this->ufid = ufid;
    this->left = nullptr;
    this->right = nullptr;
}

void AVL::insert(string name, int ufid) {
    insertRecursive(root, name, ufid);
}

Node *AVL::insertRecursive(Node *node, string name, int ufid) {
    if (!node){
        root = new Node(name, ufid);
        return root;
    }
    if (ufid < node->ufid){
        insertRecursive(node->left, name, ufid);
    }
    else if (ufid > node->ufid){
        insertRecursive(node->right, name, ufid);
    }
    return node;
}
