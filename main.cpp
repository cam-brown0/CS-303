#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stdexcept>
#include <unistd.h>

using namespace std;

class Building {
public:
    vector<int> floors;

    // Constructor to initialize floors
    Building() {
        for (int i = 1; i <= 10; ++i) {
            floors.push_back(i); // Update to 10 floors
        }
    }
};

class Elevator : public Building {
public:
    int current_floor;
    vector<int> requested_floors;
    bool moving_up;
    int elevator_id; // Unique elevator ID

    // Constructor to set a random initial floor and assign ID
    Elevator(int id) : elevator_id(id) {
        srand(static_cast<unsigned>(time(0)));
        current_floor = floors[rand() % floors.size()];
        moving_up = true; // Assume initial movement is upwards
    }

    // Display the current floor
    void display_current_floor();

    // Collect requested floors from the user
    void collect_requested_floors();

    // Move the elevator to the target floor
    void move_floors(int target_floor);

    // Optimize and calculate the fastest route
    void optimize_path();

    // Calculate and display the total time required for the ride
    void calculate_time_for_journey(const vector<int>& path);

    // Simulate the elevator door opening and closing
    void door_open_close();
};

// Function to find the most efficient elevator based on proximity and direction
Elevator& find_best_elevator(vector<Elevator>& elevators, int user_floor, string direction) {
    Elevator* best_elevator = nullptr;
    int minimum_distance = 10; // Arbitrary large distance

    for (Elevator& elevator : elevators) {
        int distance = abs(elevator.current_floor - user_floor);

        // Check if the elevator is already going in the correct direction or is idle
        bool correct_direction = (direction == "up" && elevator.moving_up && user_floor >= elevator.current_floor) ||
                                 (direction == "down" && !elevator.moving_up && user_floor <= elevator.current_floor);

        if (distance < minimum_distance && correct_direction) {
            minimum_distance = distance;
            best_elevator = &elevator;
        }
    }

    // If no elevator in the correct direction, pick the closest one regardless of direction
    if (best_elevator == nullptr) {
        for (Elevator& elevator : elevators) {
            int distance = abs(elevator.current_floor - user_floor);
            if (distance < minimum_distance) {
                minimum_distance = distance;
                best_elevator = &elevator;
            }
        }
    }

    return *best_elevator;
}

void Elevator::display_current_floor() {
    cout << "Elevator " << elevator_id << " is currently on floor: " << current_floor << endl;
}

void Elevator::collect_requested_floors() {
    int desired_floor;
    while (true) {
        cout << "Enter desired floor (or -1 to exit): ";
        cin >> desired_floor;

        // Exit the floor selection menu
        if (desired_floor == -1) {
            break;
        }

        // Validate input
        if (find(floors.begin(), floors.end(), desired_floor) == floors.end()) {
            cout << "Invalid floor. Please choose a floor between 1 and 10." << endl;
        } else {
            requested_floors.push_back(desired_floor);
        }
    }

    if (!requested_floors.empty()) {
        cout << "Elevator " << elevator_id << " will begin moving to the selected floors." << endl;
        optimize_path();  // Optimize the elevator's path
    } else {
        cout << "No floors requested. Exiting." << endl;
    }
}

void Elevator::optimize_path() {
    vector<int> upward_floors, downward_floors;

    for (int floor : requested_floors) {
        if (floor > current_floor) {
            upward_floors.push_back(floor);
        } else if (floor < current_floor) {
            downward_floors.push_back(floor);
        }
    }

    // Sort floors to handle efficiently
    sort(upward_floors.begin(), upward_floors.end());
    sort(downward_floors.rbegin(), downward_floors.rend());

    vector<int> optimized_path = upward_floors;
    optimized_path.insert(optimized_path.end(), downward_floors.begin(), downward_floors.end());

    // Calculate and display the total time required for the journey
    calculate_time_for_journey(optimized_path);

    // Move to each floor in the optimized path
    for (int floor : optimized_path) {
        move_floors(floor);
        door_open_close();
    }

    // Update direction based on final destination
    moving_up = current_floor < *optimized_path.rbegin();
}

void Elevator::calculate_time_for_journey(const vector<int>& path) {
    int total_time = 0;
    int previous_floor = current_floor;

    for (int floor : path) {
        int travel_time = abs(floor - previous_floor) * 5;
        total_time += travel_time + 15; // 15 seconds for doors opening/closing
        previous_floor = floor;

        cout << "Time to floor " << floor << ": " << travel_time + 15 << " seconds (includes door open/close time)" << endl;
    }

    cout << "Total time for the entire journey: " << total_time << " seconds." << endl;
}

void Elevator::move_floors(int target_floor) {
    cout << "Elevator " << elevator_id << " is moving to floor: " << target_floor << endl;

    while (target_floor != current_floor) {
        if (target_floor > current_floor) {
            ++current_floor;
        } else if (target_floor < current_floor) {
            --current_floor;
        }

        cout << "Elevator " << elevator_id << " is now on floor: " << current_floor << endl;
        sleep(5); // Simulate time to move floors (5 seconds per floor)
    }

    cout << "Elevator " << elevator_id << " has reached floor " << target_floor << "." << endl;
}

void Elevator::door_open_close() {
    cout << "Elevator " << elevator_id << " door is open." << endl;
    sleep(5);  // Simulate door open time
    cout << "Elevator " << elevator_id << " door is closed." << endl;
}

int main() {
    int num_elevators;
    cout << "Enter the number of elevators available: ";
    cin >> num_elevators;

    vector<Elevator> elevators;
    for (int i = 1; i <= num_elevators; ++i) {
        elevators.push_back(Elevator(i)); // Assign elevator ID as i
    }

    while (true) {
        int user_floor;
        string direction;

        // Ask user for their current floor and desired direction
        cout << "Enter your current floor (or -1 to exit): ";
        cin >> user_floor;
        if (user_floor == -1) {
            cout << "Exiting program." << endl;
            break;
        }

        cout << "Do you want to go 'up' or 'down'? ";
        cin >> direction;

        // Find the most efficient elevator to handle the request
        Elevator& selected_elevator = find_best_elevator(elevators, user_floor, direction);

        cout << "Elevator " << selected_elevator.elevator_id << " will pick you up." << endl;

        selected_elevator.move_floors(user_floor);  // Move the selected elevator to the user
        selected_elevator.door_open_close();  // Simulate doors opening and closing

        // Collect multiple floor requests and move to them
        selected_elevator.collect_requested_floors();
    }

    return 0;
}
