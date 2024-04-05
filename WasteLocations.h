#ifndef WASTELOCATIONS_H_INCLUDED
#define WASTELOCATIONS_H_INCLUDED

#include <string>

using namespace std;

// Class representing waste locations and associated data
class WasteLocations {
public:
    // Member variables
    string locationNames[10] = {"", "Waste Collector", "Seoul", "Suwon", "Ulsan", "Jeju", "Busan", "Incheon", "Daegu", "Daejeon"}; // Names of waste locations
    int grid[9][9]; // Grid representing the map
    int wasteLevels[10]; // Waste levels at each location
    int distances[10][10]; // Distances between locations
    double budget; // Budget for waste management
    double fuelCost; // Cost of fuel per kilometer
    double waste; // Minimum waste level required for pickup
    double wage; // Wage of the workers
    int obstacle; // Indicator for obstacles

    // Constructor
    WasteLocations();

    // Breadth-first search algorithm
    void bfs(int start);

    // Display the waste locations and associated data
    void displayLocations();
};

#endif // WASTELOCATIONS_H_INCLUDED
