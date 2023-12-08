# **MatrixMultiW_Deep**

## Authors: Chandramouli Iyer
## Author Emails: chandramouli.iyer@sjsu.edu
## Date Last Modified: December 7th, 2023


## Description
Unlike the previous one, this program accomplishes the same thing in parallel, but 
now also has the ability to accept multiple W matrices as arguments, which will all 
run in parallel, in corresponding number of child processes. Furthermore, this 
program can take inputs from stdin.

This program taken in an input matrix and as many W matrices as CLI arguments. It then 
creates an rSumMatrix which the summation of the product of the input matrix and each of 
the W matrices. After that, the program would ask for input from stdin for more files.
For these files, the rSumMatrix calculated previously would be provided as the input 
matrix. Then, these would be summed to create an updated rSumMatrix. The program would 
again ask for more files, and the process continues until the user presses Ctrl+D. The 
program would dynamically allocate the requistite amount of memory for the files given.
This program uses mmap() to share the result array with the parent.

## Notes
The user needs to provide at least two files with numbers as input. The program 
assumes that the input file contains only positive integers separated by spaces. If any 
of the files cannot be read for whatever reason, the program will list the problematic 
file to PID.err and quit. Furthermore, the matrices calculated will be 8x8 in size.


## Installation
Step 1: Clone this repo locally: git clone -b master https://bitbucket.org/ciyer17/cs149 cs149_chandramouli_iyer

Step 2: Inside the cs149_chandramouli_iyer directory, navigate into the BONUS/A4 directory.

Step 3: Compile two programs: <br />
gcc -o matrixmult_multiw_deep.o matrixmult_multiw_deep.c <br />
gcc -o matrixmult_parallel.o matrixmult_parallel.c <br />

You should have two executables: <br />
matrixmult_multiw_deep.o and matrixmult_parallel.o <br />

Make sure that the matrixmult_parallel executable is exactly named as given.


## Usage
Sample test files are provided with the program under the test directory. To run with 
the test files, execute the following commands (assuming you are in the directory where 
the program was compiled and the test directory is present in). <br />

./matrixmult_multiw_deep.o test/A1.txt test/W1.txt test/W2.txt test/W3.txt <br />

After pressing enter, the program will output: <br />

"Enter file paths:" <br /> <br/>

Enter the following (without quotes): <br />
"test/W4.txt test/W5.txt test/W6.txt test/W7.txt" <br /> <br />

After pressing enter, the program will again ask for input: <br />
"Enter file paths (Ctrl+D to exit): " <br /> <br />

Enter the following (without quotes): <br />
"test/W8.txt" <br /> <br />

The program will again ask for input. Press Ctrl+D.

The output should be: <br />
Rsum = [ <br />
71350 54770 54770 54770 54770 54770 54770 97080 <br /> 
0 0 0 0 0 0 0 0 <br />
0 0 0 0 0 0 0 0 <br />
0 0 0 0 0 0 0 0 <br />
0 0 0 0 0 0 0 0 <br />
0 0 0 0 0 0 0 0 <br />
0 0 0 0 0 0 0 0 <br />
0 0 0 0 0 0 0 0 <br />
] <br />

The output for each process should be stored in PID.out and PID.err for stdout and stderr respectively.
You can view them via the following command. They would just show the files used, start, and end:

$ cat \*.out \*.err<br />

However, if errors were to be generated, they would be redirected to PID.err. <br />

You can provide your own test files to the program. Make sure they are readable by the 
current user and actually exist, otherwise the program will exit with an error. <br />

You can pass in as many files as you wish, in any order, both on the command line as well as stdin. <br />


## Average Running Time <br />
Running the program three times with the following command (ignoring stdin times, the code for which 
is within the matrixmult_multiw_deep.c file itself and uses time.h): <br />

./matrixmult_multiw_deep.o test/A1.txt test/W1.txt test/W2.txt test/W3.txt <br />

and then two lines in stdin: <br />
Enter file paths: <br />
test/W4.txt test/W5.txt test/W6.txt test/W7.txt <br />
Enter file paths (Ctrl+D to exit): <br />
test/W8.txt <br />

results in the following time output: <br />

Run time: 0.003049 secs <br />

Run time: 0.003808 secs <br />

Run time: 0.002906 secs <br />

which averages out to approx 0.0033 secs per run. This can vary based upon number of inputs, 
number of cores and threads on the CPU, current CPU governor, the CPU itself, and compiler 
optimizations (like -O3).
