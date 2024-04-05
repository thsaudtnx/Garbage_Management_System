#include <iostream>          // Include standard input-output stream library
#include "Authentication.h" // Include the declaration of Authentication class

using namespace std;

// Definition of the member function authenticateUser() of the Authentication class
void Authentication::authenticateUser() {
    // Loop until user authentication succeeds
    while (1) {
        string username;
        string password;

        // Prompt user for username and password
        cout << "=== User Authentication ===" << endl;
        cout << "username: ";
        cin >> username;
        cout << "password: ";
        cin >> password;

        // Check if entered username and password match the expected values
        if (username == "username" && password == "password") {
            // Display authentication success message in green color
            cout << "\033[32m" << "Authentication Success\n" << "\033[0m" << endl;
            break; // Exit the loop as authentication succeeded
        } else {
            // Display authentication failure message in red color
            cout << "\033[31m" << "Authentication Fail\n" << "\033[0m" << endl;
        }
    }
}
