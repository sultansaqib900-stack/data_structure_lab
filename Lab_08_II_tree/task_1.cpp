#include <iostream>
#include <memory>
#include <string>

class Node {
public:
    std::string name;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(const std::string& memberName) : name(memberName) {}
};

void displayHierarchy(const Node* node) {
    if (node == nullptr) {
        return;
    }

    std::cout << node->name << " | left: "
              << (node->left ? node->left->name : "None")
              << " | right: "
              << (node->right ? node->right->name : "None") << '\n';

    displayHierarchy(node->left.get());
    displayHierarchy(node->right.get());
}

int main() {
    auto hod = std::make_unique<Node>("Dr. Ayesha (HOD)");
    hod->left = std::make_unique<Node>("Dr. Bilal (CS Coordinator)");
    hod->right = std::make_unique<Node>("Dr. Sara (AI Coordinator)");
    hod->left->left = std::make_unique<Node>("Mr. Hamza (CS Faculty)");
    hod->left->right = std::make_unique<Node>("Ms. Noor (CS Faculty)");
    hod->right->left = std::make_unique<Node>("Mr. Ali (AI Faculty)");
    hod->right->right = std::make_unique<Node>("Ms. Zainab (AI Faculty)");

    std::cout << "University Department Hierarchy\n";
    displayHierarchy(hod.get());
    return 0;
}
