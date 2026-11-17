#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <queue>

// ============================================================================
// Data Structure Lab - Assignment 01
// Task 2: Emergency Rescue Operations — Priority-Based AVL Tree
// ============================================================================

class Node {
public:
    int emergencyID;
    std::string location;
    int severityLevel; // 1 (Low) to 5 (Critical)
    int height;
    Node* left;
    Node* right;

    Node(int id, const std::string& loc, int severity)
        : emergencyID(id), location(loc), severityLevel(severity),
          height(1), left(nullptr), right(nullptr) {}
};

class EmergencyAVL {
private:
    Node* root;

    // 1. Get height of node
    int getHeight(Node* n) const {
        return (n == nullptr) ? 0 : n->height;
    }

    // 2. Calculate balance factor of node: height(left) - height(right)
    int getBalanceFactor(Node* n) const {
        return (n == nullptr) ? 0 : getHeight(n->left) - getHeight(n->right);
    }

    // Update height of a node based on its children
    void updateHeight(Node* n) {
        if (n != nullptr) {
            n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
        }
    }

    // 3. Right Rotation (for LL imbalance):
    // Rotates node y with its left child x; x becomes new root of this subtree.
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        // Return new root of subtree
        return x;
    }

    // 4. Left Rotation (for RR imbalance):
    // Rotates node x with its right child y; y becomes new root of this subtree.
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        // Return new root of subtree
        return y;
    }

    // 5. Balance the node handling all 4 rotation cases (LL, RR, LR, RL)
    Node* balanceNode(Node* node, int id, bool isInsert = true) {
        if (node == nullptr) return nullptr;

        // Update height of this ancestor node
        updateHeight(node);

        // Get balance factor
        int balance = getBalanceFactor(node);

        // Case 1: Left-Left (LL) Case
        if (balance > 1 && (isInsert ? (id < node->left->emergencyID) : (getBalanceFactor(node->left) >= 0))) {
            std::cout << "   [AVL Rebalance] LL Case detected at ID " << node->emergencyID 
                      << " (BF=" << balance << ") -> Performing Right Rotation.\n";
            return rightRotate(node);
        }

        // Case 2: Right-Right (RR) Case
        if (balance < -1 && (isInsert ? (id > node->right->emergencyID) : (getBalanceFactor(node->right) <= 0))) {
            std::cout << "   [AVL Rebalance] RR Case detected at ID " << node->emergencyID 
                      << " (BF=" << balance << ") -> Performing Left Rotation.\n";
            return leftRotate(node);
        }

        // Case 3: Left-Right (LR) Case
        if (balance > 1 && (isInsert ? (id > node->left->emergencyID) : (getBalanceFactor(node->left) < 0))) {
            std::cout << "   [AVL Rebalance] LR Case detected at ID " << node->emergencyID 
                      << " (BF=" << balance << ") -> Performing Left-Right Rotation (Left on Child, then Right).\n";
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Case 4: Right-Left (RL) Case
        if (balance < -1 && (isInsert ? (id < node->right->emergencyID) : (getBalanceFactor(node->right) > 0))) {
            std::cout << "   [AVL Rebalance] RL Case detected at ID " << node->emergencyID 
                      << " (BF=" << balance << ") -> Performing Right-Left Rotation (Right on Child, then Left).\n";
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Recursive helper to insert an emergency record and rebalance
    Node* insertHelper(Node* node, int id, const std::string& loc, int severity) {
        // Step 1: Standard BST Insertion
        if (node == nullptr) {
            return new Node(id, loc, severity);
        }

        if (id < node->emergencyID) {
            node->left = insertHelper(node->left, id, loc, severity);
        } else if (id > node->emergencyID) {
            node->right = insertHelper(node->right, id, loc, severity);
        } else {
            std::cout << "[Warning] Emergency ID " << id << " already exists! Duplicates ignored.\n";
            return node;
        }

        // Step 2 & 3: Update height & perform rotations if unbalanced
        return balanceNode(node, id, true);
    }

    // Helper: Find node with minimum emergencyID in subtree
    Node* findMinNode(Node* node) const {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Recursive helper to delete an emergency record and rebalance
    Node* deleteHelper(Node* node, int id, bool& deleted) {
        if (node == nullptr) {
            return nullptr;
        }

        // Standard BST delete step
        if (id < node->emergencyID) {
            node->left = deleteHelper(node->left, id, deleted);
        } else if (id > node->emergencyID) {
            node->right = deleteHelper(node->right, id, deleted);
        } else {
            // Node found!
            deleted = true;

            // Node with 0 or 1 child
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    // No child case
                    temp = node;
                    node = nullptr;
                } else {
                    // One child case
                    *node = *temp; // Copy child contents
                }
                delete temp;
            } else {
                // Node with 2 children: get inorder successor
                Node* temp = findMinNode(node->right);
                node->emergencyID = temp->emergencyID;
                node->location = temp->location;
                node->severityLevel = temp->severityLevel;

                // Delete the inorder successor
                bool subDeleted = false;
                node->right = deleteHelper(node->right, temp->emergencyID, subDeleted);
            }
        }

        if (node == nullptr) {
            return nullptr;
        }

        // Rebalance the node after deletion
        return balanceNode(node, id, false);
    }

    // Helper: Search for an emergency ID
    Node* searchHelper(Node* node, int id) const {
        if (node == nullptr || node->emergencyID == id) {
            return node;
        }
        if (id < node->emergencyID) {
            return searchHelper(node->left, id);
        }
        return searchHelper(node->right, id);
    }

    // Helper: In-order traversal (Displays sorted by Emergency ID)
    void inOrderHelper(Node* node) const {
        if (node == nullptr) return;
        inOrderHelper(node->left);
        std::cout << std::left << std::setw(15) << node->emergencyID
                  << std::setw(35) << node->location
                  << std::setw(15) << (std::to_string(node->severityLevel) + "/5")
                  << std::setw(10) << node->height
                  << std::setw(10) << getBalanceFactor(node) << "\n";
        inOrderHelper(node->right);
    }

    // Helper: Visual tree display (2D structure)
    void displayTreeHelper(Node* node, int space, int indent = 8) const {
        if (node == nullptr) return;
        space += indent;
        displayTreeHelper(node->right, space, indent);
        std::cout << "\n";
        for (int i = indent; i < space; i++) {
            std::cout << " ";
        }
        std::cout << "[" << node->emergencyID << " | BF:" << getBalanceFactor(node) << "]\n";
        displayTreeHelper(node->left, space, indent);
    }

    // Free memory
    void clearHelper(Node* node) {
        if (node == nullptr) return;
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }

public:
    EmergencyAVL() : root(nullptr) {}

    ~EmergencyAVL() {
        clearHelper(root);
    }

    // Insert an emergency record
    void insert(int id, const std::string& loc, int severity) {
        std::cout << "Inserting Record -> ID: " << id << " | Location: " << loc 
                  << " | Severity: " << severity << "/5\n";
        root = insertHelper(root, id, loc, severity);
    }

    // Delete an emergency record
    bool deleteRecord(int id) {
        std::cout << "\nAttempting to delete Emergency ID: " << id << "...\n";
        bool deleted = false;
        root = deleteHelper(root, id, deleted);
        if (deleted) {
            std::cout << ">> Emergency Record ID " << id << " successfully deleted and AVL rebalanced.\n";
        } else {
            std::cout << ">> Emergency Record ID " << id << " NOT found.\n";
        }
        return deleted;
    }

    // Search for an emergency record
    void search(int id) const {
        std::cout << "\nSearching for Emergency ID: " << id << "...\n";
        Node* res = searchHelper(root, id);
        if (res != nullptr) {
            std::cout << ">> Emergency Record Found!\n";
            std::cout << "   Emergency ID    : " << res->emergencyID << "\n"
                      << "   Location        : " << res->location << "\n"
                      << "   Severity Level  : " << res->severityLevel << "/5\n"
                      << "   Node Height     : " << res->height << "\n"
                      << "   Balance Factor  : " << getBalanceFactor(res) << "\n";
        } else {
            std::cout << ">> Emergency ID " << id << " NOT found in rescue records.\n";
        }
    }

    // Display all records according to Emergency IDs (In-Order)
    void displayInOrder() const {
        std::cout << "\n--- In-Order Traversal (Sorted by Emergency ID) ---\n";
        std::cout << std::left << std::setw(15) << "Emergency ID"
                  << std::setw(35) << "Location / Incident"
                  << std::setw(15) << "Severity"
                  << std::setw(10) << "Height"
                  << std::setw(10) << "BF" << "\n";
        std::cout << std::string(85, '-') << "\n";
        inOrderHelper(root);
    }

    // Level-order traversal (BFS) using queue
    void displayLevelOrder() const {
        std::cout << "\n--- Level-Order Traversal (BFS by Tree Levels) ---\n";
        if (root == nullptr) {
            std::cout << "[Tree is empty]\n";
            return;
        }

        std::queue<Node*> q;
        q.push(root);
        int currentLevel = 1;

        while (!q.empty()) {
            int levelSize = q.size();
            std::cout << ">> Level " << currentLevel << " (" << levelSize << " node(s)):\n";
            std::cout << std::left << std::setw(15) << "  Emergency ID"
                      << std::setw(35) << "Location / Incident"
                      << std::setw(15) << "Severity"
                      << std::setw(10) << "Height"
                      << std::setw(10) << "BF" << "\n";
            std::cout << "  " << std::string(83, '-') << "\n";

            for (int i = 0; i < levelSize; ++i) {
                Node* curr = q.front();
                q.pop();

                std::cout << "  " << std::left << std::setw(13) << curr->emergencyID
                          << std::setw(35) << curr->location
                          << std::setw(15) << (std::to_string(curr->severityLevel) + "/5")
                          << std::setw(10) << curr->height
                          << std::setw(10) << getBalanceFactor(curr) << "\n";

                if (curr->left != nullptr) q.push(curr->left);
                if (curr->right != nullptr) q.push(curr->right);
            }
            std::cout << "\n";
            currentLevel++;
        }
    }

    // Visual tree display
    void displayTreeStructure() const {
        if (root == nullptr) {
            std::cout << "[Empty AVL Tree]\n";
            return;
        }
        std::cout << "\nVisual AVL Tree Structure (Rotate 90 deg counter-clockwise: [ID | BF]):\n";
        displayTreeHelper(root, 0);
        std::cout << "\n";
    }

    // Get root height
    int getRootHeight() const {
        return getHeight(root);
    }
};

int main() {
    std::cout << "======================================================================\n";
    std::cout << "    EMERGENCY RESCUE OPERATIONS SYSTEM (PRIORITY-BASED AVL TREE)      \n";
    std::cout << "======================================================================\n";

    EmergencyAVL rescueTree;

    // Requirement: Insert at least 12 emergency records according to BST/AVL rules
    // Designed to trigger and test all 4 AVL rotations (LL, RR, LR, RL)
    std::cout << "\n[Step 1] Inserting 13 Emergency Records with Automatic AVL Balancing...\n";
    std::cout << "----------------------------------------------------------------------\n";
    rescueTree.insert(150, "Rawal Dam (Water Rescue)", 3);
    rescueTree.insert(120, "Blue Area (Fire Outbreak)", 5);
    rescueTree.insert(110, "Sector F-7 (Flooding)", 4);      // Triggers LL rotation
    rescueTree.insert(140, "Sector G-9 (Building Collapse)", 5);
    rescueTree.insert(130, "Highway M-2 (Collision)", 5);    // Triggers LR rotation
    rescueTree.insert(180, "Expressway (Medical Aid)", 3);
    rescueTree.insert(200, "Faizabad (Landslide Rescue)", 4);// Triggers RR rotation
    rescueTree.insert(160, "Margalla Hills (Forest Fire)", 4);
    rescueTree.insert(170, "Industrial Area (Gas Leak)", 5); // Triggers RL rotation
    rescueTree.insert(190, "Sector I-8 (Structural Damage)", 2);
    rescueTree.insert(210, "Airport Road (Chemical Spill)", 3);
    rescueTree.insert(220, "Saddar (Substation Fire)", 4);
    rescueTree.insert(230, "Sector H-12 (Search & Rescue)", 3);

    std::cout << "\n>> All 13 emergency records inserted and balanced successfully!\n";

    // Requirement: Display the balanced AVL tree structure
    std::cout << "\n[Step 2] Displaying Initial Balanced AVL Tree Structure...\n";
    rescueTree.displayTreeStructure();

    // Requirement: Display all emergency records according to Emergency IDs (In-Order)
    std::cout << "\n[Step 3] Displaying Records via In-Order Traversal:\n";
    rescueTree.displayInOrder();

    // Requirement: Display emergency records using Level-order (BFS) traversal
    std::cout << "\n[Step 4] Displaying Records via Level-Order (BFS) Traversal:\n";
    rescueTree.displayLevelOrder();

    // Requirement: Implement searching using Emergency ID
    std::cout << "\n[Step 5] Searching for Emergency Records...\n";
    rescueTree.search(160); // Existing ID
    rescueTree.search(220); // Existing ID
    rescueTree.search(999); // Non-existing ID

    // Requirement: Implement deletion of emergency records with automatic rebalancing
    std::cout << "\n[Step 6] Deleting Records with Automatic AVL Rebalancing...\n";
    
    // Delete leaf node
    rescueTree.deleteRecord(230);

    // Delete node that triggers AVL rebalancing
    rescueTree.deleteRecord(110);

    // Delete root or internal node with 2 children
    rescueTree.deleteRecord(150);

    // Requirement: Display traversals after deletions
    std::cout << "\n[Step 7] Records After Deletions (In-Order Traversal):\n";
    rescueTree.displayInOrder();

    std::cout << "\n[Step 8] Level-Order Traversal After Deletions:\n";
    rescueTree.displayLevelOrder();

    // Requirement: Display final balanced AVL Tree structure
    std::cout << "\n[Step 9] Final Balanced AVL Tree Structure:\n";
    rescueTree.displayTreeStructure();

    std::cout << "Overall Tree Height: " << rescueTree.getRootHeight() << "\n";

    std::cout << "======================================================================\n";
    std::cout << "               EMERGENCY RESCUE AVL SYSTEM COMPLETE                   \n";
    std::cout << "======================================================================\n";

    return 0;
}
