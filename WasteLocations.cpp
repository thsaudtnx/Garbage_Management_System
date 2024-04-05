#include "WasteLocations.h"
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

// ANSI escape codes for text colors
#define RESET   "\033[0m"
#define BLUE    "\033[34m"  // Blue color
#define GREEN   "\033[32m"  // Green color
#define RED     "\033[31m"  // Red color

// Constructor
WasteLocations::WasteLocations() {
    // Input Settings
    cout << "=== Initial Settings ===" << endl;
    cout << "Company Budget (RM): ";
    cin >> budget;
    cout << "Fuel Cost (RM per km) : ";
    cin >> fuelCost;
    cout << "Driver Wage (RM per h): ";
    cin >> wage;
    cout << "Number of Obstacles : ";
    cin >> obstacle;
    cout << "Waste Level to proceed: ";
    cin >> waste;

    // Initialize grid to 0
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid[i][j] = 0;
        }
    }

    // Set the other garbage locations randomly
    for (int i = 1; i < 10; i++) {
        bool loop = true;
        while (loop) {
            int x = rand() % 9;
            int y = rand() % 9;
            if (grid[x][y] == 0) {
                grid[x][y] = i;
                loop = false;
            }
        }
    }

    // Set Obstacles
    for (int i = 0; i < obstacle; i++) {
        bool loop = true;
        while (loop) {
            int x = rand() % 9;
            int y = rand() % 9;
            if (grid[x][y] == 0) {
                grid[x][y] = -1;
                loop = false;
            }
        }
    }

    // Generate random waste levels between 0 and 100
    wasteLevels[1] = 100;
    for (int i = 2; i < 10; i++) {
        wasteLevels[i] = rand() % 101;
    }

    // Set the distances to 0
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            distances[i][j] = 0;
        }
    }

    // Calculate the distances
    for (int i = 1; i < 10; i++) {
        bfs(i);
    }
}

// Breadth-first search algorithm to calculate distances
void WasteLocations::bfs(int start) {
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    int visited[9][9];
    queue<tuple<int, int, int>> q;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            visited[i][j] = 0;
            if (grid[i][j] == start) {
                visited[i][j] = 1;
                q.push(make_tuple(i, j, 0));
                distances[start][start] = 0;
                visited[i][j] = 1;
            }
        }
    }

    while (!q.empty()) {
        tuple<int, int, int> cur = q.front();
        q.pop();
        int x = get<0>(cur);
        int y = get<1>(cur);
        int dis = get<2>(cur);

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (0 <= nx && nx < 9 && 0 <= ny && ny < 9) {
                if (visited[nx][ny] == 0 && grid[nx][ny] != -1) {
                    visited[nx][ny] = 1;
                    if (grid[nx][ny] != 0) {
                        distances[start][grid[nx][ny]] = dis + 1;
                    }
                    q.push(make_tuple(nx, ny, dis + 1));
                }
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        if (distances[start][i] == 0 && i != start) {
            distances[start][i] = -1;
        }
    }
}

// Display the waste locations and associated data
void WasteLocations::displayLocations() {
    // Display the Waste Level
    cout << "=== Waste Level ===" << endl;
    cout << BLUE;
    for (int i = 2; i < 10; i++) {
        cout << i << ". " << locationNames[i] << " - Waste Level: " << wasteLevels[i] << "%" << endl;
    }
    cout << RESET << endl;

    // Display the locations in the map
    cout << "=== Garbage Location ===" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (0 < grid[i][j] && grid[i][j] < 10) {
                cout << BLUE << grid[i][j] << " " << RESET;
            } else if (grid[i][j] == -1) {
                cout << RED << grid[i][j] << " " << RESET;
            } else {
                cout << grid[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;

    // Display the distances
    cout << "=== Distances ===" << endl;
    cout << GREEN;
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            cout << distances[i][j] << " ";
        }
        cout << endl;
    }
    cout << RESET;
}
