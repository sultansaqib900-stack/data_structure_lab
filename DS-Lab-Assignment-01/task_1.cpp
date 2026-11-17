#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

// ============================================================================
// Data Structure Lab - Assignment 01
// Task 1: Airport Flight Scheduling System — Binary Search Tree (BST)
// ============================================================================

class Node {
public:
    int flightNumber;
    std::string destination;
    std::string departureTime;
    Node* left;
    Node* right;

    Node(int fNumber, const std::string& dest, const std::string& depTime)
        : flightNumber(fNumber), destination(dest), departureTime(depTime),
          left(nullptr), right(nullptr) {}
};

class FlightBST {
private:
    Node* root;

    // Helper: Insert record into BST
    Node* insertHelper(Node* current, int fNumber, const std::string& dest, const std::string& depTime) {
        if (current == nullptr) {
            return new Node(fNumber, dest, depTime);
        }
        if (fNumber < current->flightNumber) {
            current->left = insertHelper(current->left, fNumber, dest, depTime);
        } else if (fNumber > current->flightNumber) {
            current->right = insertHelper(current->right, fNumber, dest, depTime);
        } else {
            std::cout << "[Warning] Flight " << fNumber << " already exists! Duplicates not allowed.\n";
        }
        return current;
    }

    // Helper: Search for a flight
    Node* searchHelper(Node* current, int fNumber) const {
        if (current == nullptr || current->flightNumber == fNumber) {
            return current;
        }
        if (fNumber < current->flightNumber) {
            return searchHelper(current->left, fNumber);
        }
        return searchHelper(current->right, fNumber);
    }

    // Helper: Find node with minimum flight number in a subtree
    Node* findMinNode(Node* current) const {
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Helper: Find node with maximum flight number in a subtree
    Node* findMaxNode(Node* current) const {
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    // Helper: Delete a flight record handling all 3 cases
    Node* deleteHelper(Node* current, int fNumber, bool& deleted) {
        if (current == nullptr) {
            return nullptr;
        }

        if (fNumber < current->flightNumber) {
            current->left = deleteHelper(current->left, fNumber, deleted);
        } else if (fNumber > current->flightNumber) {
            current->right = deleteHelper(current->right, fNumber, deleted);
        } else {
            // Node found!
            deleted = true;

            // Case 1: Leaf node (no children)
            if (current->left == nullptr && current->right == nullptr) {
                std::cout << "-> Case 1 Applied: Deleting leaf node (Flight " << fNumber << ").\n";
                delete current;
                return nullptr;
            }
            // Case 2: Node with only one child
            else if (current->left == nullptr) {
                std::cout << "-> Case 2 Applied: Deleting node with right child only (Flight " << fNumber << ").\n";
                Node* temp = current->right;
                delete current;
                return temp;
            } else if (current->right == nullptr) {
                std::cout << "-> Case 2 Applied: Deleting node with left child only (Flight " << fNumber << ").\n";
                Node* temp = current->left;
                delete current;
                return temp;
            }
            // Case 3: Node with two children
            else {
                std::cout << "-> Case 3 Applied: Deleting node with two children (Flight " << fNumber << ").\n";
                // Get inorder successor (smallest in the right subtree)
                Node* successor = findMinNode(current->right);
                std::cout << "   Replacing Flight " << current->flightNumber 
                          << " with inorder successor Flight " << successor->flightNumber << ".\n";
                current->flightNumber = successor->flightNumber;
                current->destination = successor->destination;
                current->departureTime = successor->departureTime;

                // Delete the inorder successor from right subtree
                bool subDeleted = false;
                current->right = deleteHelper(current->right, successor->flightNumber, subDeleted);
            }
        }
        return current;
    }

    // Helper: In-order traversal (Left, Root, Right)
    void inOrderHelper(Node* current) const {
        if (current == nullptr) return;
        inOrderHelper(current->left);
        std::cout << std::left << std::setw(15) << current->flightNumber
                  << std::setw(25) << current->destination
                  << std::setw(20) << current->departureTime << "\n";
        inOrderHelper(current->right);
    }

    // Helper: Pre-order traversal (Root, Left, Right)
    void preOrderHelper(Node* current) const {
        if (current == nullptr) return;
        std::cout << std::left << std::setw(15) << current->flightNumber
                  << std::setw(25) << current->destination
                  << std::setw(20) << current->departureTime << "\n";
        preOrderHelper(current->left);
        preOrderHelper(current->right);
    }

    // Helper: Post-order traversal (Left, Right, Root)
    void postOrderHelper(Node* current) const {
        if (current == nullptr) return;
        postOrderHelper(current->left);
        postOrderHelper(current->right);
        std::cout << std::left << std::setw(15) << current->flightNumber
                  << std::setw(25) << current->destination
                  << std::setw(20) << current->departureTime << "\n";
    }

    // Helper: Count total flights
    int countFlightsHelper(Node* current) const {
        if (current == nullptr) return 0;
        return 1 + countFlightsHelper(current->left) + countFlightsHelper(current->right);
    }

    // Helper: Calculate height of tree
    int calculateHeightHelper(Node* current) const {
        if (current == nullptr) return 0; // Height in terms of levels (empty tree = 0)
        return 1 + std::max(calculateHeightHelper(current->left), calculateHeightHelper(current->right));
    }

    // Helper: Visual tree display (2D)
    void displayTreeHelper(Node* current, int space, int indent = 8) const {
        if (current == nullptr) return;
        space += indent;
        displayTreeHelper(current->right, space, indent);
        std::cout << "\n";
        for (int i = indent; i < space; i++) {
            std::cout << " ";
        }
        std::cout << "[" << current->flightNumber << ":" << current->destination << "]\n";
        displayTreeHelper(current->left, space, indent);
    }

    // Helper: Free memory recursively
    void clearHelper(Node* current) {
        if (current == nullptr) return;
        clearHelper(current->left);
        clearHelper(current->right);
        delete current;
    }

public:
    FlightBST() : root(nullptr) {}

    ~FlightBST() {
        clearHelper(root);
    }

    // Insert flight
    void insert(int fNumber, const std::string& dest, const std::string& depTime) {
        root = insertHelper(root, fNumber, dest, depTime);
    }

    // Search flight
    void search(int fNumber) const {
        std::cout << "\nSearching for Flight Number: " << fNumber << "...\n";
        Node* result = searchHelper(root, fNumber);
        if (result != nullptr) {
            std::cout << ">> Flight Found!\n";
            std::cout << "   Flight Number  : " << result->flightNumber << "\n"
                      << "   Destination    : " << result->destination << "\n"
                      << "   Departure Time : " << result->departureTime << "\n";
        } else {
            std::cout << ">> Flight " << fNumber << " NOT found in schedule.\n";
        }
    }

    // Delete flight
    bool deleteFlight(int fNumber) {
        std::cout << "\nAttempting to delete Flight Number: " << fNumber << "...\n";
        bool deleted = false;
        root = deleteHelper(root, fNumber, deleted);
        if (deleted) {
            std::cout << ">> Flight " << fNumber << " successfully deleted.\n";
        } else {
            std::cout << ">> Flight " << fNumber << " NOT found for deletion.\n";
        }
        return deleted;
    }

    // Traversals
    void displayInOrder() const {
        std::cout << "\n--- In-Order Traversal (Sorted by Flight Number) ---\n";
        std::cout << std::left << std::setw(15) << "Flight No." 
                  << std::setw(25) << "Destination" 
                  << std::setw(20) << "Departure Time" << "\n";
        std::cout << std::string(60, '-') << "\n";
        inOrderHelper(root);
    }

    void displayPreOrder() const {
        std::cout << "\n--- Pre-Order Traversal (Root, Left, Right) ---\n";
        std::cout << std::left << std::setw(15) << "Flight No." 
                  << std::setw(25) << "Destination" 
                  << std::setw(20) << "Departure Time" << "\n";
        std::cout << std::string(60, '-') << "\n";
        preOrderHelper(root);
    }

    void displayPostOrder() const {
        std::cout << "\n--- Post-Order Traversal (Left, Right, Root) ---\n";
        std::cout << std::left << std::setw(15) << "Flight No." 
                  << std::setw(25) << "Destination" 
                  << std::setw(20) << "Departure Time" << "\n";
        std::cout << std::string(60, '-') << "\n";
        postOrderHelper(root);
    }

    // Min and Max
    void displayMinFlight() const {
        Node* minNode = findMinNode(root);
        if (minNode) {
            std::cout << "Minimum Flight Number: " << minNode->flightNumber 
                      << " (" << minNode->destination << " at " << minNode->departureTime << ")\n";
        } else {
            std::cout << "BST is empty.\n";
        }
    }

    void displayMaxFlight() const {
        Node* maxNode = findMaxNode(root);
        if (maxNode) {
            std::cout << "Maximum Flight Number: " << maxNode->flightNumber 
                      << " (" << maxNode->destination << " at " << maxNode->departureTime << ")\n";
        } else {
            std::cout << "BST is empty.\n";
        }
    }

    // Count flights
    int countFlights() const {
        return countFlightsHelper(root);
    }

    // Calculate height
    int calculateHeight() const {
        return calculateHeightHelper(root);
    }

    // Visual tree structure display
    void displayTreeStructure() const {
        if (root == nullptr) {
            std::cout << "[Empty Tree]\n";
            return;
        }
        std::cout << "\nVisual BST Structure (Rotate 90 deg counter-clockwise: Right child top, Left child bottom):\n";
        displayTreeHelper(root, 0);
        std::cout << "\n";
    }
};

int main() {
    std::cout << "======================================================================\n";
    std::cout << "       AIRPORT FLIGHT SCHEDULING SYSTEM (BINARY SEARCH TREE)         \n";
    std::cout << "======================================================================\n";

    FlightBST flightTree;

    // Requirement: Insert at least 12 flight records according to BST rules
    std::cout << "\n[Step 1] Inserting 14 Flight Records into BST...\n";
    flightTree.insert(350, "Paris", "10:30 AM");
    flightTree.insert(200, "London", "08:15 AM");
    flightTree.insert(600, "Tokyo", "01:45 PM");
    flightTree.insert(100, "Dubai", "06:00 AM");
    flightTree.insert(280, "New York", "09:30 AM");
    flightTree.insert(450, "Singapore", "11:15 AM");
    flightTree.insert(800, "Sydney", "04:00 PM");
    flightTree.insert(50,  "Toronto", "05:00 AM");
    flightTree.insert(150, "Frankfurt", "07:20 AM");
    flightTree.insert(250, "Istanbul", "08:50 AM");
    flightTree.insert(300, "Doha", "10:00 AM");
    flightTree.insert(520, "Rome", "02:10 PM");
    flightTree.insert(700, "Beijing", "03:30 PM");
    flightTree.insert(950, "Cairo", "05:45 PM");

    std::cout << ">> 14 Flight records successfully inserted!\n";

    // Display initial tree structure
    flightTree.displayTreeStructure();

    // Requirement: Display flight records using In-order, Pre-order, Post-order
    std::cout << "\n[Step 2] Displaying Traversals...\n";
    flightTree.displayInOrder();
    flightTree.displayPreOrder();
    flightTree.displayPostOrder();

    // Requirement: Search for a flight using flight number
    std::cout << "\n[Step 3] Performing Flight Searches...\n";
    flightTree.search(280); // Existing flight
    flightTree.search(700); // Existing flight
    flightTree.search(999); // Non-existing flight

    // Requirement: Display minimum and maximum flight numbers
    std::cout << "\n[Step 4] Minimum & Maximum Flight Records:\n";
    flightTree.displayMinFlight();
    flightTree.displayMaxFlight();

    // Requirement: Count total number of flights
    std::cout << "\n[Step 5] Total Flight Count:\n";
    std::cout << "Total number of flights scheduled: " << flightTree.countFlights() << "\n";

    // Requirement: Calculate height of the tree
    std::cout << "\n[Step 6] Tree Height:\n";
    std::cout << "Height of BST (Levels): " << flightTree.calculateHeight() << "\n";
    std::cout << "Height of BST (Edges) : " << flightTree.calculateHeight() - 1 << "\n";

    // Requirement: Delete flight records handling all THREE cases
    std::cout << "\n[Step 7] Deleting Records (Demonstrating all 3 Deletion Cases)...\n";
    
    // Case 1: Delete a leaf node (Flight 50 has 0 children)
    std::cout << "\n--- Testing Deletion Case 1: Leaf Node ---";
    flightTree.deleteFlight(50);

    // Case 2: Delete a node with one child (Flight 450 has only right child 520)
    std::cout << "\n--- Testing Deletion Case 2: Node with One Child ---";
    flightTree.deleteFlight(450);

    // Case 3: Delete a node with two children (Flight 200 has left child 100 and right child 280)
    std::cout << "\n--- Testing Deletion Case 3: Node with Two Children ---";
    flightTree.deleteFlight(200);

    // Verify state after deletions
    std::cout << "\n[Step 8] State After All Deletions:\n";
    std::cout << "Updated Flight Count: " << flightTree.countFlights() << "\n";
    std::cout << "Updated Tree Height (Levels): " << flightTree.calculateHeight() << "\n";

    // Display In-order after deletions
    flightTree.displayInOrder();

    // Requirement: Display the final BST structure
    std::cout << "\n[Step 9] Final BST Structure After Operations:\n";
    flightTree.displayTreeStructure();

    std::cout << "======================================================================\n";
    std::cout << "                  FLIGHT SCHEDULING SYSTEM COMPLETE                   \n";
    std::cout << "======================================================================\n";

    return 0;
}
