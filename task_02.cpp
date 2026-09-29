#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
};

int main() {
    // Create initial nodes: 10 -> 30 -> NULL
    Node* head = new Node();
    Node* second = new Node();
    
    head->data = 10;
    head->next = second;
    
    second->data = 30;
    second->next = NULL;
    
    // Insert 20 at position 2
    int pos = 2;
    Node* newNode = new Node();
    newNode->data = 20;
    
    Node* current = head;
    for (int i = 1; i < pos - 1 && current != NULL; i++) {
        current = current->next;
    }
    
    if (current != NULL) {
        newNode->next = current->next;
        current->next = newNode;
    }
    
    // Display the Linked List
    cout << "Linked List after inserting at position 2: ";
    current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    
    return 0;
}