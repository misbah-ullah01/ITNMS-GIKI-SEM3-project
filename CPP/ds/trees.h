#ifndef TREES_H
#define TREES_H

#include <iostream>
using namespace std;

template <typename T>
struct TreeNode
{
    T data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST
{
private:
    TreeNode<T> *root;

    // Helper: insert recursively
    TreeNode<T> *insertRec(TreeNode<T> *node, T val)
    {
        if (!node)
            return new TreeNode<T>(val);

        if (val < node->data)
            node->left = insertRec(node->left, val);
        else if (val > node->data)
            node->right = insertRec(node->right, val);
        // if val == node->data, do nothing (no duplicates)
        return node;
    }

    // Helper: search recursively
    bool searchRec(TreeNode<T> *node, T val)
    {
        if (!node)
            return false;
        if (node->data == val)
            return true;
        if (val < node->data)
            return searchRec(node->left, val);
        else
            return searchRec(node->right, val);
    }

    // Helper: inorder traversal
    void inorderRec(TreeNode<T> *node) const
    {
        if (!node)
            return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

    // Helper: delete tree
    void clearRec(TreeNode<T> *node)
    {
        if (!node)
            return;
        clearRec(node->left);
        clearRec(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    ~BST()
    {
        clearRec(root);
    }

    // Insert a value
    void insert(T val)
    {
        root = insertRec(root, val);
    }

    // Search a value
    bool search(T val)
    {
        return searchRec(root, val);
    }

    // Display tree in-order
    void displayInorder() const
    {
        cout << "BST Inorder: ";
        inorderRec(root);
        cout << endl;
    }

    // Check if tree is empty
    bool isEmpty() const
    {
        return root == nullptr;
    }
};

#endif
