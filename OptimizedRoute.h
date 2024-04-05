#ifndef OPTIMIZEDROUTE_H
#define OPTIMIZEDROUTE_H

#include <vector>
#include <string>

using namespace std;

class OptimizedRoute {
public:
    // Member variables
    double totalDistance = 0;
    double totalSpendage = 0;
    vector<int> route;
    string locationNames[10] = {"", "Waste Collector", "Seoul", "Suwon", "Ulsan", "Jeju", "Busan", "Incheon", "Daegu", "Daejeon"};
    int grid[9][9];
    int wasteLevels[10];
    int distances[10][10];
    double budget;
    double fuelCost;
    double waste;
    double wage;
    int obstacle;
    int parent[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Parent array for disjoint set

    // Constructor
    OptimizedRoute(int _grid[9][9], int _wasteLevels[10], int _distances[10][10], double _budget, double _fuelCost, double _waste, double _wage, int _obstacle);

    // Member functions
    int findParent(int x); // Find parent of a node in disjoint set
    bool hasSameParent(int x, int y); // Check if two nodes have the same parent in disjoint set
    void setUnion(int x, int y); // Union operation in disjoint set
    void kruskal(); // Kruskal's algorithm for finding the minimum spanning tree
    void floydWarshall(); // Floyd Warshall algorithm for finding shortest paths
    void displayRoute(); // Display route and summary
    void displayMenu(); // Display menu for optimized route options
    void saveInFile(string filename); // Save route information in a file
};

#endif // OPTIMIZEDROUTE_H
