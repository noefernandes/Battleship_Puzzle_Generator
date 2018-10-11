# Battleship Puzzle Generator

# Student: 
- Noé Fernandes


# Intro

In this project was implemented a program that generates maps for the game Battleship Puzzle. The algorithm should receive the number of maps that the user wants to be generated, as well as the number of rows and columns of the map set to be generated. Therefore, through the command line, the user to provide this data in the format: ./run n_arq n_lin n_col, with the limit of 1 to 100 for the number of files, and 7 to 15 for the number of rows and columns, inclusive .

# Motivation

The purpose of this generator will be to be the basis for the second part of the project, the development of the game Batleship Puzzle.

# Strategy 

In the generator construction, the random and chrono libraries were used to develop a function that creates random numbers. Through this function it was possible to randomly obtain the position of each ship, in terms of rows and columns. In addition, a structure Navio was used, which stored the specific characteristics of each ship type, such as position, location, size and string representation. In the insertion of the ships, the strategy adopted was to add each ship always testing whether it is possible to place it horizontally or vertically. If one of the ways (or both) is played as possible, the algorithm chooses the one that has preference. Right after the selection process is used an istringstream that inserts character by character (duly converted into string) for the matrix. Isolating each ship with a differentiating character is a fundamental part of the two functions that were used in ships insertion.

# Output Files

The program results in two output files. One with only characters representing the ships and another with the output already formatted for user viewing.

# Alternative Libraries Used

- sstream
- fstream
- chrono
- Random
 
