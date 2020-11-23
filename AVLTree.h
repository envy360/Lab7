#ifndef AVLTREE_H
#define AVLTREE_H

#include <fstream>
#include <string>

using namespace std;

typedef struct Node {
    string data;
    unsigned int height;
    unsigned int count;  // Increment if the same data is inserted.
    int balanceFactor;  // Increment if the same data is inserted.
    Node* left;
    Node* right;
    Node* parent;

    Node(const string &data)
            : data(data), height(0), count(1), balanceFactor(0), left(nullptr), right(nullptr), parent(nullptr) {}
} Node;

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(const string &val);
    void visualizeTree(const string &val) const;
    int balanceFactor(Node *node) const;
    void printBalanceFactors() const;

private:
    Node *root_;

    void rotate(Node *node, const string &val);
    Node *rotateLeft(Node *node);
    Node *rotateRight(Node *node);
    void visualizeTree(ofstream &, Node *node) const;
    Node *findUnbalancedNode(Node *node, const string &val) const;
    void printBalanceFactors(Node *node) const;
};

#endif