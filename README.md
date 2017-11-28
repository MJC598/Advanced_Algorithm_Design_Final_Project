# CS3050_Final_Project
3050 Final Project
@authors: Matthew Carroll, Clayton Cornett, Brian Lasker, Jeff Rohlman

Objective:
Guide two robots from a starting to an ending point in a maze without the robots overlapping each other

Idea:
Take a BFS for both robots. If one of the robots can reach the exit without a conflict of the other robot, it takes the path to the exit before moving the other robot and then vice versa. If there is a conflict you find a place where one of the robots must move so there is the least movement possible. 
