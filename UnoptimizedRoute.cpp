#include "UnoptimizedRoute.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
#include <cmath>
#include <limits>
#include <stack>

using namespace std;

// Constructor
UnoptimizedRoute::UnoptimizedRoute(int _grid[9][9], int _wasteLevels[10], int _distances[10][10], double _budget, double _fuelCost, double _waste, double _wage, int _obstacle)
    : budget(_budget), fuelCost(_fuelCost), waste(_waste), wage(_wage), obstacle(_obstacle) {

    // Copy the grid
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            grid[i][j] = _grid[i][j];
        }
    }

    // Copy the waste levels
    for (int i = 0; i < 10; ++i) {
        wasteLevels[i] = _wasteLevels[i];
    }

    // Copy the distances
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            distances[i][j] = _distances[i][j];
        }
    }
}

// Greedy algorithm by cost
void UnoptimizedRoute::greedyByCost() {
    totalDistance = 0;
    totalSpendage = 0;
    route.clear();

    int visited[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int now = 1;
    int d = 100;
    int n = 100;
    route.push_back(1); // Start from waste collector
    while (1) {
        for (int next = 2; next < 10; next++) {
            if (now == next) continue;
            if (distances[now][next] == -1) continue;
            if (waste > wasteLevels[next]) continue;

            if (visited[next] == 0 && distances[now][next] < d) {
                d = distances[now][next];
                n = next;
            }
        }

        // If it cannot go to the next, return to waste collector and end the loop
        if (d == 100) {
            if (totalSpendage + distances[now][1] * (wage + fuelCost) <= budget) {
                totalDistance += distances[now][1];
                totalSpendage += distances[now][1] * (wage + fuelCost);
                route.push_back(1);
                break;
            } else {
                while (true) {
                    int last = route.back();
                    route.pop_back();
                    int secondLast = route.back();

                    totalDistance -= distances[secondLast][last];
                    totalSpendage -= distances[secondLast][last] * (wage + fuelCost);
                    if (totalSpendage + distances[secondLast][1] * (wage + fuelCost) <= budget) {
                        totalDistance += distances[secondLast][1];
                        totalSpendage += distances[secondLast][1] * (wage + fuelCost);
                        route.push_back(1);
                        break;
                    }
                }
            }
            break;
        }
        // Move to the next garbage location
        else {
            route.push_back(n);
            visited[n] = 1;
            totalDistance += d;
            totalSpendage += d * (wage + fuelCost);
            now = n;
            d = 100;
            n = 100;
        }
    }
}

// Greedy algorithm by waste level
void UnoptimizedRoute::greedyByWasteLevel() {
    vector<pair<int, int>> temp;
    totalDistance = 0;
    totalSpendage = 0;
    route.clear();

    // Filter locations based on waste level
    for (int i = 2; i < 10; i++) {
        if (wasteLevels[i] >= waste) {
            temp.push_back(make_pair(wasteLevels[i], i));
        }
    }
    sort(temp.begin(), temp.end());

    route.push_back(1); // Start from waste collector
    for (int i = temp.size() - 1; i >= 0; i--) {
        int next = temp[i].second;

        if (totalSpendage + (distances[route.back()][next] + distances[next][1]) * (wage + fuelCost) <= budget) {
            totalSpendage += distances[route.back()][next] * (wage + fuelCost);
            totalDistance += distances[route.back()][next];
            route.push_back(next);
        } else {
            break;
        }
    }
    totalSpendage += distances[route.back()][1] * (wage + fuelCost);
    totalDistance += distances[route.back()][1];
    route.push_back(1); // Return to waste collector
}

// Display the route and summary
void UnoptimizedRoute::displayRoute() {
    cout << "\n=== Route ===" << endl;
    cout << "\033[34m"; // Set text color to blue
    for (int i = 0; i < route.size() - 1; i++) {
        cout << locationNames[route[i]] << " to " << locationNames[route[i + 1]]
             << " - Distance: " << distances[route[i]][route[i + 1]] << " km, Fuel: "
             << distances[route[i]][route[i + 1]] * fuelCost << " RM, Wage: "
             << distances[route[i]][route[i + 1]] * wage << " RM" << endl;
    }
    cout << "\033[0m"; // Reset text color
    cout << endl;

    cout << "=== Summary ===" << endl;
    cout << "\033[32m"; // Set text color to green
    cout << "Total Route : ";
    for (int i = 0; i < route.size() - 1; i++) {
        cout << locationNames[route[i]] << " -> ";
    }
    cout << "Waste Collector" << endl;
    cout << "Total Distance : " << totalDistance << endl;
    cout << "Total Spendage : " << totalSpendage << endl;
    cout << "\033[0m"; // Reset text color
}

// Display the menu and handle user choices
void UnoptimizedRoute::displayMenu() {
    int choice;
    do {
        cout << "\n--------- Unoptimized Route ---------" << endl;
        cout << "|  1. Greedy By Cost                  |" << endl;
        cout << "|  2. Greedy By Waste Level           |" << endl;
        cout << "|  3. Go Back                         |" << endl;
        cout << "------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                greedyByCost();
                displayRoute();
                saveInFile("greedyByCostRoute.txt");
                break;
            case 2:
                greedyByWasteLevel();
                displayRoute();
                saveInFile("greedyByWasteLevel.txt");
                break;
            case 3:
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
                break;
        }
    } while (choice != 3);
}

// Save route information in a file
void UnoptimizedRoute::saveInFile(string filename) {
    ofstream myfile;
    myfile.open(filename);

    myfile << "\n=== Route ===" << endl;
    for (int i = 0; i < route.size() - 1; i++) {
        myfile << locationNames[route[i]] << " to " << locationNames[route[i + 1]]
             << " - Distance: " << distances[route[i]][route[i + 1]] << " km, Fuel: "
             << distances[route[i]][route[i + 1]] * fuelCost << " RM, Wage: "
             << distances[route[i]][route[i + 1]] * wage << " RM" << endl;
    }
    myfile << endl;

    myfile << "=== Summary ===" << endl;
    myfile << "Total Route : ";
    for (int i = 0; i < route.size() - 1; i++) {
        myfile << locationNames[route[i]] << " -> ";
    }
    myfile << "Waste Collector" << endl;
    myfile << "Total Distance : " << totalDistance << endl;
    myfile << "Total Spendage : " << totalSpendage << endl;

    myfile.close();
}
