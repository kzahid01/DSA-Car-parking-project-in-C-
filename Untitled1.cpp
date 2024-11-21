#include <iostream>
#include <string>

#define MAX_SIZE 100 // Maximum capacity of the parking lot

using namespace std;

// Stack implementation for parking lot
class ParkingStack {
private:
    int top;
    int blockCounter; // Keeps track of the next unique block number
    int totalRevenue; // Tracks total revenue generated
    struct Car {
        string licensePlate;
        string ownerName;
        string vehicleType; // Vehicle type (Car, Motorbike, Van)
        int blockNumber;    // Unique block number
    } stack[MAX_SIZE];

public:
    ParkingStack() : top(-1), blockCounter(1), totalRevenue(0) {}

    // Park a vehicle (push onto the stack)
    bool parkVehicle(const string& licensePlate, const string& ownerName, const string& vehicleType) {
        if (top >= MAX_SIZE - 1) {
            cout << "Parking lot is full (Stack overflow).\n";
            return false;
        }

        int rate = getRate(vehicleType);
        if (rate == -1) {
            cout << "Invalid vehicle type entered. Parking failed.\n";
            return false;
        }

        top++;
        stack[top].licensePlate = licensePlate;
        stack[top].ownerName = ownerName;
        stack[top].vehicleType = vehicleType;
        stack[top].blockNumber = blockCounter++; // Assign and increment block number
        totalRevenue += rate;

        cout << "Vehicle with license plate " << licensePlate << " parked at block " << stack[top].blockNumber
             << ". Vehicle type: " << vehicleType << ".\n";
        return true;
    }

    // Remove a specific vehicle by license plate
    bool removeVehicle(const string& licensePlate) {
        if (top < 0) {
            cout << "Parking lot is empty (Stack underflow).\n";
            return false;
        }

        // Search for the vehicle in the stack
        int vehicleIndex = -1;
        for (int i = top; i >= 0; i--) {
            if (stack[i].licensePlate == licensePlate) {
                vehicleIndex = i;
                break;
            }
        }

        if (vehicleIndex == -1) {
            cout << "Vehicle with license plate " << licensePlate << " not found in parking.\n";
            return false;
        }

        // Remove the vehicle and shift elements above it down
        cout << "Vehicle with license plate " << stack[vehicleIndex].licensePlate
             << " from block " << stack[vehicleIndex].blockNumber << " is leaving the parking lot.\n";

        for (int i = vehicleIndex; i < top; i++) {
            stack[i] = stack[i + 1]; // Shift elements down
        }
        top--;
        return true;
    }

    // Search for a vehicle in the parking lot
    void searchVehicle(const string& licensePlate) {
        for (int i = top; i >= 0; i--) {
            if (stack[i].licensePlate == licensePlate) {
                cout << "Vehicle found in parking: Block Number " << stack[i].blockNumber
                     << ", Owner Name: " << stack[i].ownerName
                     << ", Vehicle Type: " << stack[i].vehicleType << ".\n";
                return;
            }
        }
        cout << "Vehicle with license plate " << licensePlate << " not found in parking.\n";
    }

    // Display all parked vehicles
    void displayVehicles() {
        if (top < 0) {
            cout << "Parking lot is empty.\n";
            return;
        }
        cout << "Vehicles in parking:\n";
        for (int i = top; i >= 0; i--) {
            cout << "Block Number: " << stack[i].blockNumber
                 << ", License Plate: " << stack[i].licensePlate
                 << ", Owner Name: " << stack[i].ownerName
                 << ", Vehicle Type: " << stack[i].vehicleType << endl;
        }
    }

    // Get the total revenue
    void displayRevenue() {
        cout << "Total revenue generated: $" << totalRevenue << endl;
    }

    // Get the parking rate based on vehicle type
    int getRate(const string& vehicleType) {
        if (vehicleType == "Car") {
            return 50;
        } else if (vehicleType == "Motorbike") {
            return 20;
        } else if (vehicleType == "Van") {
            return 100;
        }
        return -1; // Invalid vehicle type
    }

    // Get the total number of vehicles in the parking lot
    int totalVehicles() {
        return top + 1;
    }
};

int main() {
    ParkingStack parking;

    int choice;
    string licensePlate, ownerName, vehicleType;

    while (true) {
        // Improved menu-driven system
        cout << "\n================= Parking Management System =================\n";
        cout << "1. Park a vehicle\n";
        cout << "2. Remove a specific vehicle\n";
        cout << "3. Display vehicles\n";
        cout << "4. Search for a vehicle\n";
        cout << "5. View total vehicles in parking\n";
        cout << "6. View total revenue\n";
        cout << "7. Exit\n";
        cout << "=============================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // Park a vehicle
                cout << "Enter license plate (e.g., XYZ123): ";
                cin >> licensePlate;
                cout << "Enter owner name: ";
                cin.ignore(); // Clear input buffer before getline
                getline(cin, ownerName);
                cout << "Enter vehicle type (Car, Motorbike, Van): ";
                cin >> vehicleType;
                parking.parkVehicle(licensePlate, ownerName, vehicleType);
                break;

            case 2: // Remove a specific vehicle
                cout << "Enter license plate of the vehicle to remove: ";
                cin >> licensePlate;
                parking.removeVehicle(licensePlate);
                break;

            case 3: // Display vehicles
                parking.displayVehicles();
                break;

            case 4: // Search for a vehicle
                cout << "Enter license plate to search: ";
                cin >> licensePlate;
                parking.searchVehicle(licensePlate);
                break;

            case 5: // View total vehicles in parking
                cout << "Total vehicles in parking: " << parking.totalVehicles() << endl;
                break;

            case 6: // View total revenue
                parking.displayRevenue();
                break;

            case 7: // Exit
                cout << "Thank you for using the Parking Management System. Goodbye!\n";
                return 0;

            default: // Invalid input
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

