/**************************************************************
Author: Niraj Parajuli
Filename: Sorting.cpp

This program generates a file of 10 random numbers,
copies them into an array and sorts the numbers using 
the following sorting algorithms:
*Insertion Sort
*Merge Sort
*Quick Sort
*Heap Sort

It, then, increases the number of items in the list 
by 10 and displays the time cost for sorting the list
with each algorithm.
**************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <new>
#include <limits>

using namespace std;

//generate a list of random numbers of size n 
//and save it to "list.txt"
void random_generator(int n);

//Declaring inserstion_sort
void insertion_sort(float A[], int n);

//declaring merge_sort and sub-function merge
void merge_sort(float A[], int p, int r);	
void merge (float A[], int p, int q, int r);

//delcaring quick_sort and sub-fuction partition
void quick_sort(float A[], int p, int r);
int partition(float A[], int p, int r);

//declaring heap_sort and sub-functions build_max_heap
//and max_heapify
void heap_sort(float A[], int length, int size);
void build_max_heap(float A[], int length, int size);
void max_heapify(float A[], int i, int size);

int main() {
  cout << "\nSorting Algorithm\t" << "Input Size\t" << "Time Cost (in secs)\n";
  cout << "***********************************************************\n";
  for (int k = 10; k <= 1000000; k = k * 10) {	//loop to increase number of items
    int length = k;	//number of items in a list

    float* main_array = new float[length]; //dynamic array to hold the numbers
    float* i_array = new float[length + 1]; //insertion-sort I/O array
    float* m_array = new float[length + 1]; //merge-sort I/O array
    float* q_array = new float[length + 1]; //quick-sort I/O array
    float* h_array = new float[length + 1]; //heap-sort I/O array

    random_generator(length);

    ifstream infile("inlist.txt"); //input file with list of numbers
    ofstream outfile; //output stream

    //load the items into an array
    if (infile.is_open()) {
      for (int i = 0; i < length; i++)
	infile >> main_array[i];
    } else {
      cout << "Error: Cannot open input file.";
      return -1;
    }

    //copy the array with indexing changed from A[0...n-1] to
    //A[1...n]
    for (int i = 0; i < length; i++) {
      i_array[i+1] = main_array[i];
      m_array[i+1] = main_array[i];
      q_array[i+1] = main_array[i];
      h_array[i+1] = main_array[i];
    }

    clock_t t;  //setting up time to calculate time cost
    float elapsed_time;

    //Insertion Sort
    t = clock();
    insertion_sort (i_array, length);
    t = clock() - t;
    elapsed_time = ((float)t)/CLOCKS_PER_SEC;
    
    //streaming output to file
    outfile.open("insertion-sort.txt"); 
    for (int i = 1; i <= length; i++)
      outfile << i_array[i] << " ";
    outfile.close();

    //displaying results for insertion-sort
    cout << "Insertion Sort\t\t" << length << "\t\t" << elapsed_time << endl;

    int startI = 1;
    int endI = length;

    //Merge Sort
    t = clock();
    merge_sort (m_array, startI, endI);
    t = clock() - t;
    elapsed_time = ((float)t)/CLOCKS_PER_SEC;

    //streaming output to file
    outfile.open("merge-sort.txt");
    for (int i = 1; i <= length; i++)
      outfile << m_array[i] << " ";
    outfile.close();

    //displaying results for merge-sort
    cout << "Merge Sort\t\t" << length << "\t\t" << elapsed_time << endl;

    //Quick Sort
    t = clock();
    quick_sort(q_array, startI, endI);
    t = clock() - t;
    elapsed_time = ((float)t)/CLOCKS_PER_SEC;

    //streaming output to file
    outfile.open("quick-sort.txt");
    for (int i = 1; i <= length; i++)
      outfile << q_array[i] << " ";
    outfile.close();

    //displaying results for quick-sort
    cout << "Quick Sort\t\t" << length << "\t\t" << elapsed_time << endl;

    //Heap Sort
    t = clock();
    heap_sort (h_array, length, length);
    t = clock() - t;
    elapsed_time = ((float)t)/CLOCKS_PER_SEC;

    //streaming output to file
    outfile.open("heap-sort.txt");
    for (int i = 1; i <= length; i++)
      outfile << h_array[i] << " ";
    outfile.close();

    //displaying results for heap-sort
    cout << "Heap Sort\t\t" << length << "\t\t" << elapsed_time << endl << endl;
  
    //returning all memory back to heap
    delete[] main_array;
    delete[] i_array;
    delete[] m_array;
    delete[] q_array;
    delete[] h_array;
  }
  return 0;
}

/***********************************************************
 **************Generate n random numbers********************
 ***********************************************************/
void random_generator (int n) {
  float random, seven = 7.0;
  ofstream outfile;

  srand(time(NULL));	//seed for the pseudo-random number

  outfile.open("inlist.txt");

  for (int i = 0; i < n; i++) {
    random = rand() % 10000;
    outfile << random / seven << " ";
  }
  outfile << endl;

  outfile.close();
  return;
}

/***********************************************************
 ***********************Insertion Sort**********************
 ***********************************************************/
void insertion_sort(float A[], int n) {
  float key;
  int i;
  for (int j = 2; j <= n; j++) {
    key = A[j];
    //Insert A[j] into the sorted sequence A[1...j-1]
    i = j - 1;
    while ((i > 0) && (A[i] > key)) {
      A[i + 1] = A[i];
      i--;
    }
    A[i+1] = key;
  }
  return;
}

/***********************************************************
 **************************Merge Sort***********************
 ***********************************************************/
void merge_sort(float A[], int p, int r) {
  if (p < r) {
    int q = (p + r) / 2;
    merge_sort(A, p, q);
    merge_sort(A, q+1, r);
    merge(A, p, q, r);
  }
  return;
}

void merge(float A[], int p, int q, int r) {
  int n1 = q - p + 1;
  int n2 = r - q;
  float L[n1 + 2], R[n2 + 2];

  for (int i = 1; i <= n1; i++) 
    L[i] = A[p + i - 1];

  for (int j = 1; j <= n2; j++)
    R[j] = A[q + j];

  L[n1 + 1] = numeric_limits<float>::max();
  R[n2 + 1] = numeric_limits<float>::max();

  int i = 1;
  int j = 1;

  for (int k = p; k <= r; k++) {
    if (L[i]<= R[j]) {
      A[k] = L[i];
      i++;
    }
    else {
      A[k] = R[j];
      j++;
    }
  }
  return;
}

/***********************************************************
 **************************Quick Sort***********************
 ***********************************************************/
void quick_sort(float A[], int p, int r) {
  if (p < r) {
    int q = partition(A, p, r);
    quick_sort(A, p, q-1);
    quick_sort(A, q+1, r);
  }
  return;
}

int partition(float A[], int p, int r) {
  float x = A[r];
  int i = p - 1;
  float temp;
  for (int j = p; j < r; j++) {
    if (A[j] <= x) {
      i++;
      temp = A[i];
      A[i] = A[j];
      A[j] = temp;
    }
  }
  temp = A[r];
  A[r] = A[i+1];
  A[i+1] = temp;

  return i+1;
}

/***********************************************************
 **************************Heap Sort************************
 ***********************************************************/
void heap_sort(float A[], int length, int size) {
	float temp;
	build_max_heap(A, length, size);
	for (int i = length; i > 1; i--) {
		temp = A[1];
		A[1] = A[i];
		A[i] = temp;
		size--;
		max_heapify(A, 1, size);
	}
}

void build_max_heap(float A[], int length, int size) {
	for (int i = length/2; i > 0; i--) 
	  max_heapify(A, i, size);
}

void max_heapify(float A[], int i, int size) {
	int largest;
	float temp;
	int l = 2*i;	//left child
	int r = 2*i + 1;	//right child

	if ((l <= size)&& (A[l] > A[i]))
		largest = l;
	else 
		largest = i;
	if ((r <= size) && (A[r] > A[largest]))
		largest = r;
	if (largest != i) {
		temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;
		max_heapify(A, largest, size);
	}
}
