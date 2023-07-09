# maze_solver
This project is being created for the competition Technoxian Maze solver challenge organised by All India Council For Robotics & Automation (AICRA)” and the Ministry of Electronics & Information Technology, Govt of India.

# The Aim
The challenge is to build a small self-contained autonomous robot (Micromouse) to negotiate a maze in the shortest possible time. The Robot which will start on the START tile and reach the FINISH tile in the shortest time will be nominated as the winner.

# Electronics

Microcontroller used : Arduino Uno

Distance Sensors : IR sensors and Ultrasonic sensors


# Algorithm Used : Flood Fill Algorithm

Choosing an algorithm for the maze robot is
critical in solving the maze. The researchers
selected Flood fill algorithm to solve the maze
because of its efficient balance. Flood fill
algorithm is one of the best mazes solving
algorithms. The algorithm is used to discover
walls and obtain the best available route. Each
cell in the maze provides a value that indicates
its distance from the target.
The algorithm begins to address the distance of
each cell from its neighbors while no wall exists
to separate the cells. The mechanism starts from
the final point by giving it an initial value and
then moves forward to other neighboring points
by giving them a higher value. Sometimes the
algorithm identifies more than one route with
the same weight. However, it should determine
the shortest route and the most direct route to
the destination.

![image](https://github.com/adisehdev/maze_solver/assets/97792541/4af84c83-964b-4a61-932a-62a8fd0a98e3)


