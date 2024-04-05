#ifndef UNOPTIMIZEDROUTE_H_INCLUDED
#define UNOPTIMIZEDROUTE_H_INCLUDED

#include <vector>
#include <string>

using namespace std;

class UnoptimizedRoute {
public:
    // Member variables
    double totalDistance = 0; // Total distance traveled
    double totalSpendage = 0; // Total cost incurred
    vector<int> route; // Stores the route as a sequence of locations
    string locationNames[10] = {"", "Waste Collector", "Seoul", "Suwon", "Ulsan", "Jeju", "Busan", "Incheon", "Daegu", "Daejeon"}; // Names of locations
    int grid[9][9]; // Grid representing the map
    int wasteLevels[10]; // Waste levels at each location
    int distances[10][10]; // Distances between locations

    // Parameters
    double budget; // Budget for the route
    double fuelCost; // Cost of fuel per kilometer
    double waste; // Minimum waste level required for pickup
    double wage; // Wage of the driver
    int obstacle; // Obstacle indicator

    // Constructor
    UnoptimizedRoute(int _grid[9][9], int _wasteLevels[10], int _distances[10][10], double _budget, double _fuelCost, double _waste, double _wage, int _obstacle);

    // Greedy algorithm to find the route based on cost
    void greedyByCost();

    // Greedy algorithm to find the route based on waste level
    void greedyByWasteLevel();

    // Display the route and summary
    void displayRoute();

    // Display the menu for selecting route optimization method
    void displayMenu();

    // Save route information to a file
    void saveInFile(string filename);
};

#endif // UNOPTIMIZEDROUTE_H_INCLUDED
