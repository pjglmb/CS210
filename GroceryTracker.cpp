#include "GroceryTracker.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

GroceryTracker::GroceryTracker() = default;

std::string GroceryTracker::trim(const std::string& s) {
    const auto start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return {};
    }
    const auto end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

std::string GroceryTracker::toLowerKey(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (unsigned char c : s) {
        out.push_back(static_cast<char>(std::tolower(c)));
    }
    return out;
}

bool GroceryTracker::loadInputFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        return false;
    }

    m_frequencyByKey.clear();
    m_displayName.clear();

    std::string line;
    while (std::getline(in, line)) {
        const std::string item = trim(line);
        if (item.empty()) {
            continue;
        }
        // Lowercase key groups "Apples" and "apples"; display keeps first spelling seen.
        const std::string key = toLowerKey(item);
        if (m_displayName.find(key) == m_displayName.end()) {
            m_displayName[key] = item;
        }
        ++m_frequencyByKey[key];
    }

    return true;
}

bool GroceryTracker::writeFrequencyBackup(const std::string& filename) const {
    std::ofstream out(filename, std::ios::trunc);
    if (!out) {
        return false;
    }
    // Same display order as printAllFrequencies: alphabetical by normalized key.
    for (const auto& pair : m_frequencyByKey) {
        const std::string& key = pair.first;
        const int count = pair.second;
        const auto it = m_displayName.find(key);
        const std::string& name = (it != m_displayName.end()) ? it->second : key;
        out << name << ' ' << count << '\n';
    }
    return true;
}

int GroceryTracker::getFrequency(const std::string& item) const {
    const std::string key = toLowerKey(trim(item));
    if (key.empty()) {
        return 0;
    }
    const auto it = m_frequencyByKey.find(key);
    return (it != m_frequencyByKey.end()) ? it->second : 0;
}

void GroceryTracker::printAllFrequencies() const {
    if (m_frequencyByKey.empty()) {
        std::cout << "No items loaded.\n";
        return;
    }
    for (const auto& pair : m_frequencyByKey) {
        const std::string& key = pair.first;
        const int count = pair.second;
        const auto it = m_displayName.find(key);
        const std::string& name = (it != m_displayName.end()) ? it->second : key;
        std::cout << name << " " << count << '\n';
    }
}

void GroceryTracker::printHistogram() const {
    if (m_frequencyByKey.empty()) {
        std::cout << "No items loaded.\n";
        return;
    }
    for (const auto& pair : m_frequencyByKey) {
        const std::string& key = pair.first;
        const int count = pair.second;
        const auto it = m_displayName.find(key);
        const std::string& name = (it != m_displayName.end()) ? it->second : key;
        std::cout << name << ' ';
        for (int i = 0; i < count; ++i) {
            std::cout << '*';
        }
        std::cout << '\n';
    }
}

void GroceryTracker::runMenu() {
    while (true) {
        std::cout << "\nCorner Grocer — Item Frequency Menu\n";
        std::cout << "1) Search for the frequency of a specific item\n";
        std::cout << "2) Print all item frequencies\n";
        std::cout << "3) Print a histogram of item frequencies\n";
        std::cout << "4) Exit the program\n";
        std::cout << "Enter your choice (1-4): ";

        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cout << "\nEnd of input; exiting.\n";
            break;
        }

        // Parse menu choice without failing on non-numeric input (no cin >> int stuck state).
        std::istringstream iss(line);
        int choice = 0;
        if (!(iss >> choice) || choice < 1 || choice > 4) {
            std::cout << "Invalid choice. Please enter a number from 1 to 4.\n";
            continue;
        }

        char extra = 0;
        if (iss >> extra) {
            std::cout << "Invalid choice. Please enter a single number from 1 to 4.\n";
            continue;
        }

        if (choice == 1) {
            std::cout << "Enter an item name: ";
            if (!std::getline(std::cin, line)) {
                std::cout << "\nEnd of input; exiting.\n";
                break;
            }
            const int n = getFrequency(line);
            const std::string trimmed = trim(line);
            if (trimmed.empty()) {
                std::cout << "No item entered.\n";
            } else {
                std::cout << "\"" << trimmed << "\" appears " << n << " time(s).\n";
            }
        } else if (choice == 2) {
            printAllFrequencies();
        } else if (choice == 3) {
            printHistogram();
        } else if (choice == 4) {
            std::cout << "Goodbye.\n";
            break;
        }
    }
}
