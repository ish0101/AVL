//
// Created by Ismael Maura on 9/18/23.
//
#include <iostream>

#ifndef AVL_AVL_H
#define AVL_AVL_H

using namespace std;

struct Node {
    string name = "";
    int ufid = 0;
    int height = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    // constructor
    Node() = default;
    Node(string name, int ufid);
    void print()const;
};

class AVL {
private:
    vector<Node*> lookForBugs;  // vector for debugging
    Node* nodeZero = nullptr;
    Node* insertNode(Node* root, const string& name, int ufid);
    Node* rotateLeft(Node* root);
    Node* rotateRight(Node* root);
    Node* rotateRightLeft(Node* root);
    Node* rotateLeftRight(Node* root);
    int balanceFactor(Node* root);
    void updateHeight(Node* root);
    void balanceTree(Node* root);
public:

    void insert(string name, int ufid);
    void debug() const;
};


#endif //AVL_AVL_H
