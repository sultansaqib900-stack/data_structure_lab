#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string patientID;
    Node* next;
};

// Function to add a patient at the end
void addPatient(Node*& head, string id) {
    Node* newNode = new Node();
    newNode->patientID = id;
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

// Function to display the waiting list
void displayPatients(Node* head) {
    Node* current = head;
    while (current != NULL) {
        cout << current->patientID;
        if (current->next != NULL) cout << " -> ";
        current = current->next;
    }
    cout << endl;
}

// Function to remove the first patient (Doctor attends)
void serveFirstPatient(Node*& head) {
    if (head == NULL) {
        cout << "No patients waiting.\n";
        return;
    }

    Node* temp = head;
    cout << "Patient " << temp->patientID << " is being served.\n";
    head = head->next;
    delete temp;
}

int main() {
    Node* head = NULL;

    // Adding patients
    addPatient(head, "P101");
    addPatient(head, "P102");
    addPatient(head, "P103");
    addPatient(head, "P104");

    cout << "Waiting Patients:\n";
    displayPatients(head);

    // Serve the first patient
    serveFirstPatient(head);

    // Display updated queue
    cout << "Updated Queue:\n";
    Node* current = head;
    while (current != NULL) {
        cout << current->patientID << " ";
        current = current->next;
    }
    cout << endl;

    return 0;
}