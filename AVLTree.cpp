#include <queue>
#include <iostream>

#include "AVLTree.h"

using namespace std;

AVLTree::AVLTree() : root_(nullptr) {}

AVLTree::~AVLTree() {
    if (root_) {
        queue<Node *> nodes;
        nodes.push(root_);
        while (!nodes.empty()) {
            Node *node = nodes.front();
            nodes.pop();
            if (node->left) nodes.push(node->left);
            if (node->right) nodes.push(node->right);
            delete node;
        }
    }
}

void AVLTree::insert(const string &val) {

    Node* node = new Node(val);

    if (root_ == nullptr) {
        root_ = node;
        return;
    }

    Node* curr = root_;
    while (curr != nullptr) {
        if ( node->data < curr->data) {
            curr->balanceFactor += 1;
            if (curr->left == nullptr) {
                // cout << node->data << " " << curr->data << endl;
                curr->left = node;
                node->parent = curr;
                curr = nullptr;
            }
            else {
                curr = curr->left;
            }
        }
        else {
            curr->balanceFactor -= 1;
            if (curr->right == nullptr) {
                curr->right = node;
                node->parent = curr;
                curr = nullptr;
            }
            else {
                curr = curr->right;
            }
        }
    }

    /*
    node = node⇢parent
    while (node != null) {
        AVLTreeRebalance(tree, node)
        node = node⇢parent
    }
    */

}

int AVLTree::balanceFactor(Node *node) const {
    return node->balanceFactor;
}

void AVLTree::printBalanceFactors() const {
    cout << " Print Balance Factor In-order" << endl;
    printBalanceFactors(root_);
    cout << endl;
}

void AVLTree::rotate(Node *node, const string &val) {

}

Node *AVLTree::rotateLeft(Node *node) {
    Node *right = node->right;
    Node *T2 = node->left;

    right->left = node;
    node->right = T2;

    node->height = max(node->left->height, node->right->height) + 1;
    right->height = max(right->left->height, right->right->height)+1;

    return right;
}

Node *AVLTree::rotateRight(Node *node) {
    Node *left = node->left;
    Node *T2 = left->right;

    left->right = node;
    node->left = T2;

    node->height =max(node->left->height, node->right->height) + 1;
    left->height = max(left->left->height, node->right->height) +1;

    return node;
}

Node *AVLTree::findUnbalancedNode(Node *node, const string &val) const {

}

void AVLTree::printBalanceFactors(Node *node) const {
    if (node != nullptr ){
        printBalanceFactors(node->left);
        cout << node->data << "(" << node->balanceFactor << ") ";
        printBalanceFactors(node->right);
    }
    else return;
}

void AVLTree::visualizeTree(const string& outputFilename) const {
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open()) {
        cout << "Error" << endl;
        return;
    }
    outFS << "digraph G {" << endl;
    visualizeTree(outFS, root_);
    outFS << "}";
    outFS.close();
    string jpgFilename =
            outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream& outFS, Node* node) const {
    if (node) {
        if (node->left) {
            visualizeTree(outFS, node->left);
            outFS << node->data << " -> " << node->left->data << ";" << endl;
        }
        if (node->right) {
            visualizeTree(outFS, node->right);
            outFS << node->data << " -> " << node->right->data << ";" << endl;
        }
    }
}