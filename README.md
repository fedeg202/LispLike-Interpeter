# LispLike-Interpeter
A lisp-like interpreter made for an university exam. The specification can be found in the "Spec" PDF file.
This intepreter take as input from the command line a name of a file with ".txt" extension and does a lexical and semantic analysis on it, if it follow the grammar rules of the specification it does also an evaluation and put the output on the terminal.

## Requirements:
* A linux system
* g++ compiler

## How to get started
First you have to create the executable, to do so you have to download the code, extract the zip file, enter in the "Source" folder in the terminal and execute the following command:
```console
$ g++ -std=c++17 -o LispLikeInterpreter *.cpp
```
 ## Testing and Running
 There are some script for testing the intepreter in the "TestFiles" folder. To use them to test you have to be inside the folder where the executable is and execute the following command:
 ```console
$ ./LispLikeInterpreter [path_to_TestFIles_folder]/TestFiles/[name_of_the_test].txt
```
If you want to test it with other scripts, you just need to create a test script with ".txt" extension and from the same folder as before you have to execute the command:
 ```console
$ ./LispLikeInterpreter [path_to_test_script]/[name_of_the_test_script].txt
```
You can also try different mode by changing the value of DEBUG and VERBOSE in the lispintepreter.cpp file:
* VERBOSE set to 1: imply a more verbose program with more output on the console than the only output from the evaluation of the program
* DEBUG set to 1: imply same thing as VERBOSE set to 1 but it will also display the tokens made during the tokenizing phase and printing the syntax tree made during the parsing phase.
