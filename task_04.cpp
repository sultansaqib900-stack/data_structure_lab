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
    
    // Reverse logic using three pointers
    Node* prev = NULL;
    Node* current = head;
    Node* nextNode = NULL;
    
    while (current != NULL) {
        nextNode = current->next; // Store next node
        current->next = prev;     // Reverse the link
        prev = current;           // Move prev forward
        current = nextNode;       // Move current forward
    }
    head = prev;                  // Update head to the new front
    
    // Display the Reversed Linked List
    cout << "Reversed Linked List: ";
    current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    
    return 0;
}