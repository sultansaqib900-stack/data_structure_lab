#include <iostream>
using namespace std;

class Node {
public:
    int rollNumber;
    Node* next;
};

// Function to add a student at the end
void appendStudent(Node*& head, int roll) {
    Node* newNode = new Node();
    newNode->rollNumber = roll;
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

// Function to display all registered students
void displayStudents(Node* head) {
    Node* current = head;
    cout << "Registered Students:\n";
    while (current != NULL) {
        cout << current->rollNumber;
        if (current->next != NULL) cout << " -> ";
        current = current->next;
    }
    cout << endl;
}

// Function to search for a student using Roll Number
void searchStudent(Node* head, int roll) {
    Node* current = head;
    bool found = false;
    while (current != NULL) {
        if (current->rollNumber == roll) {
            found = true;
            break;
        }
        current = current->next;
    }

    cout << "Enter Roll Number to Search: " << roll << endl;
    if (found) {
        cout << "Student Found\n";
    } else {
        cout << "Student Not Found\n";
    }
}

int main() {
    Node* head = NULL;

    // Adding students as per example
    appendStudent(head, 101);
    appendStudent(head, 105);
    appendStudent(head, 108);
    appendStudent(head, 112);

    // Display registered students
    displayStudents(head);

    // Search for a student
    searchStudent(head, 108);

    return 0;
}