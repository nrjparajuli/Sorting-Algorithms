# Sorting-Algorithms
This project contains an implementation of several sorting algorithms in C++, specifically insertion sort, heap sort, merge sort and quick sort.

To compile the program and build a binary, run $ g++ Sorting.cpp -o Sorting

Then, run the executable by typing $ ./Sorting

The program is designed to run automatically. During its first iteration, it will create a list of 10 random numbers and save it into a file. It will, then, load the numbers into a dynamic array from the file and then employ different sorting algorithms to sort the numbers in the array. The numbers are then sent into an output file. On screen, it will display the time taken to run each algorithm. For every other iteration, the number of elements increases by a factor of 10 until the number of element reaches 1,000,000. 
