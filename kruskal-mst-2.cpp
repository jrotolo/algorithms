//=============================================================
//          Kruskal Minimumum Spanning Tree Algorithm
//               By: Jarrod Rotolo & Caleb Leger
//=============================================================

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

struct Edge
{
	int src, dest, weight;
};

struct EdgeList
{
	int V, E;
	struct Edge* edge;
};

struct Set
{
	int parent;
	int size;
};

struct EdgeList* buildEdgeList(int N, int M)
{
	struct EdgeList* edgeList = (struct EdgeList*)malloc(sizeof(struct EdgeList));
	edgeList->V = N;
	edgeList->E = M;
	edgeList->edge = (struct Edge*)malloc(edgeList->E * sizeof(struct Edge));
	return edgeList;
}

int find(struct Set sets[], int vertex)
{
	if (sets[vertex].parent != vertex)
		sets[vertex].parent = find(sets, sets[vertex].parent);
	return sets[vertex].parent;
}

void Union(struct Set sets[], int u, int v)
{
	int pNode = find(sets, u);
	int qNode = find(sets, v);

	if (sets[pNode].size < sets[qNode].size)
		sets[pNode].parent = qNode;
	else if (sets[pNode].size > sets[qNode].size)
		sets[qNode].parent = pNode;
	else { sets[qNode].parent = pNode; sets[pNode].size++; }
}

// Used to sort edges if not already sorted
int compareEdges(const void* a, const void* b)
{
    struct Edge* e1 = (struct Edge*)a;
    struct Edge* e2 = (struct Edge*)b;
    return e1->weight > e2->weight;
}

void KruskalMST(struct EdgeList* edgeList)
{
	int numVertices = edgeList->V;
	struct Edge resultMST[numVertices];

	qsort(edgeList->edge, edgeList->E, sizeof(edgeList->edge[0]), compareEdges);

	struct Set* sets = (struct Set*)malloc(numVertices * sizeof(struct Set));

	// Initialize our Set array
	for (int i=0; i < numVertices; ++i)
	{
		sets[i].parent = i;
		sets[i].size = 0;
	}

	int e = 0;
	int i = 0;
	while (e < (numVertices-1))
	{
		struct Edge pEdge = edgeList->edge[i++];
		int u = find(sets, pEdge.src);
		int v = find(sets, pEdge.dest);

		// Checking for cycle
		if (u != v) { resultMST[e++] = pEdge; Union(sets, u, v); }
	}

	printf("The Minimum Spanning Tree:\n");
	for (int j=0; j<e; ++j)
		printf("Source: %d, Destination: %d, Weight: %d\n",
			resultMST[j].src, resultMST[j].dest, resultMST[j].weight);
	return;
}

int main()
{
    int V = 10;  // Number of vertices in graph
    int E = 11;  // Number of edges in graph
    struct EdgeList* edgeList = buildEdgeList(V, E);

    edgeList->edge[0].src = 0;
    edgeList->edge[0].dest = 1;
    edgeList->edge[0].weight = 4;

    edgeList->edge[1].src = 0;
    edgeList->edge[1].dest = 3;
    edgeList->edge[1].weight = 6;


    edgeList->edge[2].src = 1;
    edgeList->edge[2].dest = 3;
    edgeList->edge[2].weight = 8;


    edgeList->edge[3].src = 2;
    edgeList->edge[3].dest = 4;
    edgeList->edge[3].weight = 8;


    edgeList->edge[4].src = 3;
    edgeList->edge[4].dest = 4;
    edgeList->edge[4].weight = 9;

    edgeList->edge[5].src = 4;
    edgeList->edge[5].dest = 5;
    edgeList->edge[5].weight = 10;

    edgeList->edge[6].src = 4;
    edgeList->edge[6].dest = 6;
    edgeList->edge[6].weight = 12;

    edgeList->edge[7].src = 5;
    edgeList->edge[7].dest = 6;
    edgeList->edge[7].weight = 14;

    edgeList->edge[8].src = 5;
    edgeList->edge[8].dest = 7;
    edgeList->edge[8].weight = 16;

    edgeList->edge[9].src = 7;
    edgeList->edge[9].dest = 8;
    edgeList->edge[9].weight = 18;

    edgeList->edge[10].src = 9;
    edgeList->edge[10].dest = 10;
    edgeList->edge[10].weight = 22;

    KruskalMST(edgeList);

    return 0;
}
