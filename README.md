# RobotDevelopment
RobotDevelopment

# line following
In the line following section, we made the hardware design and software design in two parts.
The hardware part of the work, including the choice of sensors, the top design, wiring design, light sensor selection debugging.
The work of the software part includes the general idea, the concrete algorithm realization, the data processing parameter computation, the algorithm process refinement, the improvement process and so on.
In the process of completing the inspection line, we found a lot of problems, such as can not read two sensors at the same time for reading analysis, the cycle design is too complicated to lead to the car can not respond to the offset in time, etc., but in our group Members of the common discussion, we redesign the process, modify the algorithm, determine the method to simplify the number of cycles, and ultimately get a satisfactory result.

# pass the maze
First, take the maze of the general idea is: always along the right / left side of the wall to go. By observing the maze of the topological structure, it is not difficult to find that the maze of our walk is not isolated, not connected with other walls of the wall, so it is a "single connected maze", there is no loop in the single connected maze, the maze is split by the correct path Into two parts, so as long as the side of the wall to go, always able to get out of the maze.
Then we need to achieve the "walk" algorithm based on the specific terrain.
By observing the maze of the maze, we choose to "go right" and summarize the following typical cases:
1\ default, the right is the straight wall, front accessibility. In this case we should control the robot along the wall to do straight, while the control and wall distance to maintain a fixed value.
2\ right is the straight wall, the front is the wall. In this case we should control the robot to turn left and return to the default.
3\ right no wall In this case, the robot should turn right to ninety degrees or one hundred and eighty degrees, and then return to the default situation.
