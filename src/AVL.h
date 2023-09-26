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
};

class AVL {
private:
    Node* insertRecursive(Node* node, string name, int ufid);
public:
    Node* root = nullptr;
    void insert(string name, int ufid);
};


#endif //AVL_AVL_H
