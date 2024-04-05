#include "OptimizedRoute.h"    // Include the declaration of OptimizedRoute class
#include "OptimizedRoute.cpp"  // Include the implementation of OptimizedRoute class
#include "UnoptimizedRoute.h"  // Include the declaration of UnoptimizedRoute class
#include "UnoptimizedRoute.cpp"// Include the implementation of UnoptimizedRoute class
#include "WasteLocations.h"    // Include the declaration of WasteLocations class
#include "WasteLocations.cpp"  // Include the implementation of WasteLocations class
#include "Authentication.h"    // Include the declaration of Authentication class
#include "Authentication.cpp"  // Include the implementation of Authentication class
#include <iostream>            // Include standard input-output stream library

using namespace std;

int main() {
    // Create an instance of the Authentication class
    Authentication authentication;
    // Authenticate the user
    authentication.authenticateUser();

    // Create an instance of the WasteLocations class
    WasteLocations wasteLocations;

    // Create an instance of the UnoptimizedRoute class
    // Pass the necessary parameters to the constructor
    UnoptimizedRoute unoptimizedRoute(
        wasteLocations.grid,
        wasteLocations.wasteLevels,
        wasteLocations.distances,
        wasteLocations.budget,
        wasteLocations.fuelCost,
        wasteLocations.waste,
        wasteLocations.wage,
        wasteLocations.obstacle
    );

    // Create an instance of the OptimizedRoute class
    // Pass the necessary parameters to the constructor
    OptimizedRoute optimizedRoute(
        wasteLocations.grid,
        wasteLocations.wasteLevels,
        wasteLocations.distances,
        wasteLocations.budget,
        wasteLocations.fuelCost,
        wasteLocations.waste,
        wasteLocations.wage,
        wasteLocations.obstacle
    );

    int choice;
    // Display menu and prompt user for choice until they choose to exit
    do {
        cout << "\n--------------- Menu ---------------" << endl;
        cout << "|  1. Display Garbage Locations     |" << endl;
        cout << "|  2. Unoptimized Route             |" << endl;
        cout << "|  3. Optimized Route               |" << endl;
        cout << "|  4. Exit                          |" << endl;
        cout << "------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Perform actions based on user's choice
        switch (choice) {
            case 1:
                // Display garbage locations
                wasteLocations.displayLocations();
                break;
            case 2:
                // Display unoptimized route menu
                unoptimizedRoute.displayMenu();
                break;
            case 3:
                // Display optimized route menu
                optimizedRoute.displayMenu();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                // Display error message for invalid choice
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    } while (choice != 4);  // Continue loop until user chooses to exit

    return 0;
}
