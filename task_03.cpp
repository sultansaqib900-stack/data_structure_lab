#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
};

int main() {
    // Create initial nodes: 10 -> 20 -> 30 -> NULL
    Node* head = new Node();
    Node* second = new Node();
    Node* third = new Node();
    
    head->data = 10;
    head->next = second;
    
    second->data = 20;
    second->next = third;
    
    third->data = 30;
    third->next = NULL;
    
    // Delete the first node
    if (head != NULL) {
        Node* temp = head;     // Temporarily store current head
        head = head->next;     // Move head to the next node
        delete temp;           // Free memory of old head
    }
    
    // Display the Linked List
    cout << "Linked List after deleting the first node: ";
    Node* current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    
    return 0;
}