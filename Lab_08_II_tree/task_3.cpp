#include <iostream>
#include <memory>
#include <string>

class Node {
public:
    std::string folder;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(const std::string& folderName) : folder(folderName) {}
};

void inOrder(const Node* node) {
    if (node == nullptr) {
        return;
    }
    inOrder(node->left.get());
    std::cout << node->folder << ' ';
    inOrder(node->right.get());
}

void preOrder(const Node* node) {
    if (node == nullptr) {
        return;
    }
    std::cout << node->folder << ' ';
    preOrder(node->left.get());
    preOrder(node->right.get());
}

void postOrder(const Node* node) {
    if (node == nullptr) {
        return;
    }
    postOrder(node->left.get());
    postOrder(node->right.get());
    std::cout << node->folder << ' ';
}

int main() {
    auto root = std::make_unique<Node>("C:");
    root->left = std::make_unique<Node>("Documents");
    root->right = std::make_unique<Node>("Downloads");
    root->left->left = std::make_unique<Node>("Assignments");
    root->left->right = std::make_unique<Node>("Projects");
    root->right->left = std::make_unique<Node>("Images");
    root->right->right = std::make_unique<Node>("Videos");

    std::cout << "Computer File Explorer - Depth-First Traversals (DFS)\n";
    std::cout << "In-order (left, root, right): ";
    inOrder(root.get());
    std::cout << "\nPre-order (root, left, right): ";
    preOrder(root.get());
    std::cout << "\nPost-order (left, right, root): ";
    postOrder(root.get());
    std::cout << '\n';
    return 0;
}
