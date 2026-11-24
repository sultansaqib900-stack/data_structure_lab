#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <utility>

// ============================================================================
// Data Structure Lab - Lab 09 (Heap and Heap Sort)
// Task 1: University Student Merit Ranking (Max Heap using Binary Tree Nodes)
// ============================================================================

class Student {
public:
    std::string name;
    int rollNumber;
    double marks;
    Student* left;
    Student* right;
    Student* parent;

    Student(const std::string& studentName, int roll, double studentMarks)
        : name(studentName), rollNumber(roll), marks(studentMarks),
          left(nullptr), right(nullptr), parent(nullptr) {}
};

class StudentMaxHeap {
private:
    Student* root;
    int size;

    void swapData(Student* a, Student* b) {
        std::swap(a->name, b->name);
        std::swap(a->rollNumber, b->rollNumber);
        std::swap(a->marks, b->marks);
    }

    // Move newly inserted node up to restore Max Heap property
    void heapifyUp(Student* node) {
        while (node->parent != nullptr && node->marks > node->parent->marks) {
            swapData(node, node->parent);
            node = node->parent;
        }
    }

    // Move root node down after deletion to restore Max Heap property
    void heapifyDown(Student* node) {
        while (node != nullptr) {
            Student* largest = node;

            if (node->left != nullptr && node->left->marks > largest->marks) {
                largest = node->left;
            }
            if (node->right != nullptr && node->right->marks > largest->marks) {
                largest = node->right;
            }

            if (largest != node) {
                swapData(node, largest);
                node = largest;
            } else {
                break;
            }
        }
    }

    // Find the last node in level-order traversal
    Student* getLastNode() const {
        if (root == nullptr) return nullptr;

        std::queue<Student*> q;
        q.push(root);
        Student* last = nullptr;

        while (!q.empty()) {
            last = q.front();
            q.pop();
            if (last->left != nullptr) q.push(last->left);
            if (last->right != nullptr) q.push(last->right);
        }
        return last;
    }

    void clear(Student* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    StudentMaxHeap() : root(nullptr), size(0) {}

    ~StudentMaxHeap() {
        clear(root);
    }

    void insert(const std::string& name, int rollNumber, double marks) {
        Student* newNode = new Student(name, rollNumber, marks);
        size++;

        if (root == nullptr) {
            root = newNode;
            return;
        }

        // Level-order search to find the first node with an available child slot
        std::queue<Student*> q;
        q.push(root);

        while (!q.empty()) {
            Student* current = q.front();
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

    void deleteHighestMarks() {
        if (root == nullptr) {
            std::cout << "Heap is empty. No student to delete.\n";
            return;
        }

        std::cout << "\nDeleting Student with Highest Marks (Root):\n";
        std::cout << "  Name       : " << root->name << "\n"
                  << "  Roll No.   : " << root->rollNumber << "\n"
                  << "  Marks      : " << root->marks << "\n";

        if (size == 1) {
            delete root;
            root = nullptr;
            size = 0;
            return;
        }

        Student* last = getLastNode();
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
            std::cout << "Heap is empty.\n";
            return;
        }

        std::cout << std::left << std::setw(12) << "Roll No."
                  << std::setw(22) << "Student Name"
                  << std::setw(10) << "Marks" << "\n";
        std::cout << std::string(44, '-') << "\n";

        std::queue<Student*> q;
        q.push(root);

        while (!q.empty()) {
            Student* current = q.front();
            q.pop();

            std::cout << std::left << std::setw(12) << current->rollNumber
                      << std::setw(22) << current->name
                      << std::setw(10) << current->marks << "\n";

            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "   UNIVERSITY STUDENT MERIT RANKING (MAX HEAP)      \n";
    std::cout << "====================================================\n\n";

    StudentMaxHeap meritHeap;

    // Insert 7 students into the Max Heap
    std::cout << "Inserting 7 students into the Max Heap...\n";
    meritHeap.insert("Ali Hassan", 101, 82.5);
    meritHeap.insert("Ayesha Khan", 102, 91.0);
    meritHeap.insert("Bilal Ahmed", 103, 76.0);
    meritHeap.insert("Fatima Noor", 104, 95.5);
    meritHeap.insert("Usman Tariq", 105, 88.0);
    meritHeap.insert("Zainab Malik", 106, 84.5);
    meritHeap.insert("Hamza Raza", 107, 93.0);

    std::cout << "\nMax Heap (Level Order Traversal) after insertions:\n";
    meritHeap.displayLevelOrder();

    // Delete student with the highest marks and apply Heapify Down
    meritHeap.deleteHighestMarks();

    std::cout << "\nUpdated Max Heap (Level Order Traversal) after Heapify Down:\n";
    meritHeap.displayLevelOrder();

    return 0;
}
