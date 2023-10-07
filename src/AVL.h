//
// Created by Ismael Maura on 9/18/23.
//
#include <iostream>
#include <queue>

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
//    void print()const;
};

class AVL {
private:
    //vector<Node*> lookForBugs;  // vector for debugging
    Node* nodeZero = nullptr;
    Node* newRootNodeAfterBalance = nullptr;
    Node* insertNode(Node* root, const string& name, int ufid);
    Node* rotateLeft(Node* root);
    Node* rotateRight(Node* root);
    Node* rotateRightLeft(Node* root);
    Node* rotateLeftRight(Node* root);
    int balanceFactor(Node* root);
    void updateHeight(Node* root);
    void balanceTree(Node* root);
    void printInorder(Node* node, vector<string>& inorder);
    void remove(Node* root, Node* parent, const int ufid);
    void removeInorder(Node* root,vector<Node*>& inorder);
    void printPreorder(Node *node, vector<string>& preorder);
    void printPostorder(Node* node, vector<string>& postorder);
public:
    void test();

    void insert(string name, int ufid);
    void search(const int ufid);

    void search(const string& name);
    void printLevelCount();
    void printInorder();
    void remove(const int ufid);
    void removeInorder(const int index);
    void printPreorder();
    void printPostorder();

    //void debug() const;
};


#endif //AVL_AVL_H
