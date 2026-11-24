#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <utility>
#include <vector>

// ============================================================================
// Data Structure Lab - Lab 09 (Heap and Heap Sort)
// Task 3: Online Shopping Order Sorting (Heap Sort using Binary Tree Nodes)
// ============================================================================

class Order {
public:
    int orderID;
    std::string customerName;
    double orderAmount;
    Order* left;
    Order* right;
    Order* parent;

    Order(int id, const std::string& customer, double amount)
        : orderID(id), customerName(customer), orderAmount(amount),
          left(nullptr), right(nullptr), parent(nullptr) {}
};

struct OrderRecord {
    int orderID;
    std::string customerName;
    double orderAmount;
};

class OrderMaxHeap {
private:
    Order* root;
    int size;

    void swapData(Order* a, Order* b) {
        std::swap(a->orderID, b->orderID);
        std::swap(a->customerName, b->customerName);
        std::swap(a->orderAmount, b->orderAmount);
    }

    void heapifyUp(Order* node) {
        while (node->parent != nullptr && node->orderAmount > node->parent->orderAmount) {
            swapData(node, node->parent);
            node = node->parent;
        }
    }

    void heapifyDown(Order* node) {
        while (node != nullptr) {
            Order* largest = node;

            if (node->left != nullptr && node->left->orderAmount > largest->orderAmount) {
                largest = node->left;
            }
            if (node->right != nullptr && node->right->orderAmount > largest->orderAmount) {
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

    Order* getLastNode() const {
        if (root == nullptr) return nullptr;

        std::queue<Order*> q;
        q.push(root);
        Order* last = nullptr;

        while (!q.empty()) {
            last = q.front();
            q.pop();
            if (last->left != nullptr) q.push(last->left);
            if (last->right != nullptr) q.push(last->right);
        }
        return last;
    }

    void clear(Order* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    OrderMaxHeap() : root(nullptr), size(0) {}

    ~OrderMaxHeap() {
        clear(root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    int getSize() const {
        return size;
    }

    void insert(int orderID, const std::string& customerName, double orderAmount) {
        Order* newNode = new Order(orderID, customerName, orderAmount);
        size++;

        if (root == nullptr) {
            root = newNode;
            return;
        }

        std::queue<Order*> q;
        q.push(root);

        while (!q.empty()) {
            Order* current = q.front();
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

    // Delete root (largest order amount) and return its record
    OrderRecord deleteRoot() {
        OrderRecord maxOrder{root->orderID, root->customerName, root->orderAmount};

        if (size == 1) {
            delete root;
            root = nullptr;
            size = 0;
            return maxOrder;
        }

        Order* last = getLastNode();
        swapData(root, last);

        if (last->parent->left == last) {
            last->parent->left = nullptr;
        } else {
            last->parent->right = nullptr;
        }

        delete last;
        size--;

        heapifyDown(root);
        return maxOrder;
    }

    // Heap Sort using repeated root deletion, placing largest elements at the back
    std::vector<OrderRecord> heapSortAscending() {
        int n = size;
        std::vector<OrderRecord> sortedOrders(n);

        for (int i = n - 1; i >= 0; --i) {
            sortedOrders[i] = deleteRoot();
        }
        return sortedOrders;
    }

    void displayLevelOrder() const {
        if (root == nullptr) {
            std::cout << "Heap is empty.\n";
            return;
        }

        std::cout << std::left << std::setw(12) << "Order ID"
                  << std::setw(22) << "Customer Name"
                  << std::setw(15) << "Order Amount" << "\n";
        std::cout << std::string(49, '-') << "\n";

        std::queue<Order*> q;
        q.push(root);

        while (!q.empty()) {
            Order* current = q.front();
            q.pop();

            std::cout << std::left << std::setw(12) << current->orderID
                      << std::setw(22) << current->customerName
                      << "$" << std::fixed << std::setprecision(2) << current->orderAmount << "\n";

            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "    ONLINE SHOPPING ORDER SORTING (HEAP SORT)       \n";
    std::cout << "====================================================\n\n";

    OrderMaxHeap orderHeap;

    // Insert 7 customer orders into the Max Heap
    std::cout << "Inserting 7 customer orders into the Max Heap...\n";
    orderHeap.insert(3001, "Saqib Sultan", 249.50);
    orderHeap.insert(3002, "Mahnoor Zahid", 89.99);
    orderHeap.insert(3003, "Faisal Iqbal", 540.00);
    orderHeap.insert(3004, "Areeba Saleem", 175.25);
    orderHeap.insert(3005, "Junaid Akram", 410.75);
    orderHeap.insert(3006, "Sadia Farooq", 120.00);
    orderHeap.insert(3007, "Omar Farooq", 325.40);

    std::cout << "\nMax Heap (Level Order Traversal) before Heap Sort:\n";
    orderHeap.displayLevelOrder();

    // Perform Heap Sort using repeated root deletion
    std::vector<OrderRecord> sortedOrders = orderHeap.heapSortAscending();

    std::cout << "\nSales Report - Orders Sorted in Ascending Order (Smallest to Largest):\n";
    std::cout << std::left << std::setw(12) << "Order ID"
              << std::setw(22) << "Customer Name"
              << std::setw(15) << "Order Amount" << "\n";
    std::cout << std::string(49, '-') << "\n";

    for (const auto& order : sortedOrders) {
        std::cout << std::left << std::setw(12) << order.orderID
                  << std::setw(22) << order.customerName
                  << "$" << std::fixed << std::setprecision(2) << order.orderAmount << "\n";
    }

    return 0;
}
