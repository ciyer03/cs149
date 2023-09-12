# **MatrixMult**


## Authors: Chandramouli Iyer and Safiullah Saif
## Author Emails: chandramouli.iyer@sjsu.edu , safiullah.saif@sjsu.edu
## Date Last Modified: September 11th, 2023


## Description
In the C Standard Library, there are no routines for multiplying two matrices. This 
program aims to bridge that gap.

This program takes in three file inputs, called the input, weights, and bias matrices 
repectively. It calculates the dot product of the input and weight matrices. Then, it 
adds the product matrix and the bias matrices, and outputs the result to stdout.

## Notes
The user needs to provide exactly three files with numbers as input. The program 
assumes that the input file contains only positive integers separated by spaces. If any 
of the files cannot be read for whatever reason, the program will list the problematic 
file and quit.

## Installation
Step 1: Clone this repo locally: git clone https://ciyer17-admin@bitbucket.org/ciyer17/cs149.git  

Step 2: Navigate into the A1 directory.  

Step 3: Compile the program: gcc -O3 -o matrixmult matrixmult.c  

You should have a file called matrixmult which is the executable.

## Usage
Sample test files are provided with the program under the test directory. To run with 
the test files, execute the following commands (assuming you are in the directory where 
the program was compiled and the test directory is present in):

 1: ./matrixmult.o test/A1.txt test/W1.txt test/B1.txt
 
 2: ./matrixmult.o test/A2.txt test/W2.txt test/B2.txt
 
 3: ./matrixmult.o test/A3.txt test/W3.txt test/B3.txt  


The output should be the following, respectively:

 1: Result of test/A1.txt\*test/W1.txt+test/B1.txt is = [ 111 191 391 51 11 ]
 
 2: Result of test/A2.txt\*test/W2.txt+test/B2.txt is = [ 701 151 191 51 11 ]
 
 3: Result of test/A3.txt\*test/W3.txt+test/B3.txt is = [ 11 19 39 55 55 ]

You can provide your own test files to the program. Make sure they are readable by the 
current user and actually exist, otherwise the program will exit with an error.
