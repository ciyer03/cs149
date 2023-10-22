# **MatrixMultParallel (Version with Child Processes and Logging)**
### Authors: Chandramouli Iyer and Safiullah Saif
### Author Emails: chandramouli.iyer@sjsu.edu, safiullah.saif@sjsu.edu

### Date Last Modified: October 11th, 2023

### Description
In the C Standard Library, there are no routines for multiplying two matrices. This program aims to bridge that gap. Unlike the previous one, this program accomplishes the same thing in parallel.
This program is a parallel matrix multiplication program that is built to utilize the power of multi-core computer systems. It is designed to multiply one primary matrix `A` with multiple secondary matrices `W1, W2, ... WN` in parallel. This program is focused on matrix operations and its enhanced logging capabilities.

### Notes
The user provides multiple files with numbers as input. The program assumes that the input file contains only positive integers separated by spaces. If any of the files cannot be read for whatever reason, the program will list the problematic file and quit. Furthermore, the matrices calculated will be 8x8 in size. Logging is central to this project. Each child process logs its operations and errors to separate files, named after its Process ID (PID). The multiplication logic used here is derived from Assignment A2, `matrixmult_parallel`.

### Installation
Step 1: Clone this repo locally: git clone https://safi_0919@bitbucket.org/ciyer17/cs149.git
Step 2: Navigate into the A3 directory.
Step 3: Compile the program: gcc -O3 -o matrixmult_parellel matrixmult_parellel.c
You should have a file called matrixmult_parellel which is the executable.


### Usage
Sample test files are provided with the program under the test directory. To run with the test files, execute the following commands (assuming you are in the directory where the program was compiled and the test directory is present):
./matrixmult_parellel.o test/A1.txt test/W1.txt
The output should be the following, respectively:
Result of A*W = [
11 7 0 0 0 11 0 0
21 13 0 0 0 21 0 0
16 10 0 0 0 16 0 0
16 10 0 0 0 16 0 0
21 13 0 0 0 21 0 0
26 16 0 0 0 26 0 0
26 16 0 0 0 26 0 0
16 10 0 0 0 16 0 0
]
You can provide your test files to the program. Make sure they are readable by the current user and exist, otherwise, the program will exit with an error.

### Average Running Time
Running the program three times with the following commands:
time ./matrixmult_parallel.o test/A.txt test/W.txt
results in the following time output:
./matrixmult_parallel.o test/A.txt test/W.txt 0.00s user 0.00s system 94% cpu 0.005 total
./matrixmult_parallel.o test/A.txt test/W.txt 0.00s user 0.00s system 94% cpu 0.004 total
./matrixmult_parallel.o test/A.txt test/W.txt 0.00s user 0.00s system 94% cpu 0.004 total
which averages out to 0.004 secs per run.






