#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
};

int main() {
    // Create initial nodes: 20 -> 30 -> NULL
    Node* head = new Node();
    Node* second = new Node();
    
    head->data = 20;
    head->next = second;
    
    second->data = 30;
    second->next = NULL;
    
    // Create a new node to insert at the beginning
    Node* newNode = new Node();
    newNode->data = 10;
    newNode->next = head; // Point new node to the old head
    head = newNode;       // Update head to point to the new node
    
    // Display the Linked List
    cout << "Linked List after inserting at the beginning: ";
    Node* current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    
    return 0;
}