# **MatrixMultiW**

## Authors: Chandramouli Iyer
## Author Emails: chandramouli.iyer@sjsu.edu
## Date Last Modified: December 6th, 2023


## Description
Unlike the previous one, this program accomplishes the same thing in parallel, but now 
also has the ability to accept multiple W matrices as arguments, which will all run in 
parallel, in corresponding number of child processes.

This program takes in at least 2 input files, but you can supply as many W matrices as
you wish. The program pairs the first matrix (the A matrix) with subsequent W matrices, 
creates the corresponding number of child processes, and passes the A matrix and the W'ith
matrix to the child process matrixmult_parallel, the same one from A2. It calculates the 
dot product of the input and weight matrices, and outputs the result to two files: PID.out 
and PID.err, where PID is the Process ID of the child process, and both files correspond to 
stdout and stderr respectively.

## Notes
The user needs to provide at least two files with numbers as input. The program 
assumes that the input file contains only numbers separated by spaces. If any 
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

Starting command 1: child 324924 pid of parent 324923 <br />
test/A1.txt=[ <br />
10.00 30.00 40.00 50.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
] <br />
test/W1.txt=[ <br />
1.00 3.00 4.00 5.00 1.00 0.00 0.00 0.00  <br />
2.00 4.00 5.00 0.00 0.00 0.00 0.00 0.00  <br />
1.00 1.00 5.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
] <br />
R=[ <br />
110.00 190.00 390.00 50.00 10.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
] <br />
Finished child 324924 pid of parent 324923 <br />
Exited with exitcode = 0 <br />
<br />
Starting command 2: child 324925 pid of parent 324923 <br />
test/A1.txt=[ <br />
10.00 30.00 40.00 50.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
] <br />
../A2/test/W.txt=[ <br />
5.00 3.00 0.00 0.00 0.00 5.00 0.00 0.00  <br />
5.00 3.00 0.00 0.00 0.00 5.00 0.00 0.00  <br />
5.00 3.00 0.00 0.00 0.00 5.00 0.00 0.00  <br />
1.00 1.00 0.00 0.00 0.00 1.00 0.00 0.00  <br />
1.00 0.00 0.00 0.00 0.00 1.00 0.00 0.00  <br />
1.00 2.00 0.00 0.00 0.00 1.00 0.00 0.00  <br />
1.00 1.00 0.00 0.00 0.00 1.00 0.00 0.00  <br />
1.00 1.00 0.00 0.00 0.00 1.00 0.00 0.00  <br />
] <br />
R=[ <br />
450.00 290.00 0.00 0.00 0.00 450.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
] <br />
Finished child 324925 pid of parent 324923 <br />
Exited with exitcode = 0 <br />
<br />
Starting command 3: child 324926 pid of parent 324923 <br />
test/A1.txt=[ <br />
10.00 30.00 40.00 50.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
] <br />
test/W2.txt=[ <br />
10.00 3.00 4.00 5.00 1.00 0.00 0.00 0.00  <br />
20.00 4.00 5.00 0.00 0.00 0.00 0.00 0.00  <br />
10.00 1.00 5.00 0.00 0.00 0.00 0.00 0.00  <br />
10.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
20.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
] <br />
R=[ <br />
1600.00 190.00 390.00 50.00 10.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
] <br />
Finished child 324926 pid of parent 324923 <br />
Exited with exitcode = 0 <br />

Since no errors were generated in this run, all the PID.err files are empty. However, if
errors were to be generated, they would be redirected to PID.err. <br />

You can provide your own test files to the program. Make sure they are readable by the 
current user and actually exist, otherwise the program will exit with an error. <br />

## Average Running Time <br />
Running the program three times with the following command: <br />

time ./matrixmult_multiw.o test/A1.txt test/W1.txt ../A2/test/W.txt test/W2.txt <br />

results in the following time output: <br />
./matrixmult_multiw.o test/A1.txt test/W1.txt ../A2/test/W.txt test/W2.txt  0.00s user 0.02s system 41% cpu 0.054 total <br />

./matrixmult_multiw.o test/A1.txt test/W1.txt ../A2/test/W.txt test/W2.txt  0.01s user 0.01s system 34% cpu 0.055 total <br />

./matrixmult_multiw.o test/A1.txt test/W1.txt ../A2/test/W.txt test/W2.txt  0.01s user 0.01s system 36% cpu 0.055 total <br />

which averages out to 0.055 secs per run.
