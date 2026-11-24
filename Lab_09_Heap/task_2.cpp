#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <utility>

// ============================================================================
// Data Structure Lab - Lab 09 (Heap and Heap Sort)
// Task 2: Hospital Emergency Management System (Max Heap using Tree Nodes)
// ============================================================================

class Patient {
public:
    std::string name;
    int patientID;
    int priorityLevel; // Higher number = higher emergency priority
    Patient* left;
    Patient* right;
    Patient* parent;

    Patient(const std::string& patientName, int id, int priority)
        : name(patientName), patientID(id), priorityLevel(priority),
          left(nullptr), right(nullptr), parent(nullptr) {}
};

class EmergencyMaxHeap {
private:
    Patient* root;
    int size;

    void swapData(Patient* a, Patient* b) {
        std::swap(a->name, b->name);
        std::swap(a->patientID, b->patientID);
        std::swap(a->priorityLevel, b->priorityLevel);
    }

    void heapifyUp(Patient* node) {
        while (node->parent != nullptr && node->priorityLevel > node->parent->priorityLevel) {
            swapData(node, node->parent);
            node = node->parent;
        }
    }

    void heapifyDown(Patient* node) {
        while (node != nullptr) {
            Patient* highest = node;

            if (node->left != nullptr && node->left->priorityLevel > highest->priorityLevel) {
                highest = node->left;
            }
            if (node->right != nullptr && node->right->priorityLevel > highest->priorityLevel) {
                highest = node->right;
            }

            if (highest != node) {
                swapData(node, highest);
                node = highest;
            } else {
                break;
            }
        }
    }

    Patient* getLastNode() const {
        if (root == nullptr) return nullptr;

        std::queue<Patient*> q;
        q.push(root);
        Patient* last = nullptr;

        while (!q.empty()) {
            last = q.front();
            q.pop();
            if (last->left != nullptr) q.push(last->left);
            if (last->right != nullptr) q.push(last->right);
        }
        return last;
    }

    void clear(Patient* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    EmergencyMaxHeap() : root(nullptr), size(0) {}

    ~EmergencyMaxHeap() {
        clear(root);
    }

    void insert(const std::string& name, int patientID, int priorityLevel) {
        Patient* newNode = new Patient(name, patientID, priorityLevel);
        size++;

        if (root == nullptr) {
            root = newNode;
            return;
        }

        std::queue<Patient*> q;
        q.push(root);

        while (!q.empty()) {
            Patient* current = q.front();
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

    void displayHighestPriority() const {
        if (root == nullptr) {
            std::cout << "No patients in emergency queue.\n";
            return;
        }
        std::cout << "  Patient ID : " << root->patientID << "\n"
                  << "  Name       : " << root->name << "\n"
                  << "  Priority   : " << root->priorityLevel << "\n";
    }

    void treatHighestPriorityPatient() {
        if (root == nullptr) {
            std::cout << "No patients to treat.\n";
            return;
        }

        std::cout << "\nTreating and removing patient with highest priority:\n";
        displayHighestPriority();

        if (size == 1) {
            delete root;
            root = nullptr;
            size = 0;
            return;
        }

        Patient* last = getLastNode();
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
            std::cout << "Emergency queue is empty.\n";
            return;
        }

        std::cout << std::left << std::setw(14) << "Patient ID"
                  << std::setw(22) << "Patient Name"
                  << std::setw(15) << "Priority Level" << "\n";
        std::cout << std::string(51, '-') << "\n";

        std::queue<Patient*> q;
        q.push(root);

        while (!q.empty()) {
            Patient* current = q.front();
            q.pop();

            std::cout << std::left << std::setw(14) << current->patientID
                      << std::setw(22) << current->name
                      << std::setw(15) << current->priorityLevel << "\n";

            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "   HOSPITAL EMERGENCY MANAGEMENT SYSTEM (MAX HEAP)  \n";
    std::cout << "====================================================\n\n";

    EmergencyMaxHeap emergencyQueue;

    // Insert 7 patients into the Max Heap
    std::cout << "Inserting 7 emergency patients into the Max Heap...\n";
    emergencyQueue.insert("Imran Siddiqui", 201, 4);
    emergencyQueue.insert("Sana Javed", 202, 8);
    emergencyQueue.insert("Tariq Mehmood", 203, 6);
    emergencyQueue.insert("Nadia Hussain", 204, 10);
    emergencyQueue.insert("Kamran Ali", 205, 5);
    emergencyQueue.insert("Hina Shah", 206, 9);
    emergencyQueue.insert("Danish Qureshi", 207, 7);

    std::cout << "\nAll Patients (Level Order Traversal):\n";
    emergencyQueue.displayLevelOrder();

    std::cout << "\nPatient with Highest Priority (Needs Immediate Treatment):\n";
    emergencyQueue.displayHighestPriority();

    // Delete highest priority patient after treatment and rebalance
    emergencyQueue.treatHighestPriorityPatient();

    std::cout << "\nNext Patient Who Needs Treatment (After Heapify Down):\n";
    emergencyQueue.displayHighestPriority();

    std::cout << "\nUpdated Emergency Queue (Level Order Traversal):\n";
    emergencyQueue.displayLevelOrder();

    return 0;
}
