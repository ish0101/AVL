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
    void print();
};

class AVL {
private:
    vector<Node*> lookForBugs;  // vector for debugging
    Node* nodeZero = nullptr;
    Node* insertNode(Node* root, string name, int ufid);
    void rotateLeft(Node* root);
public:

    void insert(string name, int ufid);
    void debug();
};


#endif //AVL_AVL_H
