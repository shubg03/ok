#include <iostream>

class Node {
public:
    int data;
    Node* left;
    Node* right;
    bool isThreaded;
    Node* thread;

    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
        isThreaded = false;
        thread = NULL;
    }
};

class ThreadedBinaryTree {
private:
    Node* root;

    void insert(Node*& current, int data) {
        if (!current) {
            current = new Node(data);
        } else if (data < current->data) {
            if (current->left) {
                insert(current->left, data);
            } else {
                current->left = new Node(data);
                current->left->thread = current;
                current->left->isThreaded = true;
            }
        } else {
            if (current->right) {
                insert(current->right, data);
            } else {
                Node* newNode = new Node(data);
                newNode->thread = current->thread;
                newNode->isThreaded = true;
                current->thread = newNode;
                current->right = newNode;
            }
        }
    }

    void inOrderTraversal(Node* current) {
        while (current->left) {
            current = current->left;
        }

        while (current) {
            std::cout << current->data << " ";
            if (current->isThreaded) {
                current = current->thread;
            } else {
                current = getLeftmost(current->right);
            }
        }
    }

    Node* getLeftmost(Node* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    void preOrderTraversal(Node* current) {
        if (current) {
            std::cout << current->data << " ";
            preOrderTraversal(current->left);
            preOrderTraversal(current->right);
        }
    }

public:
    ThreadedBinaryTree() : root(NULL) {}

    void insert(int data) {
        insert(root, data);
    }

    void inOrderTraversal() {
        if (root) {
            inOrderTraversal(root);
        }
    }

    void preOrderTraversal() {
        preOrderTraversal(root);
    }
};

int main() {
    ThreadedBinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    std::cout << "In-order traversal: ";
    tree.inOrderTraversal();
    
    std::cout << "\n\nPre-order traversal: ";
    tree.preOrderTraversal();

    return 0;
}
