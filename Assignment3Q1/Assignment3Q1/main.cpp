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
	int height;
};
SetNode* s;

void KruskalsMinimumSpanningTree(Edge q[], Edge t[], SetNode* &s);
void Initialization(Edge q[], int &edgeCount, SetNode* &s, int &vertexCount);
void Search(Edge q[], int edgeCount, SetNode* &s, int vertexCount, Edge t[]);
void Tree(Edge t[]);
void Insert(int x, int y, int z, Edge q[], int &edgeCount);
bool Insert(int w, SetNode* &s, int &vertexCount);
void MakeSet(SetNode* &s);
Edge DeleteMin(Edge q[], int &edgeCount);
int Max(int height1, int height2);
int Height(SetNode* s);

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
	bool result;
	int X[23] = { 0, 1, 1, 2, 2, 3, 6, 6, 5, 5, 8, 8, 6, 10, 14, 8, 11, 7, 11, 13, 13, 13, 9 };
	int Y[23] = { 0, 2, 3, 4, 5, 10, 3, 4, 7, 8, 4, 6, 10, 14, 12, 10, 8, 11, 12, 12, 7, 9, 7 };
	int Z[23] = { 0, 70, 61, 31, 110, 59, 88, 70, 30, 67, 65, 100, 65, 140, 85, 26, 12, 126, 19, 39, 105, 30, 74 };
	for (int i = 1; i < 23; i++) {
		int x = X[i];
		int y = Y[i];
		int z = Z[i];
		Insert(x, y, z, q, edgeCount);
		result = Insert(x, s, vertexCount);
		if (result == true) {
			SetNode* v = Find(x, s);
			MakeSet(v);
		}
	}
	return;
}
void Search(Edge q[], int edgeCount, SetNode* &s, int vertexCount, Edge t[]) {
	while (/*length of t < vertexCount - 1*/) {
		//e is the shortest edge in the priority queue

	}
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
bool Insert(int w, SetNode* &s, int &vertexCount) {
	bool result = false;
	if (s == NULL) {
		//insert new leafnode
		s = new SetNode;
		s->vertex = w;
		s->left = NULL;
		s->subset = NULL;
		s->right = NULL;
		vertexCount++;
		result = true;
	}
	else if (w < s->vertex) {
		//traverse to left subtree
		result = Insert(w, s->left, vertexCount);
		if (result == true) {
			if (Height(s->left) - Height(s->right) == 2) {
				if (w < s->left->vertex) {
					LL(s);
				}
				else {
					LR(s);
				}
			}
		}
	}
	else if (w > s->vertex) {
		//traverse to right subtree
		result = Insert(w, s->left, vertexCount);
		if (result == true) {
			if (Height(s->right) - Height(s->left) == 2) {
				if (w < s->right->vertex) {
					RR(s);
				}
				else {
					RL(s);
				}
			}
		}
	}
	else
		result = false;
	if (result == true) {
		s->height = (Max(Height(s->left), Height(s->right)) + 1);
	}
	return result;
}
void MakeSet(SetNode* &s) {
	s->subset = new SubsetNode;
	s->subset->size = 1;
	s->subset->firstVertex = new VertexNode;
	s->subset->firstVertex->vertex = s->vertex;
	s->subset->firstVertex->next = NULL;
}
Edge DeleteMin(Edge q[], int &edgeCount) {
	Edge e = q[1];
	//move last edge in tree to the root of q
	q[1] = q[edgeCount];
	edgeCount--;
	//percolate downwards
	Edge temp = q[1];
	int i = 1;
	while (i * 2 <= edgeCount) {
		int child = i * 2;
		if ((child != edgeCount) && (q[child + 1].distance < q[child].distance))
			child++;
		if (q[child].distance < temp.distance)
			q[i] = q[child];
		else
			break;
		i = child;
	}
	q[i] = temp;
	return e;
}
