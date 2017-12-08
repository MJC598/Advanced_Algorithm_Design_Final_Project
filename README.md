# CS3050_Final_Project
3050 Final Project
@authors: Matthew Carroll, Clayton Cornett, Brian Lasker, Jeff Rohlman

Objective:
Guide two robots from a starting to an ending point in a maze without the robots overlapping each other

Idea:
Take a DFS for both robots. If one of the robots can reach the exit without a conflict of the other robot, it takes the path to the exit before moving the other robot and then vice versa. If there is a conflict you find a place where one of the robots must move so there is the least movement possible. 

HOW TO RUN:
after importing the programs, type make to compile. The resulting executable file will be named Final_Project. To get the code to run you need two commands:

./Final_Project room.txt

With room.txt being the maze you want to test on it.

OUTPUT:
The direct paths of the robots will be shown. If there are no direct paths readily avaliable, but there are solutions to the maze, multiple outputs will be displayed. The displays will be the intial move out of the way by the first robot, then the first robot will exit the maze. Following the exit of the maze, the program will report the direct way out of the maze for the last remaining robot. All doable solutions also show the length of each robot's path.

Exit Codes: 
5 - file would not open
6 - Incorrect number of arguments
7 - Parsing error
