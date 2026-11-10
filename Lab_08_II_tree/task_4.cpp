#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

class AvlTree {
private:
    struct Node {
        int token;
        int nodeHeight;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(int value) : token(value), nodeHeight(1) {}
    };

    std::unique_ptr<Node> root;

    static int height(const Node* node) {
        return node == nullptr ? 0 : node->nodeHeight;
    }

    static int balanceFactor(const Node* node) {
        return node == nullptr ? 0 : height(node->left.get()) - height(node->right.get());
    }

    static void updateHeight(Node* node) {
        node->nodeHeight =
            1 + std::max(height(node->left.get()), height(node->right.get()));
    }

    static std::unique_ptr<Node> rotateRight(std::unique_ptr<Node> oldRoot) {
        std::unique_ptr<Node> newRoot = std::move(oldRoot->left);
        oldRoot->left = std::move(newRoot->right);
        updateHeight(oldRoot.get());
        newRoot->right = std::move(oldRoot);
        updateHeight(newRoot.get());
        return newRoot;
    }

    static std::unique_ptr<Node> rotateLeft(std::unique_ptr<Node> oldRoot) {
        std::unique_ptr<Node> newRoot = std::move(oldRoot->right);
        oldRoot->right = std::move(newRoot->left);
        updateHeight(oldRoot.get());
        newRoot->left = std::move(oldRoot);
        updateHeight(newRoot.get());
        return newRoot;
    }

    static std::unique_ptr<Node> insert(std::unique_ptr<Node> node, int token) {
        if (!node) {
            return std::make_unique<Node>(token);
        }

        if (token < node->token) {
            node->left = insert(std::move(node->left), token);
        } else if (token > node->token) {
            node->right = insert(std::move(node->right), token);
        } else {
            return node;
        }

        updateHeight(node.get());
        const int balance = balanceFactor(node.get());

        if (balance > 1 && token < node->left->token) {
            return rotateRight(std::move(node));
        }
        if (balance < -1 && token > node->right->token) {
            return rotateLeft(std::move(node));
        }
        if (balance > 1 && token > node->left->token) {
            node->left = rotateLeft(std::move(node->left));
            return rotateRight(std::move(node));
        }
        if (balance < -1 && token < node->right->token) {
            node->right = rotateRight(std::move(node->right));
            return rotateLeft(std::move(node));
        }

        return node;
    }

    static void displayInOrder(const Node* node) {
        if (node == nullptr) {
            return;
        }
        displayInOrder(node->left.get());
        std::cout << node->token << ' ';
        displayInOrder(node->right.get());
    }

    static void displayChildren(const Node* node, const std::string& prefix, bool isLeft) {
        if (node == nullptr) {
            return;
        }

        std::cout << prefix << (isLeft ? "L-- " : "R-- ") << node->token
                  << " (height=" << node->nodeHeight
                  << ", balance=" << balanceFactor(node) << ")\n";
        const std::string childPrefix = prefix + (isLeft ? "|   " : "    ");
        displayChildren(node->left.get(), childPrefix, true);
        displayChildren(node->right.get(), childPrefix, false);
    }

public:
    void insert(int token) {
        root = insert(std::move(root), token);
    }

    void display() const {
        std::cout << "In-order tokens: ";
        displayInOrder(root.get());
        std::cout << "\nFinal balanced tree (height and balance factor):\n";
        if (root) {
            std::cout << "Root: " << root->token << " (height=" << root->nodeHeight
                      << ", balance=" << balanceFactor(root.get()) << ")\n";
            displayChildren(root->left.get(), "", true);
            displayChildren(root->right.get(), "", false);
        }
    }
};

int main() {
    AvlTree appointments;
    const int tokens[] = {15, 25, 35, 45, 55, 65, 75};

    for (int token : tokens) {
        appointments.insert(token);
    }

    std::cout << "Hospital Appointment System - AVL Tree\n";
    appointments.display();
    return 0;
}
