#include <iostream>
#include <memory>
#include <queue>
#include <string>

class Node {
public:
    std::string category;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(const std::string& categoryName) : category(categoryName) {}
};

void breadthFirstTraversal(const Node* root) {
    if (root == nullptr) {
        return;
    }

    std::queue<const Node*> nodes;
    nodes.push(root);
    bool first = true;

    while (!nodes.empty()) {
        const Node* current = nodes.front();
        nodes.pop();

        if (!first) {
            std::cout << " -> ";
        }
        std::cout << current->category;
        first = false;

        if (current->left) {
            nodes.push(current->left.get());
        }
        if (current->right) {
            nodes.push(current->right.get());
        }
    }
    std::cout << '\n';
}

int main() {
    auto root = std::make_unique<Node>("Electronics");
    root->left = std::make_unique<Node>("Clothing");
    root->right = std::make_unique<Node>("Mobiles");
    root->left->left = std::make_unique<Node>("Men");
    root->left->right = std::make_unique<Node>("Women");
    root->right->left = std::make_unique<Node>("Laptops");
    root->right->right = std::make_unique<Node>("Accessories");

    std::cout << "Shopping Categories - Breadth-First Traversal (BFS)\n";
    breadthFirstTraversal(root.get());
    return 0;
}
