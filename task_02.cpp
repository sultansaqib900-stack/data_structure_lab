#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    // 1. Create and initialize the 2D parking array (4 rows x 5 columns)
    // 0 = Empty space, 1 = Occupied space
    std::vector<std::vector<int>> parking_lot = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0}
    };

    // 2. Display the complete parking layout
    std::cout << "--- Current Parking Layout ---\n";
    std::cout << "        Col 0  Col 1  Col 2  Col 3  Col 4\n";
    for (int i = 0; i < 4; ++i) {
        std::cout << "Row " << i << ": [  ";
        for (int j = 0; j < 5; ++j) {
            std::cout << parking_lot[i][j] << "      ";
        }
        std::cout << "]\n";
    }
    std::cout << "-------------------------------------------\n";

    // 3 & 4. Count occupied and empty spaces
    int total_occupied = 0;
    int total_empty = 0;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (parking_lot[i][j] == 1) {
                total_occupied++;
            } else {
                total_empty++;
            }
        }
    }

    std::cout << "Total Occupied Spaces: " << total_occupied << "\n";
    std::cout << "Total Empty Spaces: " << total_empty << "\n";

    // 7. Display the total parking capacity and current occupancy
    int total_capacity = 4 * 5;
    double occupancy_rate = (static_cast<double>(total_occupied) / total_capacity) * 100.0;
    
    std::cout << "Total Capacity: " << total_capacity << " spaces\n";
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Current Occupancy Rate: " << occupancy_rate << "%\n";
    std::cout << "-------------------------------------------\n";

    // 5. Ask the user to enter a row and column number
    int user_row, user_col;
    std::cout << "Enter row number (0-3): ";
    std::cin >> user_row;
    std::cout << "Enter column number (0-4): ";
    std::cin >> user_col;

    // 6. Check whether the selected parking space is available or occupied
    if (user_row >= 0 && user_row < 4 && user_col >= 0 && user_col < 5) {
        int selected_space = parking_lot[user_row][user_col];
        
        if (selected_space == 0) {
            std::cout << "\nSuccess: Space at Row " << user_row 
                      << ", Column " << user_col << " is EMPTY. You can park here!\n";
        } else {
            std::cout << "\nSorry: Space at Row " << user_row 
                      << ", Column " << user_col << " is OCCUPIED.\n";
        }
    } else {
        std::cout << "\nInvalid input! Please enter a row between 0-3 and a column between 0-4.\n";
    }

    return 0;
}
