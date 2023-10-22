# **MatrixMultiW**

## Authors: Chandramouli Iyer and Safiullah Saif
## Author Emails: chandramouli.iyer@sjsu.edu , safiullah.saif@sjsu.edu
## Date Last Modified: October 11th, 2023


## Description
In the C Standard Library, there are no routines for multiplying two matrices. This 
program aims to bridge that gap. Unlike the previous one, this program accomplishes the 
same thing in parallel, but now also has the ability to accept multiple W matrices as 
arguments, which will all run in parallel, in corresponding number of child processes.

This program takes in at least 2 input files, but you can supply as many W matrices as
you wish. The program pairs the first matrix (the A matrix) with subsequent W matrices, 
creates the corresponding number of child processes, and passes the A matrix and the W'ith
matrix to the child process matrixmult_parallel, the same one from A2. It calculates the 
dot product of the input and weight matrices, and outputs the result to two files: PID.out 
and PID.err, where PID is the Process ID of the child process, and both files correspond to 
stdout and stderr respectively.

## Notes
The user needs to provide at least two files with numbers as input. The program 
assumes that the input file contains only positive integers separated by spaces. If any 
of the files cannot be read for whatever reason, the program will list the problematic 
file to PID.err and quit. Furthermore, the matrices calculated will be 8x8 in size.


## Installation
Step 1: Clone this repo locally: git clone -b master https://bitbucket.org/ciyer17/cs149 cs149_chandramouli_iyer

Step 2: Inside the cs149_chandramouli_iyer directory, navigate into the A3 directory.

Step 3: Compile two programs: <br />
gcc -o matrixmult_multiw.o matrixmult_multiw.c <br />
gcc -o matrixmult_parallel.o matrixmult_parallel.c <br />

You should have two files: <br />
matrixmult_multiw.o and matrixmult_parallel.o <br />

Make sure that the matrixmult_parallel executable is exactly named as given.


## Usage
Sample test files are provided with the program under the test directory. To run with 
the test files, execute the following commands (assuming you are in the directory where 
the program was compiled and the test directory is present in). We will also use files from 
the previous assignment:

./matrixmult_multiw.o test/A1.txt test/W1.txt ../A2/test/W.txt test/W2.txt <br />


The output should be stored in PID.out and PID.err for stdout and stderr respectively.
Here are the outputs of each file respectively:

$ cat \*.out \*.err<br />

Starting command 1: child 162440 pid of parent 162439<br />
test/A1.txt=[<br />
10 30 40 50 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
]<br />
test/W1.txt=[<br />
1 3 4 5 1 0 0 0<br />
2 4 5 0 0 0 0 0<br />
1 1 5 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
]<br />
R=[<br />
110 190 390 50 10 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
]<br />
Finished child 162440 pid of parent 162439<br />
Exited with exitcode = 0<br />
<br />
Starting command 2: child 162441 pid of parent 162439<br />
test/A1.txt=[<br />
10 30 40 50 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
]<br />
../A2/test/W.txt=[<br />
5 3 0 0 0 5 0 0<br />
5 3 0 0 0 5 0 0<br />
5 3 0 0 0 5 0 0<br />
1 1 0 0 0 1 0 0<br />
1 0 0 0 0 1 0 0<br />
1 2 0 0 0 1 0 0<br />
1 1 0 0 0 1 0 0<br />
1 1 0 0 0 1 0 0<br />
]<br />
R=[<br />
450 290 0 0 0 450 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
]<br />
Finished child 162441 pid of parent 162439<br />
Exited with exitcode = 0<br />
<br />
Starting command 3: child 162442 pid of parent 162439<br />
test/A1.txt=[<br />
10 30 40 50 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
]<br />
test/W2.txt=[<br />
10 3 4 5 1 0 0 0<br />
20 4 5 0 0 0 0 0<br />
10 1 5 0 0 0 0 0<br />
10 0 0 0 0 0 0 0<br />
20 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
]<br />
R=[<br />
1600 190 390 50 10 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
0 0 0 0 0 0 0 0<br />
]<br />
Finished child 162442 pid of parent 162439<br />
Exited with exitcode = 0<br />

Since no errors were generated in this run, all the PID.err files are empty. However, if
errors were to be generated, they would be redirected to PID.err. <br />

You can provide your own test files to the program. Make sure they are readable by the 
current user and actually exist, otherwise the program will exit with an error. <br />

## Average Running Time <br />
Running the program three times with the following command: <br />

time ./matrixmult_multiw.o test/A1.txt test/W1.txt ../A2/test/W.txt test/W2.txt <br />

results in the following time output: <br />
./matrixmult_multiw.o test/A1.txt test/W1.txt ../A2/test/W.txt test/W2.txt  0.01s user 0.01s system 35% cpu 0.053 total <br />

./matrixmult_multiw.o test/A1.txt test/W1.txt ../A2/test/W.txt test/W2.txt  0.01s user 0.01s system 40% cpu 0.044 total <br />

./matrixmult_multiw.o test/A1.txt test/W1.txt ../A2/test/W.txt test/W2.txt  0.01s user 0.01s system 33% cpu 0.050 total <br />

which averages out to 0.049 secs per run.
