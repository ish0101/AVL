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
const void Node::print() const{
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

Node *AVL::insertNode(Node *root, const string& name, int ufid) {
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

    // right heavy
    if(balanceFactor(root)<=-1){
        if(balanceFactor(root->right) >= 1){ // if tree's right subtree is left heavy
            // perform right-left rotation, update height
            rotateRightLeft(root);
        }
        else{ // right subtree is right heavy
            // perform left-left rotation, update height
            rotateLeft(root);
        }
    }
//    // left heavy
//    else if(balanceFactor(root)>1){
//        rotateLeftRight(root);
//        updateHeight(root);
//        if(balanceFactor(root->left)<-1){
//            // if left subtree is right heavy
//            // perform left right rotation, update height
//        }
//        else{
//            rotateLeft(root);
//        }
//    }
    updateHeight(root);

    return root;
}

const void AVL::debug() const {
    for(auto nodes : lookForBugs){
        nodes->print();
    }
}

// right-right case (right heavy)
// left rotation
Node* AVL::rotateLeft(Node *root) {
    Node* grandchild  = root->right->left;
    Node* newParent = root->right;
    newParent->left = root;
    root->right = grandchild;
    return newParent;
}

Node *AVL::rotateRight(Node *root) {
    Node* grandchild = root->left->right;
    Node* newParent = root->left;
    newParent->right = root;
    root->left = grandchild;
    return newParent;
}

Node *AVL::rotateRightLeft(Node *root) {
    Node* newParent = root->left->left;
    Node* rootLeftChild = root->left;
    root->left->left = newParent->left;
    root->left = newParent->left;
    newParent->left = rootLeftChild;
    newParent->left = root;
    return newParent;
}

Node *AVL::rotateLeftRight(Node *root) {
    Node* newParent = root->left->right;
    Node* rootLeftChild = root->left;
    root->left->right = newParent->left;
    root->left = newParent->right;
    newParent->left = rootLeftChild;
    newParent->right = root;
    return newParent;
}

int AVL::balanceFactor(Node *root) {
    // calculate root's height
    int heightL=0, heightR = 0;
    if(root->left)
        heightL = root->left->height;
    if(root->right)
        heightR = root->right->height;
    root->height = 1+max(heightL, heightR);

    // perform AVL balancing operations
    // balance factor = heightL - heightR
    // a node is imbalanced if -1 > bf > 1
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
