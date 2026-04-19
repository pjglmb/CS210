/*
Name: Pink Galimba
CS210 Assignment: Temperature Conversion
Date: 04/04/2026

Description:
This program reads city names and their temperatures in Fahrenheit
from a file called FahrenheitTemperature.txt. It converts each
temperature to Celsius and writes the results to a new file called
CelsiusTemperature.txt.
*/


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    ifstream inFS;
    inFS.open("FahrenheitTemperature.txt");

    if (!inFS.is_open()) {
        cout << "Error opening input file." << endl;
        return 1;
    }

    ofstream outFS;
    outFS.open("CelsiusTemperature.txt");

    string city;
    int fahrenheit;
    double celsius;

    while (inFS >> city >> fahrenheit) {
        celsius = (fahrenheit - 32) * 5.0 / 9.0;
        outFS << city << " " << fixed << setprecision(2) << celsius << endl;
    }

    inFS.close();
    outFS.close();

    return 0;
}