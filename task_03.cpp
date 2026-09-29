#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string productID;
    Node* next;
};

// Function to add a product at the end of the cart
void addProduct(Node*& head, string id) {
    Node* newNode = new Node();
    newNode->productID = id;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// Function to display products in the cart
void displayCart(Node* head) {
    Node* current = head;
    while (current != NULL) {
        cout << current->productID;
        if (current->next != NULL) cout << " -> ";
        current = current->next;
    }
    cout << endl;
}

// Function to remove a product by its Product ID
void removeProduct(Node*& head, string id) {
    if (head == NULL) return;

    // If the node to be deleted is the head
    if (head->productID == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    while (current->next != NULL && current->next->productID != id) {
        current = current->next;
    }

    if (current->next != NULL) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

int main() {
    Node* head = NULL;

    // Adding products to the cart
    addProduct(head, "P101");
    addProduct(head, "P205");
    addProduct(head, "P310");
    addProduct(head, "P415");

    cout << "Shopping Cart:\n";
    displayCart(head);

    // Remove product P310
    string removeID = "P310";
    cout << "Remove Product: " << removeID << endl;
    removeProduct(head, removeID);

    // Display updated cart
    cout << "Updated Cart:\n";
    Node* current = head;
    while (current != NULL) {
        cout << current->productID << " ";
        current = current->next;
    }
    cout << endl;

    return 0;
}