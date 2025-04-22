Description:
This program creates an algorithm made to solve the 3-SAT problem, using a certifier algorithm and a brute-force algorithm.
It reads from an input file and writes to an output file.
It has O(3c * 2^n) time complexity, where c is the number of clauses given as input and n is the number of Boolean variables used within the clauses.
It accomplishes this by running the certifier algorithm on all possible truth alignments of the n variables, and returning true if any of the truth alignments are a valid solution to the problem. 
The certifier takes in the truth alignment and then checks all literals within the clauses, and if at least 1 literal in each clause is true than the clause as a whole is true. 
If all clauses are true, the truth alignment is a solution.
It 1 or more clauses are false, it returns false.
If the 3-SAT problem has a solution, the algorithm also returns a valid truth alignment for the problem.

Input File Format:
1st Line: either a 0 or 1, representing whether the input is running the brute force algorithm or the certifier directly (0 means algorithm, 1 means certifier)
2nd Line: the value of n where n is the number of Boolean variables used in the given 3-SAT input
3rd Line: the CNF form of a 3-SAT problem, inputted as the list of literals within each clause separated by spaces (so C1 = x1 V -x2 V x3 would be 1 -2 3 in the file).
4th Line: if the certifier is being test (i.e. 1st line of file is 1) than the a 4th line is added with the truth alignment to be passed into the certifier, inputted as a series of 0 and 1s with each corresponding to the truth alignment of a variable (i.e. x1 = 1, x2 = 0, x3 = 1 where n = 3 would be 1 0 1).

Example input.txt File (Certifier):
1
3
3 2 1 -3 -2 -1 3 -1 2 -3 -1 -2 -1 3 -2
0 0 1

Example input.txt File (Brute-Force Algorithm):
0
3
3 2 1 2 1 -3 1 3 -2 3 -1 -2 -3 2 -1

Instructions:
First, make sure that your command terminal, a file named input.txt with your input, and main.cpp are all in the same directory.
Then, run the following commands:
g++ -o test main.cpp
./test

This will read in your input.txt file, run it through the either the certifier or 3-SAT algorithm, and then generate a output.txt file in the same directory with the output (for the certifier

Testing:
In order to access the unit test cases, ensure that the test_units folder is in the same directory as your main.cpp file, remove input.txt from your directory and repeat the commands listed in the instructions.
The program will detect that input.txt is not in the directory and create 15 input files (5 testing the certifier and another 10 testing the brute-force algorithm), run each of them, and then create 15 corresponding output files.
The output will be written into the test_units folder.