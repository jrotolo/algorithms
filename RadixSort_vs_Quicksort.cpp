//=========================================
//        QuickSort vs RadixSort 
//              Problem #1
//  @authors: Jarrod Rotolo / Caleb Ledger
//=========================================

#include <iostream>
#include <stdlib.h>

using namespace std;

int x = 65535;
int k = 100;
int values[100];
int arr[100];
int i;


int compare(const void *a, const void *b)
{
	return(*(int*)a - *(int*)b);
}

// A utility function to get maximum value in arr[]
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// ================================================================
// A function to do counting sort of arr[] according to
// the digit represented by exp.
// ================================================================
int countSort(int arr[], int n, int exp)
{
    int output[n]; // output array
    int i, count[256] = {0};
 
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%256 ]++;
 
    // Change count[i] so that count[i] now contains actual position of
    // this digit in output[]
    for (i = 1; i < 256; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (arr[i]/exp)%256 ] - 1] = arr[i];
        count[ (arr[i]/exp)%256 ]--;
    }
 
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to curent digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// ================================================================
// The main function to that sorts arr[] of size n using Radix Sort
// ================================================================
void radixsort(int arr[], int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);
 
    // Do counting sort for every digit. Note that instead of passing digit number,
    // exp is passed. exp is 10^i where i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 256)
        countSort(arr, n, exp);
}

// ================================================================ 
// A utility function to print an array
// ================================================================
void print(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}


// ================================================================
// Main Driver function
// ================================================================
int main()
{
	// fill the array for qsort
	for (i = 0; i < k; i++)
	{
		values[i] = rand() % x;
	}
	cout <<"After sorting with qsort: \n";
	int n;
	qsort(values, k, sizeof(int), compare);
	for (n = 0; n < k; n++)
		cout << values[n] << " ";

	cout <<"\n \n";


	// fills the array for radix
	for (int j = 0; j < k; j++)
	{
		arr[j] = rand() % x;
	}
    int p = sizeof(arr)/sizeof(arr[0]);
    radixsort(arr, p);
    
    cout <<"After sorting with radix: \n";
    print(arr, p);
	return 0;
}