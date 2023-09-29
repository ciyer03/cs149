# **MatrixMultParallel**

## Authors: Chandramouli Iyer and Safiullah Saif
## Author Emails: chandramouli.iyer@sjsu.edu , safiullah.saif@sjsu.edu
## Date Last Modified: September 28th, 2023


## Description
In the C Standard Library, there are no routines for multiplying two matrices. This 
program aims to bridge that gap. Unlike the previous one, this program accomplishes the 
same thing in parallel.

This program takes in two file inputs, called the input and weights matrices 
respectively. It calculates the dot product of the input and weight matrices, and outputs 
the result to stdout.

## Notes
The user needs to provide exactly two files with numbers as input. The program 
assumes that the input file contains only positive integers separated by spaces. If any 
of the files cannot be read for whatever reason, the program will list the problematic 
file and quit. Furthermore, the matrices calculated will be 8x8 in size.

## Installation
Step 1: Clone this repo locally: git clone https://ciyer17-admin@bitbucket.org/ciyer17/cs149.git  

Step 2: Navigate into the A2 directory.  

Step 3: Compile the program: gcc -O3 -o matrixmult_parellel matrixmult_parellel.c  

You should have a file called matrixmult_parellel which is the executable.

## Usage
Sample test files are provided with the program under the test directory. To run with 
the test files, execute the following commands (assuming you are in the directory where 
the program was compiled and the test directory is present in):

./matrixmult_parellel.o test/A1.txt test/W1.txt


The output should be the following, respectively:

Result of A*W = [ <br />
11   7  0  0  0  11  0  0 <br />
21  13  0  0  0  21  0  0 <br />
16  10  0  0  0  16  0  0 <br />
16  10  0  0  0  16  0  0 <br />
21  13  0  0  0  21  0  0 <br />
26  16  0  0  0  26  0  0 <br />
26  16  0  0  0  26  0  0 <br />
16  10  0  0  0  16  0  0 <br />
] <br />


You can provide your own test files to the program. Make sure they are readable by the 
current user and actually exist, otherwise the program will exit with an error.
