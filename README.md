Compilation:

Use a standard C++ compiler, for example:
bash

g++ -o elevator_sim elevator_sim.cpp -std=c++11
This will produce an executable named elevator_sim (on Linux/macOS) or elevator_sim.exe (on Windows).
Execution:

Run the executable:
bash

./elevator_sim
When prompted, enter the number of elevators available.
Follow the on-screen instructions to input your current floor, choose a direction (up or down), and select your desired floors.
Exiting the Program:

To exit from the initial user floor prompt, enter -1.
When requesting destination floors, entering -1 after you are done will start the elevator movement.
Finally, when asked for your current floor (at the very beginning of a request cycle), entering -1 will end the entire program.
Example Interaction
vbnet

Enter the number of elevators available: 2
Enter your current floor (or -1 to exit): 3
Do you want to go 'up' or 'down'? up
Elevator 1 will pick you up.
Elevator 1 is moving to floor: 3
Floor: 2
Floor: 3
Elevator 1 has reached floor 3.
Elevator 1 door is open.
Elevator 1 door is closed.
Enter desired floor (or -1 to exit): 5
Enter desired floor (or -1 to exit): 8
Enter desired floor (or -1 to exit): -1
Elevator 1 will begin moving to the selected floors.
Time to floor 5: 20 seconds (includes door open/close time)
Time to floor 8: 35 seconds (includes door open/close time)
Total time for the entire journey: 55 seconds.
Elevator 1 is moving to floor: 5
Floor: 4
Floor: 5
Elevator 1 door is open.
Elevator 1 door is closed.
Elevator 1 is moving to floor: 8
Floor: 6
Floor: 7
Floor: 8
Elevator 1 door is open.
Elevator 1 door is closed.
Enter your current floor (or -1 to exit):

Notes
The code uses sleep(5) to simulate the time taken to move between floors and door operations.
Make sure to compile with -std=c++11 (or higher) if your compiler defaults to an older standard.
