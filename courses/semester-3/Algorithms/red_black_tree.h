    #pragma once
    #include <string>
    #include <stack>
    #include <functional>

    template <typename T>
    class RBT{
    public:
        struct Node {
            T data;
            Node *left;
            Node *right;
            Node *root;
            bool isRed;
        };
        Node *root;
        int height;
        RBT(){
            root = nullptr;
            height = 0;
        }
        void insert(T data){
            Node *newNode = new Node();
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;

            if (root == nullptr){
                height++;
                root = newNode;
            } else {
                Node *current = root;

                while (true) {
                    if (current->data > data) {
                        if (current->left == nullptr) {
                            current->left = newNode;
                            newNode->root = current;
                            height++;
                            break;
                        } else {
                            current = current->left;
                        }
                    } else {
                        if (current->right == nullptr) {
                            current->right = newNode;
                            newNode->root = current;
                            height++;
                            break;
                        } else {
                            current = current->right;
                        }
                    }
                    newNode->isRed = true;
                    fixInsert(newNode);
                }
            }
        }
        int calculateHeight(Node* node) {
            if (node == nullptr) {
                return -1; // Height of an empty tree is -1
            }

            int leftHeight = calculateHeight(node->left);
            int rightHeight = calculateHeight(node->right);

            return 1 + std::max(leftHeight, rightHeight);
        }


        std::string to_string(Node* node, bool isLeft = false, int index = 1, const std::string& parent = "", int height = 0) {
            if (node == nullptr || height >= 3) {
                return "";
            }

            std::string str = (isLeft ? "L" : "R") + std::to_string(index) + ": ";

            str += custom_to_string(node->data);

            if (!parent.empty()) {
                str += " (Parent: " + parent + ")";
            }

            if (node->left != nullptr || node->right != nullptr) {
                str += " (";

                if (node->left != nullptr) {
                    str += to_string(node->left, true, index * 2, custom_to_string(node->data), height + 1);
                }

                if (node->right != nullptr) {
                    if (node->left != nullptr) {
                        str += ", ";
                    }
                    str += to_string(node->right, false, index * 2 + 1, custom_to_string(node->data), height + 1);
                }

                str += ")";
            }

            return str;
        }

        void deleteNode(Node*& node, T key) {
            Node* target = search(node, key);

            if (target == nullptr) {
            }
            if (node == nullptr) return;

            if (key < node->data) {
                deleteNode(node->left, key);
            } else if (key > node->data) {
                deleteNode(node->right, key);
            } else {
                // (0 children)
                if (node->left == nullptr && node->right == nullptr) {
                    delete node;
                    node = nullptr;
                }
                    // (1 child)
                else if (node->left == nullptr) {
                    Node* temp = node->right;
                    delete node;
                    node = temp;
                } else if (node->right == nullptr) {
                    Node* temp = node->left;
                    delete node;
                    node = temp;
                }
                    // (2 children)
                else {
                    Node* temp = findMin(node->right);
                    node->data = temp->data;
                    deleteNode(node->right, temp->data);
                }
            }
        }
        void leftRotate(Node *&node) {
            // Implement left rotation
        }

        void rightRotate(Node *&node) {
            // Implement right rotation
        }
        void fixInsert(Node *newNode) {
            while (newNode->root != nullptr && newNode->root->color == true) {
                // Handle cases and perform rotations to fix violations
                // Implement the necessary rotations and color adjustments here
            }

            root->color = false; // Ensure the root is always black
        }

        Node* search(Node* node, T key) {
            if (node == nullptr || node->data == key) {
                return node;
            }

            if (key < node->data) {
                return search(node->left, key);
            }

            return search(node->right, key);
        }

        Node* findMin(Node* node) {
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }
        void clear(Node*& node){
            if (node != nullptr){
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
    };
