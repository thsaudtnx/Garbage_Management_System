#include "OptimizedRoute.h"
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

// Constructor for OptimizedRoute class
OptimizedRoute::OptimizedRoute(int _grid[9][9], int _wasteLevels[10], int _distances[10][10], double _budget, double _fuelCost, double _waste, double _wage, int _obstacle)
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
// Kruskal's algorithm for finding the minimum spanning tree
void OptimizedRoute::kruskal(){
    totalDistance = 0;
    totalSpendage = 0;
    route.clear();

    vector<pair<int, pair<int, int>>> graph;
    vector<pair<int, int>> temp;

    for (int from=1;from<10;from++){
        for (int to=1;to<10;to++){
            if (from != to && distances[from][to] != -1 && distances[to][from] != -1 && wasteLevels[to] >= waste && wasteLevels[from] >= waste){
                graph.push_back(make_pair(distances[from][to], make_pair(from, to)));
            }
        }
    }

    sort(graph.begin(), graph.end());

    for (int i=0;i<graph.size();i++){
        int first = graph[i].second.first;
        int second = graph[i].second.second;
        int dis = graph[i].first;

        if (totalSpendage + dis * (wage + fuelCost) > budget) break;

        if (!hasSameParent(first, second)){
            setUnion(first, second);
            totalDistance += dis;
            totalSpendage += dis *(wage + fuelCost);
            temp.push_back(make_pair(first, second));
        }
    }


    // Make the Kruskal Route path
    route.push_back(1);
    int used[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    while (true){
        for (int i=0;i<temp.size();i++){
            if (used[i] == 0){
                if (route.back() == temp[i].first){
                    route.push_back(temp[i].second);
                    used[i] = 1;
                } else if (route.back() == temp[i].second){
                    route.push_back(temp[i].first);
                    used[i] = 1;
                }
            }
        }
        int sum = 0;
        for (int use : used){
            sum += use;
        }
        if (sum == temp.size()) break;
    }


    for (int i=0;i<route.size();i++){
        if (totalSpendage + distances[route.back()][1] * (wage + fuelCost) <= budget ){
            totalSpendage += distances[route.back()][1] * (wage + fuelCost);
            totalDistance += distances[route.back()][1];
            route.push_back(1);
            break;
        } else {
            int last = route.back();
            route.pop_back();
            int secondLast = route.back();
            totalDistance -= distances[secondLast][last];
            totalSpendage -= distances[secondLast][last] * (wage + fuelCost);
        }
    }

}
// Function to find the parent of a node in disjoint set
int OptimizedRoute::findParent(int x){
  if (parent[x] == x) return x;
  else return parent[x] = findParent(parent[x]);
}
// Function to check if two nodes have the same parent in disjoint set
bool OptimizedRoute::hasSameParent(int x, int y){
  x = findParent(x);
  y = findParent(y);
  return x==y;
}
// Function to perform union operation in disjoint set
void OptimizedRoute::setUnion(int x, int y){
  x = findParent(x);
  y = findParent(y);
  if (x!=y){
    parent[y] = x;
  }
}
// Floyd Warshall algorithm for finding shortest paths
void OptimizedRoute::floydWarshall(){
    totalDistance = 0;
    totalSpendage = 0;
    route.clear();

    int minDistTable[10][10];
    for (int i=0;i<10;i++){
        for (int j=0;j<10;j++){
            if (i==j) minDistTable[i][j] = 0;
            else minDistTable[i][j] = 100;
        }
    }

    for (int from=1;from<10;from++){
        for (int to=1;to<10;to++){
            if (from != to && distances[from][to] != -1 && distances[to][from] != -1 && wasteLevels[to] >= waste && wasteLevels[from] >= waste){
                minDistTable[from][to] = distances[from][to];
            }
        }
    }

    for (int k = 1; k < 10; k++) {
        for (int i = 1; i < 10; i++) {
            for (int j = 1; j < 10; j++) {
                if (minDistTable[i][j] > minDistTable[i][k] + minDistTable[k][j])
                    minDistTable[i][j] = minDistTable[i][k] + minDistTable[k][j];
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << minDistTable[i][j] << " ";
        }
        cout << endl;
    }

    int visited[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int now = 1;
    int d = 100;
    int n = 100;
    route.push_back(1); // Depart in waste collector
    while (1){
        for (int next=2;next<10;next++){
            if (now == next) continue;
            if (distances[now][next] == -1) continue;
            if (waste > wasteLevels[next]) continue;

            if (visited[next] == 0 && distances[now][next] < d){
                d = distances[now][next];
                n = next;
            }
        }

        // If it cannot go to the next, go to waste collector and end the loop
        if (d==100){
            if (totalSpendage + distances[now][1]*(wage + fuelCost) <= budget){
                totalDistance += distances[now][1];
                totalSpendage += distances[now][1]*(wage + fuelCost);
                route.push_back(1);
                break;
            } else {
                while(true){
                  int last = route.back();
                  route.pop_back();
                  int secondLast = route.back();

                  totalDistance -= distances[secondLast][last];
                  totalSpendage -= distances[secondLast][last] * (wage + fuelCost);
                  if (totalSpendage + distances[secondLast][1]*(wage + fuelCost) <= budget){
                        totalDistance += distances[secondLast][1];
                        totalSpendage += distances[secondLast][1]*(wage + fuelCost);
                        route.push_back(1);
                        break;
                  }
                }
            }
            break;
        }
        // Move to next garbage location
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
// Function to display the route and summary
void OptimizedRoute::displayRoute(){

    cout << "\n=== Route ===" << endl;
    cout << "\033[34m";
    for (int i=0;i<route.size()-1;i++){
        cout << locationNames[route[i]] << " to " << locationNames[route[i+1]]
            << " - Distance: " << distances[route[i]][route[i+1]] << " km, Fuel: "
            << distances[route[i]][route[i+1]] * fuelCost << " RM, Wage: "
            << distances[route[i]][route[i+1]] * wage << " RM" << endl;
    }
    cout << "\033[0m";
    cout << endl;

    cout << "=== Summary ===" << endl;
    cout << "\033[32m";
    cout << "Total Route : ";
    for (int i=0;i<route.size()-1;i++){
        cout << locationNames[route[i]] << " -> ";
    }
    cout << "Waste Collector" << endl;
    cout << "Total Distance : " << totalDistance << endl;
    cout << "Total Spendage : " << totalSpendage << endl;
    cout << "\033[0m";
}
// Function to display the menu for optimized route options
void OptimizedRoute::displayMenu(){
    int choice;
    do {
        cout << "\n---------- Optimized Route ----------" << endl;
        cout << "|  1. Kruskal                         |" << endl;
        cout << "|  2. Floyd Warshall                  |" << endl;
        cout << "|  3. Go Back                         |" << endl;
        cout << "------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
        case 1:
            kruskal();
            displayRoute();
            saveInFile("KruskalRoute.txt");
            break;
        case 2:
            floydWarshall();
            displayRoute();
            saveInFile("floydWarshall.txt");
            break;
        case 3:
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
            break;
        }
    }while (choice != 3);
}
// Function to save route information in a file
void OptimizedRoute::saveInFile(string filename){
    ofstream myfile;
    myfile.open(filename);

    myfile << "\n=== Route ===" << endl;
    for (int i=0;i<route.size()-1;i++){
        myfile << locationNames[route[i]] << " to " << locationNames[route[i+1]]
            << " - Distance: " << distances[route[i]][route[i+1]] << " km, Fuel: "
            << distances[route[i]][route[i+1]] * fuelCost << " RM, Wage: "
            << distances[route[i]][route[i+1]] * wage << " RM" << endl;
    }
    myfile << endl;

    myfile << "=== Summary ===" << endl;
    myfile << "Total Route : ";
    for (int i=0;i<route.size()-1;i++){
        myfile << locationNames[route[i]] << " -> ";
    }
    myfile << "Waste Collector" << endl;
    myfile << "Total Distance : " << totalDistance << endl;
    myfile << "Total Spendage : " << totalSpendage << endl;

    myfile.close();
}
