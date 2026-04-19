/*
 * CS 210 Project One: Chada Tech Clocks
 * Author: Pink Galimba
 * Description: Displays 12-hour and 24-hour clocks simultaneously with a menu
 *              to add one hour, one minute, or one second. Both clocks update
 *              from a single internal 24-hour time. Simulation only.
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

 // ----- Function Prototypes -----
std::string format12h(int hour24, int minute, int second);
std::string format24h(int hour24, int minute, int second);
void displayClocks(int hour24, int minute, int second);
void addOneSecond(int& hour24, int& minute, int& second);
void addOneMinute(int& hour24, int& minute, int& second);
void addOneHour(int& hour24);
void displayMenu();
void getInitialTime(int& hour24, int& minute, int& second);

// ----- MAIN -----
int main() {
    int hour24, minute, second;
    int choice;

    // Get starting time from user
    getInitialTime(hour24, minute, second);

    // Main loop
    while (true) {
        displayClocks(hour24, minute, second);
        displayMenu();

        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            addOneHour(hour24);
        }
        else if (choice == 2) {
            addOneMinute(hour24, minute, second);
        }
        else if (choice == 3) {
            addOneSecond(hour24, minute, second);
        }
        else if (choice == 4) {
            std::cout << "Exiting program.\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

// ----- Get Initial Time -----
void getInitialTime(int& hour24, int& minute, int& second) {
    std::cout << "Enter hour (0-23): ";
    std::cin >> hour24;

    std::cout << "Enter minute (0-59): ";
    std::cin >> minute;

    std::cout << "Enter second (0-59): ";
    std::cin >> second;
}

// ----- Format 12-hour -----
std::string format12h(int hour24, int minute, int second) {
    int hour12 = hour24 % 12;
    if (hour12 == 0) hour12 = 12;

    std::string ampm = (hour24 < 12) ? "AM" : "PM";

    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << hour12 << ":"
        << std::setw(2) << minute << ":"
        << std::setw(2) << second << " " << ampm;

    return oss.str();
}

// ----- Format 24-hour -----
std::string format24h(int hour24, int minute, int second) {
    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << hour24 << ":"
        << std::setw(2) << minute << ":"
        << std::setw(2) << second;

    return oss.str();
}

// ----- Display Clocks -----
void displayClocks(int hour24, int minute, int second) {
    std::string s12 = format12h(hour24, minute, second);
    std::string s24 = format24h(hour24, minute, second);

    std::cout << "\n***************************    ***************************\n";
    std::cout << "*     12-Hour Clock      *    *     24-Hour Clock      *\n";
    std::cout << "*     " << s12 << "     *    *       " << s24 << "       *\n";
    std::cout << "***************************    ***************************\n";
}

// ----- Display Menu -----
void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1 - Add One Hour\n";
    std::cout << "2 - Add One Minute\n";
    std::cout << "3 - Add One Second\n";
    std::cout << "4 - Exit Program\n\n";
}

// ----- Add One Second -----
void addOneSecond(int& hour24, int& minute, int& second) {
    second++;
    if (second >= 60) {
        second = 0;
        minute++;
    }
    if (minute >= 60) {
        minute = 0;
        hour24++;
    }
    if (hour24 >= 24) {
        hour24 = 0;
    }
}

// ----- Add One Minute -----
void addOneMinute(int& hour24, int& minute, int& second) {
    minute++;
    if (minute >= 60) {
        minute = 0;
        hour24++;
    }
    if (hour24 >= 24) {
        hour24 = 0;
    }
}

// ----- Add One Hour -----
void addOneHour(int& hour24) {
    hour24 = (hour24 + 1) % 24;
}