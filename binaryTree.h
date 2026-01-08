#include <iostream>
#include <queue>
using namespace std;

/* 
    ============== LEARNING ================
    Re-visit binary Tree project for class, 
    .h file, and pointer information
    ========================================
*/

class Node {
public: 
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class binaryTree {
    Node* root;

    Node* deleteRecursive(Node* current, int value) {
        // Base case:
        // If the current subtree is empty, there is nothing to delete.
        if (current == nullptr) return nullptr;

        // Case 1: The current node contains the value to be deleted.
        if (current->data == value) {
            // Case 1a: Node is a leaf (no children).
            // Safe to delete directly and return null to the parent.
            if (current->left == nullptr && current->right == nullptr) {
                delete current;
                return nullptr;
            }
            // Case 1b: Node has only a right child.
            // Replace the node with its right subtree.
            if (current->left == nullptr) {
                Node* temp = current->right;
                delete current;
                return temp;
            }
            // Case 1c: Node has only a left child.
            // Replace the node with its left subtree.
            if (current->right == nullptr) {
                Node* temp = current->left;
                delete current;
                return temp;
            }

            // Case 1d: Node has two children.
            // Find the inorder successor (smallest value in right subtree).
            Node* successor = findMin(current->right);

            // Copy the successor's value into the current node.
            current->data = successor->data;

            // Recursively delete the successor node from the right subtree.
            current->right = deleteRecursive(current->right, successor->data);
        }
        else {
            // Case 2: Current node does not match the value.
            // Continue searching both subtrees recursively.
            current->left = deleteRecursive(current->left, value);
            current->right = deleteRecursive(current->right, value);
        }
        // Return the (possibly updated) root of this subtree.
        return current;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    bool searchRecursive(Node* current, int value) {
        // no data, return false for not found
        if (current == nullptr) return false;
        // This node has the data, return true for having found the data
        if (current->data == value) return true;
        // If it's not in this node, search the node's children
        return searchRecursive(current->left, value) || searchRecursive(current->right, value);
    }

public:
    // Constructor
    binaryTree() : root(nullptr) {}

    void insertNode(int value) {
        Node* newNode = new Node(value);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        queue<Node*> q;
        q.push(root);

        while(!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current->left == nullptr) {
                current->left = newNode;
                return;
            }
            else {
                q.push(current->left);
            }

            if (current->right == nullptr) {
                current->right = newNode;
                return;
            }
            else {
                q.push(current->right);
            }
        }
    }

    // Hides deleteRecursive from the user
    void deleteNode(int value) {
        root = deleteRecursive(root, value);
    }

    // Same as delete
    bool search(int value) {
        return searchRecursive(root, value);
    }

    // levelOrder function made possible by inserting the nodes into the queue initially
    void levelOrder() {
        if (root == nullptr) return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
        cout << endl;
    }
}; 