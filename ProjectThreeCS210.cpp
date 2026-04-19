// Name: Pink Galimba
// CS210 Project Three - Corner Grocer
// Date: 4/19/2026


#include "GroceryTracker.h"

#include <iostream>

int main() {
    GroceryTracker tracker;

    if (!tracker.loadInputFile()) {
        std::cerr << "Error: Could not read CS210_Project_Three_Input_File.txt\n";
        std::cerr << "Place the file in the program's working directory (usually next to the .exe).\n";
        return 1;
    }

    std::cout << "Data loaded from CS210_Project_Three_Input_File.txt\n";
    if (!tracker.writeFrequencyBackup()) {
        std::cerr << "Warning: Could not write frequency.dat (check folder permissions).\n";
    }
    else {
        std::cout << "Backup written to frequency.dat\n";
    }
    tracker.runMenu();
    return 0;
}