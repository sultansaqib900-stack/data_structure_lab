#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <utility>

// ============================================================================
// Data Structure Lab - Lab 09 (Heap and Heap Sort)
// Task 4: Hospital Medicine Expiry Management (Min Heap using Tree Nodes)
// ============================================================================

class Medicine {
public:
    std::string name;
    int medicineID;
    int expiryDate; // Format: YYYYMMDD (smaller value = nearer expiry date)
    Medicine* left;
    Medicine* right;
    Medicine* parent;

    Medicine(const std::string& medName, int id, int expiry)
        : name(medName), medicineID(id), expiryDate(expiry),
          left(nullptr), right(nullptr), parent(nullptr) {}
};

class MedicineMinHeap {
private:
    Medicine* root;
    int size;

    void swapData(Medicine* a, Medicine* b) {
        std::swap(a->name, b->name);
        std::swap(a->medicineID, b->medicineID);
        std::swap(a->expiryDate, b->expiryDate);
    }

    // Move newly inserted node up to restore Min Heap property
    void heapifyUp(Medicine* node) {
        while (node->parent != nullptr && node->expiryDate < node->parent->expiryDate) {
            swapData(node, node->parent);
            node = node->parent;
        }
    }

    // Move root node down after deletion to restore Min Heap property
    void heapifyDown(Medicine* node) {
        while (node != nullptr) {
            Medicine* smallest = node;

            if (node->left != nullptr && node->left->expiryDate < smallest->expiryDate) {
                smallest = node->left;
            }
            if (node->right != nullptr && node->right->expiryDate < smallest->expiryDate) {
                smallest = node->right;
            }

            if (smallest != node) {
                swapData(node, smallest);
                node = smallest;
            } else {
                break;
            }
        }
    }

    Medicine* getLastNode() const {
        if (root == nullptr) return nullptr;

        std::queue<Medicine*> q;
        q.push(root);
        Medicine* last = nullptr;

        while (!q.empty()) {
            last = q.front();
            q.pop();
            if (last->left != nullptr) q.push(last->left);
            if (last->right != nullptr) q.push(last->right);
        }
        return last;
    }

    void clear(Medicine* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    MedicineMinHeap() : root(nullptr), size(0) {}

    ~MedicineMinHeap() {
        clear(root);
    }

    void insert(const std::string& name, int medicineID, int expiryDate) {
        Medicine* newNode = new Medicine(name, medicineID, expiryDate);
        size++;

        if (root == nullptr) {
            root = newNode;
            return;
        }

        std::queue<Medicine*> q;
        q.push(root);

        while (!q.empty()) {
            Medicine* current = q.front();
            q.pop();

            if (current->left == nullptr) {
                current->left = newNode;
                newNode->parent = current;
                break;
            } else {
                q.push(current->left);
            }

            if (current->right == nullptr) {
                current->right = newNode;
                newNode->parent = current;
                break;
            } else {
                q.push(current->right);
            }
        }

        heapifyUp(newNode);
    }

    void deleteNearestExpiry() {
        if (root == nullptr) {
            std::cout << "Min Heap is empty. No medicine to delete.\n";
            return;
        }

        std::cout << "\nMedicine with Nearest Expiry Date (Identified & Deleting):\n";
        std::cout << "  Medicine ID : " << root->medicineID << "\n"
                  << "  Name        : " << root->name << "\n"
                  << "  Expiry Date : " << root->expiryDate << " (YYYYMMDD)\n";

        if (size == 1) {
            delete root;
            root = nullptr;
            size = 0;
            return;
        }

        Medicine* last = getLastNode();
        swapData(root, last);

        if (last->parent->left == last) {
            last->parent->left = nullptr;
        } else {
            last->parent->right = nullptr;
        }

        delete last;
        size--;

        heapifyDown(root);
    }

    void displayLevelOrder() const {
        if (root == nullptr) {
            std::cout << "Min Heap is empty.\n";
            return;
        }

        std::cout << std::left << std::setw(14) << "Medicine ID"
                  << std::setw(24) << "Medicine Name"
                  << std::setw(18) << "Expiry (YYYYMMDD)" << "\n";
        std::cout << std::string(56, '-') << "\n";

        std::queue<Medicine*> q;
        q.push(root);

        while (!q.empty()) {
            Medicine* current = q.front();
            q.pop();

            std::cout << std::left << std::setw(14) << current->medicineID
                      << std::setw(24) << current->name
                      << std::setw(18) << current->expiryDate << "\n";

            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "   HOSPITAL MEDICINE EXPIRY MANAGEMENT (MIN HEAP)   \n";
    std::cout << "====================================================\n\n";

    MedicineMinHeap medicineHeap;

    // Insert 7 medicines using YYYYMMDD expiry dates
    std::cout << "Inserting 7 medicines into the Min Heap...\n";
    medicineHeap.insert("Paracetamol 500mg", 401, 20270515);
    medicineHeap.insert("Amoxicillin 250mg", 402, 20261210);
    medicineHeap.insert("Ibuprofen 400mg", 403, 20270322);
    medicineHeap.insert("Insulin Glargine", 404, 20261130);
    medicineHeap.insert("Ciprofloxacin", 405, 20270801);
    medicineHeap.insert("Omeprazole 20mg", 406, 20270118);
    medicineHeap.insert("Azithromycin", 407, 20261225);

    std::cout << "\nMin Heap (Level Order Traversal) after insertions:\n";
    medicineHeap.displayLevelOrder();

    // Identify and delete the medicine with the nearest expiry date
    medicineHeap.deleteNearestExpiry();

    std::cout << "\nUpdated Min Heap (Level Order Traversal) after Heapify Down:\n";
    medicineHeap.displayLevelOrder();

    return 0;
}
