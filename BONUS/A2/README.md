# **MatrixMultParallel**

## Authors: Chandramouli Iyer
## Author Emails: chandramouli.iyer@sjsu.edu
## Date Last Modified: December 6th, 2023


## Description
This program takes in two file inputs, called the input and weights matrices 
respectively. It calculates input * weight and outputs the result to stdout.

## Notes
The user needs to provide exactly two files with numbers as input. The program 
assumes that the input file contains only numbers separated by spaces. If any 
of the files cannot be read for whatever reason, the program will list the problematic 
file and quit. Furthermore, the matrices calculated will be 8x8 in size.

## Installation
Step 1: Clone this repo locally: git clone -b master https://bitbucket.org/ciyer17/cs149 cs149_chandramouli_iyer

Step 2: Navigate into the BONUS/A2 directory.

Step 3: Compile the program: gcc -o matrixmult_parellel matrixmult_parellel.c  

You should have a file called matrixmult_parellel which is the executable.

## Usage
Sample test files are provided with the program under the test directory. To run with 
the test files, execute the following commands (assuming you are in the directory where 
the program was compiled and the test directory is present in):

./matrixmult_parellel.o test/A.txt test/W.txt


The output should be the following, respectively:

Result of A*W = [ <br />
11.00 7.00 0.00 0.00 0.00 11.00 0.00 0.00 <br /> 
21.00 13.00 0.00 0.00 0.00 21.00 0.00 0.00 <br />
16.00 10.00 0.00 0.00 0.00 16.00 0.00 0.00 <br />
16.00 10.00 0.00 0.00 0.00 16.00 0.00 0.00 <br />
21.00 13.00 0.00 0.00 0.00 21.00 0.00 0.00 <br />
26.00 16.00 0.00 0.00 0.00 26.00 0.00 0.00 <br />
26.00 16.00 0.00 0.00 0.00 26.00 0.00 0.00 <br />
16.00 10.00 0.00 0.00 0.00 16.00 0.00 0.00 <br />
] <br />


You can provide your own test files to the program. Make sure they are readable by the 
current user and actually exist, otherwise the program will exit with an error. <br />

## Average Running Time
Running the program three times with the following commands: <br />

time ./matrixmult_parallel.o test/A.txt test/W.txt <br />

results in the following time output: <br />
./matrixmult_parallel.o test/A.txt test/W.txt  0.00s user 0.00s system 98% cpu 0.006 total

./matrixmult_parallel.o test/A.txt test/W.txt  0.00s user 0.00s system 96% cpu 0.006 total

./matrixmult_parallel.o test/A.txt test/W.txt  0.00s user 0.00s system 94% cpu 0.004 total <br />

which averages out to 0.005 secs per run.
