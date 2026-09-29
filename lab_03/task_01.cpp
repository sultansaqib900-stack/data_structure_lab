#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    const int NUM_STUDENTS = 6;
    const int NUM_SUBJECTS = 4;
    
    // 2D array to store marks for 6 students and 4 subjects
    float marks[NUM_STUDENTS][NUM_SUBJECTS];
    
    // Subject and student name labels for clear display
    string subjects[NUM_SUBJECTS] = {"English", "Mathematics", "Programming", "AI"};
    
    // 1. Store the marks of all students in the 2D array
    cout << "--- Enter Marks for " << NUM_STUDENTS << " Students in " << NUM_SUBJECTS << " Subjects ---\n";
    for (int i = 0; i < NUM_STUDENTS; i++) {
        cout << "\nEnter marks for Student " << (i + 1) << ":\n";
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            cout << "  " << subjects[j] << ": ";
            cin >> marks[i][j];
        }
    }
    
    // 2. Display the complete marks table
    cout << "\n\n==================================================\n";
    cout << "                 MARKS TABLE                      \n";
    cout << "==================================================\n";
    cout << setw(10) << "Student";
    for (int j = 0; j < NUM_SUBJECTS; j++) {
        cout << setw(14) << subjects[j];
    }
    cout << "\n--------------------------------------------------\n";
    
    for (int i = 0; i < NUM_STUDENTS; i++) {
        cout << setw(10) << ("S" + to_string(i + 1));
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            cout << setw(14) << marks[i][j];
        }
        cout << endl;
    }
    cout << "==================================================\n";
    
    // 3 & 4. Calculate and display total and average marks of each student
    cout << "\n--- Student Totals and Averages ---\n";
    float totals[NUM_STUDENTS] = {0};
    int topStudentIndex = 0;
    float highestTotal = -1;
    
    for (int i = 0; i < NUM_STUDENTS; i++) {
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            totals[i] += marks[i][j];
        }
        float average = totals[i] / NUM_SUBJECTS;
        
        cout << "Student " << (i + 1) << " -> Total: " << totals[i] 
             << ", Average: " << fixed << setprecision(2) << average << endl;
             
        // Track highest total marks
        if (totals[i] > highestTotal) {
            highestTotal = totals[i];
            topStudentIndex = i;
        }
    }
    
    // 5. Find and display the highest marks in each subject
    cout << "\n--- Highest Marks in Each Subject ---\n";
    for (int j = 0; j < NUM_SUBJECTS; j++) {
        float maxMark = marks[0][j];
        for (int i = 1; i < NUM_STUDENTS; i++) {
            if (marks[i][j] > maxMark) {
                maxMark = marks[i][j];
            }
        }
        cout << subjects[j] << ": " << maxMark << endl;
    }
    
    // 6. Find and display the student with the highest total marks
    cout << "\n--- Top Performing Student ---\n";
    cout << "Student " << (topStudentIndex + 1) << " has the highest total marks of " 
         << highestTotal << "!\n";
         
    return 0;
}
