# **MatrixMultiWA**

## Authors: Chandramouli Iyer
## Author Emails: chandramouli.iyer@sjsu.edu
## Date Last Modified: December 6th, 2023


## Description
This program does matrix multiplication in parallel, but now also has the ability to 
accept multiple A matrices as arguments, which will all run in parallel, in 
corresponding number of child processes. Furthermore, this program can take inputs from stdin.

This program taken in an input matrix and as many W matrices as CLI arguments. It multiplies
each W matrix with the supplied A matrix in a parallel manner. After that, the program 
would ask for input from stdin for more files. It would pass this file to each child process,
which would carry out matrix multiplication with the supplied file, and the W matrix that was
supplied previously. It would store all results in a dynamically allocated array which expands
as files are passed in. The program would again ask for more files, and the process continues 
until the user presses Ctrl+D. After input is finished, each each child's specific reuslt is 
written to its PID.out file where PID is the PID of the child process.


## Notes
The user needs to provide at least two files with numbers as input. The program 
assumes that the input file contains only numbers separated by spaces. If any 
of the files cannot be read for whatever reason, the program will list the problematic 
file to PID.err and quit.


## Installation
Step 1: Clone this repo locally: git clone -b master https://bitbucket.org/ciyer17/cs149 cs149_chandramouli_iyer

Step 2: Inside the cs149_chandramouli_iyer directory, navigate into the A5 directory.

Step 3: Compile two programs: <br />
gcc -o matrixmult_multiwa.o matrixmult_multiwa.c <br />
gcc -o matrixmult_parallel.o matrixmult_parallel.c <br />

You should have two executables: <br />
matrixmult_multiwa.o and matrixmult_parallel.o <br />

Make sure that the matrixmult_parallel executable is exactly named as given.


## Usage
Sample test files are provided with the program under the test directory. To run with 
the test files, execute the following commands (assuming you are in the directory where 
the program was compiled and the test directory is present in). <br />

./matrixmult_multiwa.o test/A1.txt test/W1.txt test/W2.txt test/W3.txt <br />

After pressing enter, the program will output: <br />

"Enter file path of an A Matrix:" <br /> <br/>

Enter the following (without quotes): <br />
"test/A2.txt" <br /> <br />

After pressing enter, the program will again ask for input: <br />
"Enter file path of an A Matrix (Ctrl+D to exit): " <br /> <br />

Enter the following (without quotes): <br />
"test/A3.txt" <br /> <br />

After pressing enter, the program will again ask for input: <br />
"Enter file path of an A Matrix (Ctrl+D to exit): " <br /> <br />

Enter the following (without quotes): <br />
"test/A1.txt" <br /> <br />

After pressing enter, the program will again ask for input: <br />
"Enter file path of an A Matrix (Ctrl+D to exit): " <br /> <br />

Enter the following (without quotes): <br />
"test/A2.txt" <br /> <br />

After pressing enter, the program will again ask for input: <br />
"Enter file path of an A Matrix (Ctrl+D to exit): " <br /> <br />

Enter the following (without quotes): <br />
"test/A3.txt" <br /> <br />

The program will again ask for input. Press Ctrl+D. <br /> <br />


The output for each process should be stored in PID.out and PID.err for stdout and stderr respectively.
You can view them via the following command. They would just show the files used, start, and end:

$ cat \*.out \*.err<br />

Looking at all the output files this should be the content: <br />

Starting command 1: child 335594 pid of parent 335593 <br />
A = test/A1.txt <br />
W = test/W1.txt <br />
R = [  <br />
110.00 190.00 390.00 50.00 10.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
70.00 150.00 190.00 50.00 10.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
11.00 19.00 39.00 5.00 1.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
110.00 190.00 390.00 50.00 10.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
70.00 150.00 190.00 50.00 10.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
11.00 19.00 39.00 5.00 1.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 ] <br />
Finished child 335594 pid of parent 335593 <br />
Exited with exitcode = 0 <br />

Starting command 2: child 335595 pid of parent 335593 <br />
A = test/A1.txt <br />
W = test/W2.txt <br />
R = [  <br />
1600.00 190.00 390.00 50.00 10.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
700.00 150.00 190.00 50.00 10.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
280.00 19.00 39.00 5.00 1.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
1600.00 190.00 390.00 50.00 10.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
700.00 150.00 190.00 50.00 10.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
280.00 19.00 39.00 5.00 1.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 ] <br />
Finished child 335595 pid of parent 335593 <br />
Exited with exitcode = 0 <br />

Starting command 3: child 335596 pid of parent 335593 <br />
A = test/A1.txt <br />
W = test/W3.txt <br />
R = [  <br />
110.00 190.00 390.00 550.00 550.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
70.00 150.00 190.00 110.00 70.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
11.00 19.00 39.00 55.00 55.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
110.00 190.00 390.00 550.00 550.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
70.00 150.00 190.00 110.00 70.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
11.00 19.00 39.00 55.00 55.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00  <br />
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 ] <br />
Finished child 335596 pid of parent 335593 <br />
Exited with exitcode = 0 <br /> <br />


However, if errors were to be generated, they would be redirected to PID.err. <br />

You can provide your own test files to the program. Make sure they are readable by the 
current user and actually exist, otherwise the program will exit with an error. <br />

You can pass in as many files as you wish, in any order, both on the command line as well as stdin. <br />


## Average Running Time <br />
Running the program three times with the following command (ignoring stdin times, the code for which 
is within the matrixmult_multiwa.c file itself and uses time.h): <br />

./matrixmult_multiwa.o test/A1.txt test/W1.txt test/W2.txt test/W3.txt <br />
Enter file path of an A Matrix: <br />
test/A2.txt <br />
Enter file path of an A Matrix (Ctrl+D to exit): <br />
test/A3.txt <br />
Enter file path of an A Matrix (Ctrl+D to exit): <br />
test/A1.txt <br />
Enter file path of an A Matrix (Ctrl+D to exit): <br />
test/A2.txt <br />
Enter file path of an A Matrix (Ctrl+D to exit): <br />
test/A3.txt <br />
Enter file path of an A Matrix (Ctrl+D to exit): <br />

results in the following time output: <br />

Run time: 0.002028 secs <br />

Run time: 0.002110 secs <br />

Run time: 0.001996 secs <br />

which averages out to approx 0.002045 secs per run. This can vary based upon number of inputs and compiler 
optimizations (like -O3).