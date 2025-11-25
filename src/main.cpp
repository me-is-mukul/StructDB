#include "../include/Graph.h"
#include <iostream>
#include <cstdlib>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#define CLEAR   "\033[2J\033[1;1H"

using namespace std;

void printOptions(const string &current, const vector<string> &neighbors) {
    cout << CLEAR; // clear screen
    cout << BOLD << BLUE << "----------------------------------------\n";
    cout << "       Study Graph Navigation Menu      \n";
    cout << "----------------------------------------" << RESET << "\n\n";

    cout << GREEN << "You are at: " << RESET << BOLD << CYAN << current << RESET << "\n\n";

    cout << YELLOW << "Available options:" << RESET << "\n";

    int idx = 1;
    for (const auto &nbr : neighbors) {
        cout << "  " << GREEN << idx++ << ". " << RESET << CYAN << nbr << RESET << "\n";
    }

    cout << "\n" << BLUE << "Enter the number of your choice, or type '" 
         << RED << "exit" << BLUE << "' to quit:" << RESET << "\n";
}

int main() {
    Graph g;
    g.addPathFromCSV("src/data.csv");

    cout << CLEAR;
    cout << BOLD << GREEN << "Welcome to the Study Graph Navigator\n\n" << RESET;

    cout << YELLOW << "Press 1 to Start\n";
    cout << "Press 2 to Exit" << RESET << "\n\n> ";

    int choice;
    cin >> choice;

    if (choice == 2) {
        cout << RED << "\nExiting program.\n" << RESET;
        return 0;
    }

    string current = "start";

    while (true) {
        vector<string> neighbors = g.getNeighbors(current);

        if (neighbors.empty()) {
            cout << RED << "\nNo further paths from '" << current << "'.\n" << RESET;
            break;
        }

        printOptions(current, neighbors);

        string option;
        cout << "> ";
        cin >> option;

        if (option == "exit") {
            cout << RED << "\nExiting navigator...\n" << RESET;
            break;
        }

        // Check if user entered a number
        bool isNum = all_of(option.begin(), option.end(), ::isdigit);

        if (isNum) {
            int idx = stoi(option);
            if (idx >= 1 && idx <= (int)neighbors.size()) {
                current = neighbors[idx - 1];
                continue;
            } else {
                cout << RED << "\nInvalid choice. Try again.\n" << RESET;
                sleep(1);
                continue;
            }
        }

        // If user entered name directly
        auto it = find(neighbors.begin(), neighbors.end(), option);
        if (it != neighbors.end()) {
            current = option;
            continue;
        }

        cout << RED << "\nInvalid input. Please choose again.\n" << RESET;
        sleep(1);
    }

    return 0;
}
