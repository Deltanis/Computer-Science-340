/*
Assignment 3, Question 1 "Kruskal's Algorithm"
Austin McPhail
200341412

*/

#include <iostream>
#include <climits> //Used for HIGH_VALUE

using namespace std;

//Priority Queue Data Structures
struct Edge {
	int vertex1;
	int vertext2;
	int distance;
};
Edge q[];
Edge t[];

//Kruskal Data Structures
struct VertexNode {
	int vertex;
	VertexNode* next;
};
struct SubsetNode {
	int size;
	VertexNode* firstVertex;
};
struct SetNode {
	int vertex;
	SetNode* left;
	SubsetNode* subset;
	SetNode* right;
};
SetNode* s;

void KruskalsMinimumSpanningTree(Edge q[], Edge t[], SetNode* &s);
void Initialization(Edge q[], int &edgeCount, SetNode* &s, int &vertexCount);
void Search(Edge q[], int edgeCount, SetNode* &s, int vertexCount, Edge t[]);
void Tree(Edge t[]);
void Insert(int x, int y, int z, Edge q[], int &edgeCount);
void Insert(int w, SetNode* &s, int &vertexCount);
void MakeSet(SetNode* &s);
void DeleteMin(Edge q[], int edgeCount);

int main() {
	KruskalsMinimumSpanningTree(q, t, s);
}

void KruskalsMinimumSpanningTree(Edge q[], Edge t[], SetNode* &s) {
	int edgeCount = 0;
	int vertexCount = 0;
	Initialization(q, edgeCount, s, vertexCount);
	Search(q, edgeCount, s, vertexCount, t);
	Tree(t);
	return;
}
void Initialization(Edge q[], int &edgeCount, SetNode* &s, int &vertexCount) {

}
void Search(Edge q[], int edgeCount, SetNode* &s, int vertexCount, Edge t[]) {

}
void Tree(Edge t[]) {

}
//Binary Heap Insert
void Insert(int x, int y, int z, Edge q[], int &edgeCount) {
	//create new edge
	Edge e;
	e.vertex1 = x;
	e.vertext2 = y;
	e.distance = z;
	//increment edges in tree
	edgeCount++;
	//determine positioning of e in priority queue
	int i = edgeCount;
	//percolate upwards
	while ((i > 1) && (e.distance < (q[i / 2].distance))) {
		q[i] = q[1 / 2];
		i = i / 2;
	}
	q[i] = e;
	return;
}
//AVL Tree Insert
void Insert(int w, SetNode* &s, int &vertexCount) {

}
void MakeSet(SetNode* &s) {

}
void DeleteMin(Edge q[], int edgeCount) {

}
