/*
 * Name: Austin Chase Minor (acm0055@auburn.edu)
 * Auburn UserID: 903223922
 * Version: 4/22/16
 * 
 * Testing program to determine runtime complexity of
 * various selection algorithms. Outputs to csv.
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ratio>
#include "selection_alg.h"
using namespace std;

ofstream out{"HW2_ACM_MINOR.txt"};
int array_sizes[] = {10, 20, 30, 40, 50, 60,
		     70, 80, 90, 100, 200, 300,
		     400, 500, 600, 700, 800,
		     900, 1000};
alg algorithms[4] = {algorithm1, algorithm2,
		     algorithm3, algorithm4};

int* gen_in_order_array(int);
int* gen_rev_array(int);
int* permutate_array(int*, int);
int time_algorithm(alg, int*, int, int);
void time_all(int k);
const int num_times{1000};
const int proc_scale_factor{1};

int main() {
  srand(time(0));

  //for correct spacing in spreadsheet
  out << " , ";
  for (int i = 0; i < 19; i++)
    out << (array_sizes[i]*proc_scale_factor) << ", ";

  out << endl;
  //runs all algorithms with a k value
  time_all(5);
}

void time_all(int k) {
  long double avg_time{};
  int* a;

  //loops through the 4 algorithms
  for (int i = 0; i < 4; i++) {
    out << "algorithm " << (i+1) << ", ";
    //loops through the 19 array sizes
    for (int j = 0; j < 19; j++) {
      //loops through the number of times to run the algorithm
      //for a specific input size
      for (int l = 0; l < num_times; l++) {
	a = gen_in_order_array(array_sizes[j]*proc_scale_factor);
	avg_time += time_algorithm(algorithms[i],
				   a,
				   array_sizes[j]*proc_scale_factor, k);
	delete [] a;
      }
      for (int l = 0; l < num_times; l++) {
	a = gen_rev_array(array_sizes[j]*proc_scale_factor);
	avg_time += time_algorithm(algorithms[i],
				   a,
				   array_sizes[j]*proc_scale_factor, k);
	delete [] a;
      }
      for (int l = 0; l < num_times; l++) {
	a = permutate_array(gen_in_order_array(array_sizes[j]*proc_scale_factor),array_sizes[j]);
       	avg_time += time_algorithm(algorithms[i],
				   a,
				   array_sizes[j]*proc_scale_factor, k);
	delete [] a;
      }

      //calculates avg time based on number times ran
      //and the fact that the times are in nanoseconds
      avg_time /= (3*num_times);
      avg_time /= 1000000000;
      cout << "avg time " << avg_time << endl;
      out << avg_time << ", ";
      //resets the avg time for the above testing code to work
      avg_time = 0;
    }
    //makes new line for the next algorithm
    out << endl;
  }
}

//returns time taken
//Information on the specific syntax and working of the chrono library and this example
//was learned from "The C++ Programming Language (4th Edition)" - Bjarne Stroustrup
int time_algorithm(alg algorithm, int* a, int n, int k) {
  chrono::system_clock::time_point first = chrono::system_clock::now();
  algorithm(a,n,k);
  chrono::system_clock::time_point last = chrono::system_clock::now();
  return chrono::duration_cast<chrono::nanoseconds>(last-first).count();
}

//generate array from 1->n
int* gen_in_order_array(int n) {
  int* a = new int[n];

  for (int i = 0; i < n; i++)
    a[i] = i + 1;

  return a;
}

int* permutate_array(int* a, int n) {
  int temp;
  int rng_index;
  //simple array permutate in theta(n) time
  for (int i = 0; i < n; i++) {
    //randomly swaps elements in the
    //array starting from element i
    //to some random indice in the range
    rng_index = rand() % n;
    temp = a[i];
    a[i] = a[rng_index];
    a[rng_index] = temp; 
  }

  return a;
}

//generates from n->1
int* gen_rev_array(int n) {
  int* a = new int[n];

  int k = 0;
  for (int i = n - 1; i > -1; i--) {
    a[k] = i + 1;
    k++;
  }

  return a;
}
