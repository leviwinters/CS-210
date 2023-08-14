/*
 * CS 210 Grocery-Tracking Program
 *
 * Date: 8/7/2023
 * Author: Levi Winters
 */

#include <iostream>

#include <fstream>

#include <string>

#include <map>

using namespace std;

class GroceryTracker {
private: map < string,
    int > itemFrequency; // Store how many times each item appears

public:
    // Show how often each item was purchased
    void itemFrequencies() {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Create a visual representation of item purchase frequency
    void itemHistogram() {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

    // Execute the grocery tracking program
    void run() {
        // Open the file containing purchased items
        ifstream inputFile("Grocery_Input_File.txt");
        if (!inputFile.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        string item;
        // Count how many times each item was purchased
        while (inputFile >> item) {
            itemFrequency[item]++; // Increment the count for each item
        }

        inputFile.close();

        // Open the output file for writing
        ofstream outputFile("frequency.dat");
        if (!outputFile.is_open()) {
            cout << "Error creating output file." << endl;
            return;
        }

        // Write the item frequencies to the output file
        for (const auto& pair : itemFrequency) {
            outputFile << pair.first << " " << pair.second << endl;
        }

        outputFile.close();

        int choice;
        do {
            // Display user menu
            cout << "Grocery-Tracking Program" << endl;
            cout << "1. Check how often an item was purchased." << endl;
            cout << "2. See a list of purchased item frequencies." << endl;
            cout << "3. Show a histogram of item purchases." << endl;
            cout << "4. Exit the program." << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            // Handle invalid input
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }

            switch (choice) {
            case 1: {
                string userInput;
                cout << "Enter an item you wish to look for (starting with a capital letter): ";
                cin >> userInput;

                // Find and display how often the requested item was purchased
                if (itemFrequency.find(userInput) != itemFrequency.end()) {
                    int frequency = itemFrequency[userInput];
                    cout << userInput << " " << frequency << endl;
                }
                else {
                    cout << userInput << " not found." << endl;
                }
                break;
            }
            case 2:
                // Show the list of purchased items and their frequencies
                itemFrequencies();
                break;
            case 3:
                // Display a visual histogram of purchase frequencies
                itemHistogram();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                // Input validation
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
            }
        } while (choice != 4);
    }
};

int main() {
    // Create an instance of the GroceryTracker class
    GroceryTracker tracker;
    // Run the grocery tracking program
    tracker.run();

    return 0;
}
