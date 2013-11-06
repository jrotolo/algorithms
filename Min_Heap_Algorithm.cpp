//=========================================
//      Implementation of Min Heap
//              Problem #1
//  @authors: Jarrod Rotolo / Caleb Ledger
//=========================================

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <string>
#include "timer.h"

using namespace std;

class Heap {
public:
    Heap();
    Heap(int k);
    ~Heap();
    void insert(int element);
    int extract_min();
    void print();
    int size() { return heap.size(); }
private:
    int left(int parent);
    int right(int parent);
    int parent(int child);
    void heapifyup(int index);
    void heapifydown(int index);
private:
    vector<int> heap;
};

// ================================================================
// Default Constructor
// ================================================================
Heap::Heap()
{
}

// ================================================================
// Default Deconstructor
// ================================================================
Heap::~Heap()
{
}

// ================================================================
// Inserts the element into the heap
// ================================================================
void Heap::insert(int element)
{
    heap.push_back(element);
    heapifyup(heap.size() - 1);
}

// ================================================================
// Removes and returns the min element from the heap
// ================================================================
int Heap::extract_min()
{
    int min = heap.front();
    heap[0] = heap.at(heap.size() - 1);
    heap.pop_back();
    heapifydown(0);
    return min;
}

// ================================================================
// Prints the heap in the console
// ================================================================
void Heap::print()
{
    vector<int>::iterator pos = heap.begin();
    cout << "Heap = ";
    while ( pos != heap.end() ) {
        cout << *pos << " ";
        ++pos;
    }
    cout << endl;
}

// ================================================================
// Restores the heap property up the tree
// ================================================================
void Heap::heapifyup(int index)
{
    while ( ( index > 0 ) && ( parent(index) >= 0 ) &&
            ( heap[parent(index)] > heap[index] ) )
    {
        int tmp = heap[parent(index)];
        heap[parent(index)] = heap[index];
        heap[index] = tmp;
        index = parent(index);
    }
}

// ================================================================
// Restores the heap property down the tree
// ================================================================
void Heap::heapifydown(int index)
{
    int child = left(index);
    if ( ( child > 0 ) && ( right(index) > 0 ) &&
         ( heap[child] > heap[right(index)] ) )
    {
        child = right(index);
    }
    if ( child > 0 )
    {
        int tmp = heap[index];
        heap[index] = heap[child];
        heap[child] = tmp;
        heapifydown(child);
    }
}

// ================================================================
// Sets the left child of the parent node
// ================================================================
int Heap::left(int parent)
{
    int i = ( parent << 1 ) + 1; // 2 * parent + 1
    return ( i < heap.size() ) ? i : -1;
}

// ================================================================
// Sets the right child of the parent node
// ================================================================
int Heap::right(int parent)
{
    int i = ( parent << 1 ) + 2; // 2 * parent + 2
    return ( i < heap.size() ) ? i : -1;
}

// ================================================================
// Sets the parent node of the child
// ================================================================
int Heap::parent(int child)
{
    if (child != 0)
    {
        int i = (child - 1) >> 1;
        return i;
    }
    return -1;
}

// ================================================================
// The Main function
// ================================================================
int main()
{
    // Create the heap
    Heap* myheap = new Heap();

    int num;
    double elapsedTime;
    const int SIZE = 3;
    char input[SIZE];
    ifstream inputFile;
    
    CStopWatch timer;

    inputFile.open("karyHeap-input.txt");

    timer.startTimer();
    // Reads the data from the input file
    while (!inputFile.eof())
    {
        inputFile >> input;
        if (input[0] == 'I')
        {
            inputFile >> input;
            num = atoi(input);
            myheap->insert(num);
            //myheap->print();
        } 
        else if (input[0] == 'E')
            cout << myheap->extract_min() << " \\\\ results for extract-min operation" << endl;
    } 

    timer.stopTimer();
    cout << timer.getElapsedTime() << " micro-sec" << endl;

    // Cleanup
    inputFile.close();
    delete myheap;
}
