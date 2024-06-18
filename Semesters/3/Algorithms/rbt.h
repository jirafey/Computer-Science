#pragma once
#include <iostream>
#include <string>
#include <functional>

template <typename T>
class RedBlackTree {
public:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node* parent;
        int color; // 0 for black, 1 for red
    };

    Node* root;
    int height;

    RedBlackTree() {
        root = nullptr;
        height = 0;
    }

    void insert(T data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->parent = nullptr;
        newNode->color = 1; // Red

        if (root == nullptr) {
            height++;
            root = newNode;
        } else {
            Node* current = root;
            Node* parent = nullptr;

            while (current != nullptr) {
                parent = current;

                if (newNode->data < current->data) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }

            newNode->parent = parent;

            if (newNode->data < parent->data) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
        }

        insertFix(newNode);
    }

    int calculateHeight(Node* node) {
        if (node == nullptr) {
            return -1; // Height of an empty tree is -1
        }

        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);

        return 1 + std::max(leftHeight, rightHeight);
    }

    void clear(Node*& node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
            node = nullptr;
        }
    }

    void preOrderTraversal(Node* node, std::function<void(T)> action) {
        if (node != nullptr) {
            action(node->data);
            preOrderTraversal(node->left, action);
            preOrderTraversal(node->right, action);
        }
    }

    void inOrderTraversal(Node* node, std::function<void(T)> action) {
        if (node != nullptr) {
            inOrderTraversal(node->left, action);
            action(node->data);
            inOrderTraversal(node->right, action);
        }
    }
    std::string to_str() {
        std::string result;
        result += "Red-Black Tree:\n";
        result += "Size: " + std::to_string(calculateSize(root)) + "\n";
        result += "{\n";
        int counter = 0; // Counter for generating unique numbers
        to_str_helper(root, 0, result, counter);
        result += "}\n";
        return result;
    }

private:
    void to_str_helper(Node* node, int indent, std::string& result, int& counter) {
        if (node != nullptr) {
            to_str_helper(node->right, indent + 1, result, counter);

            result += "(" + std::to_string(counter++) + ": ["
                      + (node->color == 0 ? "black" : "red") + ", "
                      + "p: " + (node->parent ? std::to_string(node->parent->data) : "NULL") + ", "
                      + "l: " + (node->left ? std::to_string(node->left->data) : "NULL") + ", "
                      + "r: " + (node->right ? std::to_string(node->right->data) : "NULL")
                      + "] (" + std::to_string(node->data) + ", " + std::to_string(node->data) + ")),\n";

            to_str_helper(node->left, indent + 1, result, counter);
        }
    }

    int calculateSize(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        return 1 + calculateSize(node->left) + calculateSize(node->right);
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nullptr) {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;

        if (y->right != nullptr) {
            y->right->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;
    }

    void insertFix(Node* k) {
        while (k->parent != nullptr && k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                Node* u = k->parent->parent->left; // Uncle

                if (u != nullptr && u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }

                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            } else {
                Node* u = k->parent->parent->right; // Uncle

                if (u != nullptr && u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }

                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }

            if (k == root) {
                break;
            }
        }

        root->color = 0;
    }

public:
    Node* search(Node* node, T key) {
        if (node == nullptr || node->data == key) {
            return node;
        }

        if (key < node->data) {
            return search(node->left, key);
        }

        return search(node->right, key);
    }
};
