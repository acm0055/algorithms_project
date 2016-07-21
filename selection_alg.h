/*
 * Name: Austin Chase Minor (acm0055@auburn.edu)
 * Auburn UserID: 903223922
 * Version: 4/22/16
 * 
 * Various selection algorithms.
 */

#include <iostream>
#include <cstdlib>
using namespace std;

//Thanks http://stackoverflow.com/questions/4295432/typedef-function-pointer
typedef void (*alg)(int*,int,int);

void algorithm1(int* a, int n, int k) {
  int temp;
  for (int i = 1; i < k + 1; i++) {
    for (int j = n-1; j > i - 1; j--) {
      if (a[j] > a[j - 1]) {
	temp = a[j];
	a[j] = a[j - 1];
	a[j - 1] = temp;
      }
    }
  }
  
  cout << a[k - 1] << endl;
}

void algorithm2(int* a, int n, int k) {
  int position;
  int temp;
  for (int i = 0; i < k; i++) {
    position = i;
    for (int j = i + 1; j < n; j++) {
      if (a[j] > a[position])
	position = j;
    }
    if (position != i) {
      temp = a[i];
      a[i] = a[position];
      a[position] = temp;
    }
  }

  cout << a[k - 1] << endl;
}

void algorithm3(int* a, int n, int k) {
  int* b = new int[n];
  int min = 0;
  for (int i = 0; i < k; i++) {
    b[i] = a[i];
  }
  for (int i = 1; i < k; i++) {
    if (b[i] < b[min])
      min = i;
  }
  for (int i = k; i < n; i++) {
    if (a[i] > b[min]) {
      b[min] = a[i];
      min = 0;
      for (int j = 1; j < k; j++) {
	if (b[j] < b[min])
	    min = j;
      }
    }
  }

  cout << b[min] << endl;
}

int partition(int* a, int left, int right, int pivot_index);
int recursive_algorithm4(int* a, int p, int r, int k);

void algorithm4(int* a, int n, int k) {
  cout << recursive_algorithm4(a,0,n - 1,k - 1) << endl;
}

int recursive_algorithm4(int* a, int p, int r, int k) {
  int pivotIndex = rand() % (r - p + 1) + p;
  int pivotNewIndex = partition(a,p,r,pivotIndex);
  if (pivotNewIndex - p - 1 >= k)
    return recursive_algorithm4(a,p,pivotNewIndex - 1, k);
  else if (pivotNewIndex - p - 1 == k - 1)
    return a[pivotNewIndex];
  else
    return recursive_algorithm4(a,pivotNewIndex + 1, r,k - pivotNewIndex + p - 1);
}

void swap(int& a, int& b) {
  int temp;
  temp = a;
  a = b;
  b = temp;
}

int partition(int* a, int left, int right, int pivot_index) {
  int pivotValue = a[pivot_index];
  swap(a[pivot_index], a[right]);
  int storeIndex = left;
  for (int i = left; i < right; i++) {
    if (a[i] > pivotValue) {
      swap(a[storeIndex], a[i]);
      storeIndex++;
    }
  }
  swap(a[right], a[storeIndex]);
  return storeIndex;
}
