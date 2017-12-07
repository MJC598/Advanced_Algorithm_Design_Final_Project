# CS3050_Final_Project
3050 Final Project
@authors: Matthew Carroll, Clayton Cornett, Brian Lasker, Jeff Rohlman

Objective:
Guide two robots from a starting to an ending point in a maze without the robots overlapping each other

Idea:
Take a BFS for both robots. If one of the robots can reach the exit without a conflict of the other robot, it takes the path to the exit before moving the other robot and then vice versa. If there is a conflict you find a place where one of the robots must move so there is the least movement possible. 

HOW TO RUN:
after importing the programs, type make to compile. The resulting executable file will be named Final_Project. To get the code to run you need two commands:
"/n" ./Final_Project room.txt "/n"
With room.txt being the maze you want to test on it.

OUTPUT:
The output will be the initial maze. To continue through press "enter" and the robot will move accordingly. When both robots have reached their respective exits or it is deemed impossible the program will terminate.
